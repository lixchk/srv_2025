#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>

#define EOK 0

void server(void) {
    int rcvid, chid;
    char message[512], response[512];

    printf("Server started\n");
    chid = ChannelCreate(0);
    printf("Channel ID: %d\n", chid);
    printf("Server PID: %d\n", getpid());

    while(1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        printf("Received: %s\n", message);

        int a, b;
        char op;
        if(sscanf(message, "%d%c%d", &a, &op, &b) == 3) {
            int result;
            switch(op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if(b != 0) result = a / b; break;
                default:
                    strcpy(response, "Invalid operator!!!");
                    MsgReply(rcvid, EOK, response, strlen(response)+1);
                    continue;
            }
            snprintf(response, sizeof(response), "%d", result);
        } else {
            strcpy(response, "Check the format!!!");
        }

        MsgReply(rcvid, EOK, response, strlen(response)+1);
    }
}

int main(void) {
    server();
    return 0;
}
