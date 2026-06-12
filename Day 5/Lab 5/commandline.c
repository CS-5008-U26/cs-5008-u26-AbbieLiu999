# include <stdio.h>

int main (int argc, char **argv) {
    if (argc > 1) {
        char s[1000];
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("Could not open filename %s", argv[1]);
            return 1;
        }
        while (fgets(s, 1000, fp) != NULL) {
            printf("%s\n", s);
        }
        fclose(fp);
    }
    return 0;
}