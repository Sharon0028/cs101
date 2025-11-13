#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_lotto(); 
void check_lotto();    

int main() {
    generate_lotto();
    check_lotto();
    return 0;
}

void generate_lotto() {
    FILE* fp = fopen("lotto.txt", "w");
    if (!fp) {
        printf("無法開啟 lotto.txt\n");
        exit(1);
    }

    int N;
    printf("請輸入要產生的樂透組數 (1~5)：");
    scanf("%d", &N);

    fprintf(fp, "========= lotto649 =========\n");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_str[64];
    strftime(date_str, sizeof(date_str), "%B %d %Y", t);
    fprintf(fp, "======= %s =======\n", date_str);

    srand((unsigned)time(NULL));
    int nums[7];

    for (int g = 0; g < N; g++) {
        fprintf(fp, "[%d]: ", g + 1);
        for (int i = 0; i < 7; i++) {
            nums[i] = rand() % 69 + 1;
            for (int j = 0; j < i; j++) {
                if (nums[i] == nums[j]) {
                    i--;
                    break;
                }
            }
        }
        for (int i = 0; i < 7; i++) {
            if (i > 0) fprintf(fp, " ");
            fprintf(fp, "%02d", nums[i]);
        }
        fprintf(fp, "\n");
    }

    for (int k = N + 1; k <= 5; k++)
        fprintf(fp, "[%d]: __ __ __ __ __ __ __\n", k);

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);
    printf("已產生 lotto.txt 檔案！\n\n");
}

void check_lotto() {
    FILE *fp = fopen("lotto.txt", "r");
    if (!fp) {
        printf("找不到 lotto.txt 檔案！\n");
        exit(1);
    }

    int win[3];
    printf("請輸入中獎號碼三個：");
    scanf("%d %d %d", &win[0], &win[1], &win[2]);
    printf("輸入中獎號碼為：%02d %02d %02d\n", win[0], win[1], win[2]);

    char line[256], date_line[256] = "";
    int lotto[7];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "=======", 7) == 0 && strstr(line, "20") != NULL) {
            char* start = line;
            while (*start == '=' || *start == ' ') start++; 
            char* end = line + strlen(line) - 1;
            while (end > start && (*end == '=' || *end == ' ' || *end == '\n')) {
                *end = 0;
                end--;
            }
            strcpy(date_line, start);
        }

        if (line[0] == '[') {
            int n;
            int count = sscanf(line, "[%d]: %d %d %d %d %d %d %d",
                               &n, &lotto[0], &lotto[1], &lotto[2],
                               &lotto[3], &lotto[4], &lotto[5], &lotto[6]);
            if (count != 8) continue; 

            int matched = 0;
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 3; j++)
                    if (lotto[i] == win[j])
                        matched++;

            if (matched > 0) { 
                printf("售出時間：%s:%s", date_line, line);
                found = 1;
            }
        }
    }

    if (!found)
        printf("查無中獎彩卷。\n");

    fclose(fp);
}
