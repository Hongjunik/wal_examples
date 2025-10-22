#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *fin = fopen("input.txt", "r");
    if(!fin){
        perror("fopen input.txt");
        return 1;
    }

    int x, sum = 0;
    while (fscanf(fin, "%d", &x) == 1){
        sum+=x;
    }
    fclose(fin);

    FILE *fout = fopen("output.txt", "w");
    if(!fout){
        perror("fopen output.txt");
        return 1;
    }

    fprintf(fout, "%d\n", sum);
    fclose(fout);

    printf("SUM written to output.txt: %d\n", sum);

    return 0;
}
