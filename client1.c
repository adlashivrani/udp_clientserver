#include "header.h"

int main()
{
    int sfd;//socket descriptor
    struct sockaddr_in server;
    char send[SIZE];
	char receive[SIZE];
    int len = sizeof(server);
    
    // Clean buffers:
    memset(send, 0, sizeof(send));
    memset(receive, 0, sizeof(receive));
    
    // Create socket:
    if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error while creating socket\n");
        exit(1);
    }
    printf("\nSocket created successfully\n");
    
    // Set port and IP:
    server.sin_family = AF_INET; //address family
    server.sin_port = htons(PORT);//converting from little endian to big endian
    server.sin_addr.s_addr = inet_addr("127.0.0.2"); //loopback ip
    
    // Get input from the user:
    printf("\nEnter message: ");
    fgets(send, SIZE, stdin);
    
    // Send the message to server:
    if(sendto(sfd, send, strlen(send), 0,(struct sockaddr*)&server, len) < 0){
        printf("Unable to send message\n");
        exit(1);
    }
    
    // Receive the server's response:
    if(recvfrom(sfd, receive, sizeof(receive), 0,(struct sockaddr*)&server, &len) < 0){
        printf("Error while receiving server's msg\n");
        exit(1);
    }
    
    printf("Server's response: %s\n", receive);
    
    // Close the socket:
    close(sfd);
    return 0;
}

