#include "shell.h"

/**
 * permission printer 
 */
void print_permissions(mode_t mode) {
    char permissions[11];

    permissions[0] = (S_ISDIR(mode)) ? 'd' : '-';
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    printf("%s ", permissions);
}

/**
 * change directory
 */
int own_cd(char **args) {
    if (args[1] == NULL) {
        printf("cd: missing argument\n");
        return EXIT_SUCCESS;
    }
    if (chdir(args[1]) != 0) {
        perror("cd");
    }
    return EXIT_SUCCESS;
}

/**
 * list directory contents
 */
int own_ls(char **args) {

    int long_format = 0;
    char *directory = ".";

    // get arguments
    for (int i = 1; args[i] != NULL; i++) {
        if (strcmp(args[i], "-l") == 0) {
            long_format = 1;
        } else {
            directory = args[i];
        }
    }

    // open directory, retrn exit code if failed
    DIR *d = opendir(directory);
    if (d == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // print directory contents with long format
    // 
    struct dirent *dir;
    if (long_format) {
        struct stat file_stat;
        struct passwd *pwd;
        struct group *grp;
        char timebuf[80];
        char path[1024];

        while ((dir = readdir(d)) != NULL) {
            if (dir->d_name[0] == '.') {
                continue;
            }

            snprintf(path, sizeof(path), "%s/%s", directory, dir->d_name);
            if (stat(path, &file_stat) == 0) {

                // print file permissions
                print_permissions(file_stat.st_mode);

                // print number of hard links
                printf("%hu ", file_stat.st_nlink);

                // print owner and group
                pwd = getpwuid(file_stat.st_uid);
                grp = getgrgid(file_stat.st_gid);
                printf("%s %s ", pwd->pw_name, grp->gr_name);

                // print file size
                printf("%5lld ", file_stat.st_size);

                // print last modified time
                strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                printf("%s ", timebuf);

                // print file name
                printf("%s\n", dir->d_name);
            } else {
                perror("stat");
            }
        }
    } 
    // print directory contents
    else {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_name[0] == '.') {
                continue;
            }
            printf("%s\n", dir->d_name);
        }
    }

    closedir(d);

    return EXIT_SUCCESS;
}

/**
 * print help   
 */
int own_help(char **args) {
    if (args[1] != NULL) {
        printf("help: too many arguments\n");
        return EXIT_FAILURE;
    }

    printf("BASH_ir Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    printf("  ls\n");
    printf("  cd\n");
    printf("  env\n");
    printf("  help\n");
    printf("  exit\n");
    return EXIT_SUCCESS;
}

/**
 * exit
 */
int own_exit(char **args) {
    // your probably wondering why im returning EXIT_FAILURE here
    // this is because we only want to exit the shell if the user types exit by itself
    // if the user types exit with any arguments, we want to return EXIT_FAILURE
    // so the shell does not exit
    if (args[1] != NULL) {
        printf("exit: too many arguments\n");
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE; 
}