#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>

int main(void) {
    char expression[50], response[512];
    int coid;
    long serv_pid;

    printf("Enter server PID: ");
    scanf("%ld", &serv_pid);

    coid = ConnectAttach(0, serv_pid, 1, 0, 0);
    if(coid == -1) {
        perror("ConnectAttach");
        return EXIT_FAILURE;
    }

    printf("Enter your expression without spaces: ");
    scanf("%s", expression);

    if(MsgSend(coid, expression, strlen(expression)+1, response, sizeof(response)) == -1) {
        perror("MsgSend");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", response);
    ConnectDetach(coid);
    return EXIT_SUCCESS;
}
