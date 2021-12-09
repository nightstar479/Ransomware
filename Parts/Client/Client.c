#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>


/*struct sockaddr_in{
    short               sin_family;
    unsigned short      sin_port;
    struct in_addr      sin_addr;
    char                sin_zero[8];
};
struct in_addr{
    unsigned long s_addr;
};*/
/*int bind(int socket, const struct sockaddr *address,
            socklen_t adress_len);*/

int main(int argc, char *argv[]){

    int sockid;
    int server_port = strtol(argv[2], NULL, 10);
    char *server_ip = argv[3];

    sockid = socket(AF_INET,SOCK_DGRAM,0);



    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    /*int bind_result = bind(sockid, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if(bind_result<0){
        printf("Error during binding\n");
    }
    else{
        printf("Sending on %s:%d\n", server_ip,server_port);
    }*/

    char *msg = argv[1];

    sendto(sockid,(const char * )msg,strlen(msg),
            0,(const struct sockaddr*) &server_addr,sizeof(server_addr));
    
    close(sockid);

}
