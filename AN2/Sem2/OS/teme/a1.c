#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

void list(const char *path, int recursive, int smaller_value, int has_perm_execute, int lvl)
{
    
    DIR *directory = opendir(path);
    printf("%s",path);
    struct dirent *d;
    if (directory != NULL)
    {

	    if (!lvl)
	     printf("SUCCESS\n");
	    d = readdir(directory);
	while (d != NULL)
	{
	    if (strcmp(d->d_name, ".") && strcmp(d->d_name, ".."))
	    {
		    char *file_path = (char *)malloc((strlen(path) + 1) * sizeof(char) + sizeof(char) + (strlen(d->d_name) + 1) * sizeof(char));
		    sprintf(file_path, "%s/%s", path, d->d_name);
		if (recursive)
		    list(file_path, recursive, smaller_value, has_perm_execute, 1);
		    printf("%s\n", file_path);
		if (file_path != NULL)
		    free(file_path);
	    }
	    d = readdir(directory);
	}
	closedir(directory);
    }
    else if (!lvl)
	printf("ERROR\ninvalid directory path\n");

}

int main(int argc, char **argv){
    if(argc >= 2){
        char *path = NULL, *size_smaller = NULL;
    	int recursive = 0, size_smaller_value = 0, has_perm_execute = 0, op = 0;

        if(strcmp(argv[1], "variant") == 0){
            printf("98835\n");
        }

        for(int i = 1 ; i < argc ; i++)
        {
            if(strstr(argv[i], "path="))
            {
                path = (char*)malloc((strlen(argv[i]) - 4) * sizeof(char));
                strcpy(path, argv[i]+20);
                printf("%s", path);
                FILE *f = fopen("test.txt","rw");
            }

             if(strstr(argv[i], "size_smaller="))
            {
                size_smaller = (char*)malloc((strlen(argv[i]) - 12) * sizeof(char));
                strcpy(size_smaller, argv[i]+13);
                size_smaller_value = atoi(size_smaller);
                printf("%d", size_smaller_value);
            }
            if (strstr(argv[i], "has_perm_execute"))
		        has_perm_execute = 1;

            if (strstr(argv[i], "recursive"))
		        recursive = 1;

            if (strstr(argv[i], "list"))
		        op = 1;

        }

        if (op == 1)
	        list(path, recursive, size_smaller_value, has_perm_execute, 0);
    }
    return 0;
}