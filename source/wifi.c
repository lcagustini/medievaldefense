#define SERVER "179.111.136.156"
#define PORT 8888

Gamestate runWifi(int *socketfd, struct sockaddr_in *sain) {
    if(!Wifi_InitDefault(WFC_CONNECT)) {
        PRINT("Failed to connect!\n");

        *socketfd = -1;
    }
    else {
        PRINT("Connected to wifi\n");

        *socketfd = socket(AF_INET, SOCK_DGRAM, 0);
        fcntl(*socketfd, F_SETFL, O_NONBLOCK);

        sain->sin_family = AF_INET;
        sain->sin_port = htons(PORT);
        if (inet_aton(SERVER, &sain->sin_addr) == 0) {
            PRINT("Failed aton\n");
        }

        Packet p = {.pressedKeys = 0x2000, .tx = 0, .ty = 0, .frame = 0};
        sendto(*socketfd, &p, sizeof(p), 0, (struct sockaddr *) sain, sizeof(*sain));
    }

    while (1) {
        swiWaitForVBlank();
        scanKeys();
        int keys = keysDown();
        if (keys & KEY_START) return TITLE_SCREEN;
    }
}
