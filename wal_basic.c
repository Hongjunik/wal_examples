#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "date.txt"
#define WAL_FILE "wal.log"

//WAL 기록 함수
void write_ahead_log(const char *operation, const char *date) {
    FILE *wal = fopen(WAL_FILE, "a");
    if (!wal)
    {
        perror("WAL file open failed");
        exit(1);
    }
    fprintf(wal, "%s:%s\n", operation, date);
    fclose(wal);
}

// 실제 데이터 반영 함수
void apply_date(const char *date) {
    FILE *dataFile = fopen(DATA_FILE, "a");
    if (!dataFile)
    {
        perror("Date file open failed");
        exit(1);
    }
    fprintf(dataFile, "%s\n", date);
    fclose(dataFile);
}

// main
int main()
{
    char input[100];
    printf("Enter new date to write: ");
    scanf("%s", input);

    write_ahead_log("INSERT", input);
    printf("WAL updateed successfully.\n");

    apply_date(input);
    printf("Date file updated successfully.\n");
    
    return 0;
}
