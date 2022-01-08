#include <stdio.h>
#include <string.h>

int is_encrypted(char *filename){
    printf("%s\n",filename);

    char *extension = strchr(filename, '.');
    char to_compare[]=".enc";
    if(strcmp(extension,to_compare)==0){
        return 1;
    }
   else{
       return 0;
   }
};
int main(void){
    
    printf("%d",is_encrypted("file.enc"));
    
}