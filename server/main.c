#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdint.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
 
typedef struct {
    uint16_t pressedKeys;
    uint8_t tx;
    uint8_t ty;
    uint16_t frame;
} Packet;

void die(char *s) {
    perror(s);
    exit(1);
}
 
int main(void) {
    struct sockaddr_in si_me, si_other;
    struct sockaddr_in si_players[2];
    int playerCount = 0;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    Packet p;
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if (bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
        die("bind");
    }
     
    //keep listening for data
    while (1) {
        printf("Waiting for data...");
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, &p, sizeof(p), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

        if (p.pressedKeys == 0x2000 && !p.tx && !p.ty && !p.frame) {
            if ((!playerCount) || (playerCount == 1 && si_players[0].sin_port != si_other.sin_port)) {
                si_players[playerCount] = si_other;
                playerCount++;
                printf("Connected Player\n");
                printf("Player count: %d\n", playerCount);

                if (playerCount == 2) {
                    sendto(s, &p, sizeof(p), 0, (struct sockaddr*) &si_players[1], slen); 
                    sendto(s, &p, sizeof(p), 0, (struct sockaddr*) &si_players[0], slen); 
                    printf("Starting Match\n");
                }
            }
            else {
                p.tx = p.ty = 1;
                sendto(s, &p, sizeof(p), 0, (struct sockaddr*) &si_other, slen);
                printf("Denied Player\n");
            }
        }
        else if (playerCount == 2) {
            printf("Data: %d %d %d %d\n", p.pressedKeys, p.tx, p.ty, p.frame);

            if (si_players[0].sin_port == si_other.sin_port) {
                sendto(s, &p, sizeof(p), 0, (struct sockaddr*) &si_players[1], slen); 
            }
            else if (si_players[1].sin_port == si_other.sin_port) {
                sendto(s, &p, sizeof(p), 0, (struct sockaddr*) &si_players[0], slen); 
            }
        }

#if 0
        //now reply the client with the same data
        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1) {
            die("sendto()");
        }
#endif
    }
 
    close(s);
    return 0;
}
