#include <stdio.h>
#include <string.h>

int is_encrypted(char *filename){

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
int main(void){
    
    printf("%d",is_encrypted("file"));
    
}