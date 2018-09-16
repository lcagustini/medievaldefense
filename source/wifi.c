#define SERVER "179.111.136.156"
#define PORT 8888

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

    if (!Wifi_InitDefault(WFC_CONNECT)) {
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
        iprintf("Connected to wifi\n");

        *socketfd = socket(AF_INET, SOCK_DGRAM, 0);

        sain->sin_family = AF_INET;
        sain->sin_port = htons(PORT);
        if (inet_aton(SERVER, &sain->sin_addr) == 0) {
            iprintf("Failed aton\n");
        }

        u8 n = 0;
        while (1) {
            if (n <= 0) {
                Packet p = {.pressedKeys = 0x2000, .tx = 0, .ty = 0, .frame = 0};
                sendto(*socketfd, &p, sizeof(p), 0, (struct sockaddr *) sain, sizeof(*sain));

                fd_set readfds;
                struct timeval timeout = {.tv_sec = 2, .tv_usec = 0};
                int len;

                FD_ZERO(&readfds);
                FD_SET(*socketfd, &readfds);
                u8 read = select(*socketfd+1, &readfds, NULL, NULL, &timeout);

                if (read == 1) {
                    n = recvfrom(*socketfd, &p, sizeof(p), 0, (struct sockaddr *) sain, &len);

                    if (n > 0) {
                        if (p.pressedKeys == 0x2000 && p.tx == 0 && p.ty == 0 && p.frame == 0) {
                            iprintf("Connected to server\n");
                        }
                        else {
                            iprintf("Failed to connect to server\n");

                            shutdown(*socketfd, SHUT_RDWR);
                            *socketfd = -1;
                        }
                    }
                }
            }

            swiWaitForVBlank();
            scanKeys();
            int keys = keysDown();
            if (keys & KEY_START) return TITLE_SCREEN;
        }
    }
}
