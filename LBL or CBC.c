#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "time_functions.h"

void charByChar();
void lineByLine();

int main() { 
    int choice;
    printf("Project 1\n");

    printf("This program will read and write a text file in 2 different ways\n");
    while (1) {
        printf("-----------------------------------\n");
        printf("    0 --> Character by Character   \n");
        printf("    1 --> Line by Line             \n");
        printf("    2 --> Exit Program             \n");
        printf("-----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
        case 0: 
            charByChar();
            break;
        case 1: 
            lineByLine();
            break;
        case 2: 
            printf("The progam will now conclude...");
            return 0;
        }
    }
}

void charByChar(){ 
    char *ch;
    size_t n = 0;
    int c;
#ifdef _WIN32
    printf("Windows\n"); 
    FILE *Rfile = fopen("C:\\temp\\in.txt", "r");    //input windows file location here
    FILE *Wfile = fopen("C:\\temp\\out.txt", "w");   //output windows file location here
#elif __linux__
    printf("Linux\n");
    FILE *Rfile = fopen("~/temp/in.txt", "r");       //input linux file location here
    FILE *Wfile = fopen("~/temp/out.txt", "w");      //output linux file location here
#else 
#error "Please use a Linux or Windows System\n"
#endif

    if (Rfile == NULL) {
        printf("The file you selected is empty\n");
        return;
    }

    fseek(Rfile, 0, SEEK_END);
    long f_size = ftell(Rfile);
    fseek(Rfile, 0, SEEK_SET);
    ch = (char*)malloc(f_size);
    
    start_timing();
    while ((c = fgetc(Rfile)) != EOF) {
        ch[n++] = (char)c;
        putc(c, Wfile);
    }
    stop_timing();
    double wall_time = get_wall_clock_diff() * 1000.0;
    double exe_time = get_nanodiff() / 1000000.0;
    printf("\n\nReal Time: %fms\n", wall_time);
    printf("Execution Time: %fms\n", exe_time);

    fclose(Rfile);
    fclose(Wfile);
}

void lineByLine() {
    char *line = NULL;
    size_t read, length = 0;

#ifdef _WIN32
    printf("Windows\n"); 
    FILE *Rfile = fopen("C:\\temp\\coursein\\p1-in.txt", "r");
    FILE *Wfile = fopen("C:\\temp\\courseout\\p1-out.txt", "w");
#elif __linux__
    printf("Linux\n");
    FILE *Rfile = fopen("~/temp/coursein/p1-in.txt", "r");
    FILE *Wfile = fopen("~/temp/courseout/p1-out.txt", "w");
#else 
#error "Please use a Linux or Windows System\n"
#endif   
    
    if (Rfile == NULL) {
        printf("The file you selected is empty\n");
        return;
    }

    start_timing();
    while ((read = getline(&line, &length, Rfile)) != -1) fputs(line, Wfile);
    stop_timing();
    double wall_time = get_wall_clock_diff() * 1000.0;
    double exe_time = get_nanodiff() / 1000000.0;
    printf("\n\nReal Time: %fms\n", wall_time);
    printf("Execution Time: %fms\n", exe_time);
    
    fclose(Rfile);
    fclose(Wfile);
}
