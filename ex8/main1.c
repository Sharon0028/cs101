#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    FILE *fp = fopen("lotto.txt", "r");
    int win_nums[3];
    printf("請輸入中獎號碼三個：");
    scanf("%d %d %d", &win_nums[0], &win_nums[1], &win_nums[2]);

    printf("輸入中獎號碼為：%02d %02d %02d\n", win_nums[0], win_nums[1], win_nums[2]);

    char line[128];
    char date_line[64] = "";
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "March") || strstr(line, "Jan") || strstr(line, "Feb") ||
            strstr(line, "Apr") || strstr(line, "May") || strstr(line, "Jun") ||
            strstr(line, "Jul") || strstr(line, "Aug") || strstr(line, "Sep") ||
            strstr(line, "Oct") || strstr(line, "Nov") || strstr(line, "Dec")) {
            strcpy(date_line, line);
        }

        if (line[0] == '[' && line[2] == ']') {
            int lotto[7];
            int matched = 0;

            sscanf(line, "[%*d]: %d %d %d %d %d %d %d",
                   &lotto[0], &lotto[1], &lotto[2], &lotto[3],
                   &lotto[4], &lotto[5], &lotto[6]);
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 3; j++) {
                    if (lotto[i] == win_nums[j]) {
                        matched++;
                    }
                }
            }

            if (matched >= 3) {
                if (!found) {
                    printf("以下為中獎彩卷：\n");
                    printf("售出時間：%s", date_line);
                }
                printf("%s", line);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("很遺憾，沒有中獎。\n");
    }

    fclose(fp);
    return 0;
}
