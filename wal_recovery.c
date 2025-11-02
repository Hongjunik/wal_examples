#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WAL_FILE "wal.log"
#define DATA_FILE "data.txt"

// WAL 기록 함수
void write_ahead_log(const char *data) {
    FILE *wal = fopen(WAL_FILE, "a");
    if (!wal) {
        perror("WAL open failed");
        exit(1);
    }
    fprintf(wal, "%s\n", data);
    fclose(wal);
}

// 실제 데이터 반영
void apply_data(const char *data) {
    FILE *db = fopen(DATA_FILE, "a");
    if (!db) {
        perror("Data file open failed");
        exit(1);
    }
    fprintf(db, "%s\n", data);
    fclose(db);
}

// 로그 기반 복구
void recover() {
    FILE *wal = fopen(WAL_FILE, "r");
    if (!wal) return; // 로그 없으면 복구 없음

    char buffer[256];
    printf("[RECOVERY] WAL log found. Restoring...\n");

    while (fgets(buffer, sizeof(buffer), wal)) {
        buffer[strcspn(buffer, "\n")] = 0;
        apply_data(buffer);
        printf("Restored: %s\n", buffer);
    }

    fclose(wal);
    remove(WAL_FILE);
    printf("[RECOVERY COMPLETED] WAL cleared.\n\n");
}

int main() {
    recover();

    char input[100];
    printf("새로운 데이터를 입력하세요: ");
    scanf("%s", input);

    write_ahead_log(input);
    printf("[WAL 기록 완료]\n");

    apply_data(input);
    printf("[데이터 반영 완료]\n");

    return 0;
}
