// 包含头文件
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jfif.h"
#include "bmp.h"

int main(int argc, char *argv[])
{
    void *jfif = NULL;
    BMP   bmp  = {0};
    int quality;
    char *p;
    char filename[50];

    if (argc < 3) {
        printf(
            "jfif test program\n"
            "usage: %s -d filename decode jpg file to decode.bmp\n"
            "       %s -e filename encode bmp file to encode.jpg\n",
            argv[0], argv[0]
        );
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0) {
        jfif = jfif_load(argv[2]);
        jfif_decode(jfif, &bmp);
        jfif_free  (jfif);
        bmp_save(&bmp, "decode.bmp");
        bmp_free(&bmp);
    } else if (strcmp(argv[1], "-e") == 0) {
        if (argc < 4){
            quality = 50;
        }
        else{
            quality = (int) strtol(argv[3], &p, 10);
        }
        printf("quality: %d\n", quality);
        bmp_load(&bmp, argv[2]);
        jfif = jfif_encode(&bmp, quality);
        bmp_free(&bmp);
        sprintf(filename, "encode_%d.jpg", quality);
        jfif_save(jfif, filename);
        jfif_free(jfif);
    }

    return 0;
}

