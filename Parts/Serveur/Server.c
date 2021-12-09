#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include<time.h>
#define BUFFER_SIZE 1024

int bind(int socket, const struct sockaddr *address,
            socklen_t adress_len);

int main(int argc, char *argv[]){

    int nbr_msg = strtol(argv[1], NULL, 10);

    int sockid;
    int server_port = 50000;
    char *server_ip = "192.168.1.8";
    //char *client_addr = "";

    sockid = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    time_t t;   
    time(&t);

    

    char *buffer[BUFFER_SIZE];
    int n,len;
    
    int bind_result = bind(sockid, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    FILE * fileptr;
    fileptr =fopen("passwords.txt", "a");

    if(fileptr == NULL){
        printf("Erreur durant la création du document.\n");
        exit(EXIT_FAILURE);
    }

     if(bind_result<0){
        printf("Error during binding\n");
    }
    else{
        printf("Listening on %s:%d\n", server_ip,server_port);
        for(int i=0;i<nbr_msg;i++){
            
            len = sizeof(client_addr);

            n= recvfrom(sockid,(char *) buffer, BUFFER_SIZE,
                    MSG_WAITALL, (struct sockaddr *) &client_addr,&len);

            printf("%s Message reçu de taille %d par [%s:%d]: %s\n",ctime(&t),n, // Message reçu de taille (en bits), par [ip:port]: (message)
                    inet_ntoa(client_addr.sin_addr),
                    client_addr.sin_port,
                    buffer);
            fprintf(fileptr,"%s Message reçu de taille %d par [%s:%d]: %s\n",ctime(&t),n, // Message reçu de taille (en bits), par [ip:port]: (message)
                    inet_ntoa(client_addr.sin_addr),
                    client_addr.sin_port,
                    buffer);
          
        }
        fclose(fileptr);
    };

    close(sockid);
}
