#include "header.h"

int main()
{
    int sfd;
    struct sockaddr_in server;
	struct sockaddr_in client;
    char send[SIZE];
	char receive[SIZE];
    int len = sizeof(client);
    
    // Clean buffers:
    memset(send, 0, sizeof(send));
    memset(receive, 0, sizeof(receive));
    
    // Create UDP socket:
    if ( (sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error while creating socket\n");
        exit(1);
    }
    printf("Socket created successfully\n");
    
    // Set port and IP:
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    
    // Bind to the set port and IP:
    if ((bind(sfd, (struct sockaddr*)&server,sizeof(server))) < 0){
        printf("Couldn't bind to the port\n");
       	exit(1);
    }
    printf("Done with binding\n");
    printf("Listening for incoming messages...\n\n");
    while (1) { //putting server in active state
	bzero(send, SIZE);
	bzero(receive, SIZE);
    // Receive client's message:
    if (recvfrom(sfd, receive, sizeof(receive), 0, (struct sockaddr*)&client, &len) < 0) {
        printf("Couldn't receive\n");
        exit(1);
    }

    printf("\nReceived message from IP: %s\n",inet_ntoa(client.sin_addr));//converting ip from pointer to string
    printf("Message from client: %s\n", receive);
    
    // Respond to client:
    printf("send response to client:-\n");
	fgets(send, SIZE, stdin);
    if (sendto(sfd, send, strlen(send), 0,(struct sockaddr*)&client, len) < 0){
        printf("Can't send\n");
        exit(1);
    }
      
	}
    return 0;
}
