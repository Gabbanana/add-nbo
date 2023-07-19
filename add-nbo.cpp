#include <stdio.h>
#include <stdint.h>

uint32_t read_uint32_from_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return 0;
    }

    uint32_t number;
    fread(&number, sizeof(uint32_t), 1, file);
    fclose(file);

    number = (number >> 24) | ((number << 8) & 0x00FF0000) | ((number >> 8) & 0x0000FF00) | (number << 24);

    return number;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("사용법: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    uint32_t num1 = read_uint32_from_file(argv[1]);
    uint32_t num2 = read_uint32_from_file(argv[2]);

    uint32_t sum = num1 + num2;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", (int)num1, num1, (int)num2, num2, (int)sum, sum);

    return 0;
}

