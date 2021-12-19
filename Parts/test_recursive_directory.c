#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*#define PATH "/home/kali/Music/dossier_manipulable/"*/
/*mettre en place des couleurs pour les fichiers et une autre pour les dossiers*/

void show_dir_content(char *path)
{
    DIR *d = opendir(path);
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
            sprintf(new_path, "%s/%s", path, directory ->d_name);
            printf("\n%s\n", new_path);
            printf("%s is a directory\n",directory ->d_name);
            show_dir_content(new_path);
        }
    }
    closedir(d);
}

int main(int argc, char **argv)
{
    show_dir_content(argv[1]);
}