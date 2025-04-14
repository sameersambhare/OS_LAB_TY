#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("You can not enter more or less than 3 arguments.");
        return 0;
        }
        char* fn;
        char* pat;
        char line[5000];
        FILE* fp;
        char* match;
        pat = argv[1];
        fn = argv[2];
        fp = open(fn, O_RDONLY);
        while(!feof(fp)) {
            fgets(line, 5000, fp);
            match = strstr(line, pat);
            if(match) {
                *match = '\0';
                printf("%s", line);
                printf("\033[31m%s\033[0m", pat);
                printf("%s", match + strlen(pat));
            }
        }
    close(fp);
    return 0;
}
