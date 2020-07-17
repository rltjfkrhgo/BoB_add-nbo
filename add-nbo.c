// add-nbo.c

#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
    FILE*  bin1 = NULL;
    FILE*  bin2 = NULL;
    
    uint32_t  nbo1 = 0;  // network byte order
    uint32_t  nbo2 = 0;  // network byte order
    uint32_t  hbo1 = 0;  // host byte order
    uint32_t  hbo2 = 0;  // host byte order
    
    if(argc != 3)
    {
        printf("usage: %s <file1> <file2>\n", argv[0]);
        return 0;
    }
    
    // 두 개의 파일 오픈
    bin1 = fopen(argv[1], "rb");
    bin2 = fopen(argv[2], "rb");
    
    if(bin1 == NULL || bin2 == NULL)
    {
        fprintf(stderr, "file open Error!!\n");
        return -1;
    }
    
    // network byte order로 4바이트 숫자 두 개를 읽는다.
    fread(&nbo1, sizeof(nbo1), 1, bin1);
    fread(&nbo2, sizeof(nbo2), 1, bin2);
    
    // host byte order로 바꾼다!
    hbo1 = ntohl(nbo1);
    hbo2 = ntohl(nbo2);
    
    // 출력!
    printf("%d(0x%02x) + %d(0x%02x) = %d(0x%02x)\n",
           hbo1, hbo1, hbo2, hbo2, hbo1+hbo2, hbo1+hbo2);
    
    // 파일 닫기
    fclose(bin2);
    fclose(bin1);
    
    return 0;
}