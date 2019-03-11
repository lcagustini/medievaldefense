#define SERVER "192.168.43.93"
#define PORT 8888

Wifi_AccessPoint* findAP(void){
	int selected = 0;  
	int i;
	int count = 0, displaytop = 0;

	static Wifi_AccessPoint ap;

	Wifi_ScanMode(); //this allows us to search for APs

	int pressed = 0;
	do {
		scanKeys();
		pressed = keysDown();

		count = Wifi_GetNumAP();

		consoleClear();

		iprintf("%d APs detected\n\n", count);

		int displayend = displaytop + 10;
		if (displayend > count) displayend = count;

		for(i = displaytop; i < displayend; i++) {
			Wifi_AccessPoint ap;

			Wifi_GetAPData(i, &ap);

			// display the name of the AP
			iprintf("%s %.29s\n  Wep:%s Sig:%i\n", 
				i == selected ? "*" : " ", 
				ap.ssid, 
				ap.flags & WFLAG_APDATA_WEP ? "Yes " : "No ",
				ap.rssi * 100 / 0xD0);
		}

		if(pressed & KEY_UP) {
			selected--;
			if(selected < 0) {
				selected = 0;
			}
			if(selected<displaytop) displaytop = selected;
		}

		if(pressed & KEY_DOWN) {
			selected++;
			if(selected >= count) {
				selected = count - 1;
			}
			displaytop = selected - 9;
			if (displaytop<0) displaytop = 0;
		}
		swiWaitForVBlank();
	} while(!(pressed & KEY_A));

	Wifi_GetAPData(selected, &ap);

	return &ap;
}

u8 connectToAP(Wifi_AccessPoint* ap) {
    int status = ASSOCSTATUS_DISCONNECTED;

    consoleClear();
    consoleSetWindow(NULL, 0,0,32,10);

    iprintf("Connecting to %s\n", ap->ssid);

    //this tells the wifi lib to use dhcp for everything
    Wifi_SetIP(0,0,0,0,0);	
    char wepkey[64];
    int wepmode = WEPMODE_NONE;
    if (ap->flags & WFLAG_APDATA_WEP) {
        iprintf("Enter Wep Key\n");
        while (wepmode == WEPMODE_NONE) {
            scanf("%s",wepkey);
            if (strlen(wepkey)==13) {
                wepmode = WEPMODE_128BIT;
            } else if (strlen(wepkey) == 5) {
                wepmode = WEPMODE_40BIT;
            } else {
                iprintf("Invalid key!\n");
            }
        }
        Wifi_ConnectAP(ap, wepmode, 0, (u8*)wepkey);
    } else {
        Wifi_ConnectAP(ap, WEPMODE_NONE, 0, 0);
    }
    consoleClear();

    while(status != ASSOCSTATUS_ASSOCIATED && status != ASSOCSTATUS_CANNOTCONNECT) {
        status = Wifi_AssocStatus();
        int len = strlen(ASSOCSTATUS_STRINGS[status]);
        iprintf("\x1b[0;0H\x1b[K");
        iprintf("\x1b[0;%dH%s\n", (32-len)/2,ASSOCSTATUS_STRINGS[status]);

        swiWaitForVBlank();
    }

    return status == ASSOCSTATUS_ASSOCIATED;
}

Gamestate runWifi(int *socketfd, struct sockaddr_in *sain) {
	consoleDemoInit();

    iprintf("Connecting...\n");
    if (*socketfd != -1) {
        iprintf("Already connected\n");

        while (1) {
            swiWaitForVBlank();
            scanKeys();
            int keys = keysDown();
            if (keys & KEY_START) return TITLE_SCREEN;
        }
    }

#if 0
    if (!Wifi_InitDefault(WFC_CONNECT)) {
#else
	Wifi_InitDefault(false);

    if (!connectToAP(findAP())) {
#endif
        iprintf("Failed to connect\n");

        *socketfd = -1;

        while (1) {
            swiWaitForVBlank();
            scanKeys();
            int keys = keysDown();
            if (keys & KEY_START) return TITLE_SCREEN;
        }
    }
    else {
        iprintf("Connected to WiFi\n");

        *socketfd = socket(AF_INET, SOCK_DGRAM, 0);

        sain->sin_family = AF_INET;
        sain->sin_port = htons(PORT);
        if (inet_aton(SERVER, &sain->sin_addr) == 0) {
            iprintf("Failed aton\n");
        }

        u8 n = 0;
        u8 m = 0;
        while (1) {
            if (n <= 0) {
                iprintf("Sending message to server...\n(B to cancel)\n");

                Packet p = {.pressedKeys = 0x2000, .tx = 0, .ty = 0, .frame = 0};
                sendto(*socketfd, &p, sizeof(p), 0, (struct sockaddr *) sain, sizeof(*sain));

                fd_set readfds;
                struct timeval timeout = {.tv_sec = 2, .tv_usec = 0};
                int len;

                FD_ZERO(&readfds);
                FD_SET(*socketfd, &readfds);
                u8 read = select(*socketfd+1, &readfds, NULL, NULL, &timeout);

                if (read == 1) {
                    len = sizeof(sain);
                    n = recvfrom(*socketfd, &p, sizeof(p), 0, (struct sockaddr *) sain, &len);

                    if (n > 0) {
                        if (p.pressedKeys == 0x2000 && p.tx == 0 && p.ty == 0 && p.frame == 0) {
                            return GAMEPLAY;
                        }
                    }
                }
            }

            swiWaitForVBlank();
            scanKeys();
            int keys = keysDown();
            if (keys & KEY_B) {
                shutdown(*socketfd, SHUT_RDWR);
                *socketfd = -1;
                Wifi_DisconnectAP();
                return TITLE_SCREEN;
            }
        }
    }
}
