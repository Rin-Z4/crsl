#include <limits.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char uchar;

void _fwrite(const void *ptr, size_t num, FILE *stream, uchar *err) {
    size_t num_written = fwrite(ptr, 1, num, stream);

    if (num_written != num)
        *err = 1;
}

void s_fwrite(const char *str, FILE *stream, uchar *err) {
    _fwrite(str, strlen(str), stream, err);
}


int main(int argc, char **argv) {
    FILE *fout = NULL;
    uchar err = 0; /* 0 or 1 */

    (void) argc;
    (void) argv;

    if (CHAR_BIT < 8)
        return 1;

    fout = fopen("detected_types.h", "w");
    if (fout == NULL)
        return 1;

    do {
        s_fwrite("#ifndef __CRSL_DETECTED_TYPES_H\n", fout, &err);
        if (err != 0) break;
        s_fwrite("#define __CRSL_DETECTED_TYPES_H\n", fout, &err);
        if (err != 0) break;
        s_fwrite("\n", fout, &err);
        if (err != 0) break;

        s_fwrite("#define CHAR_BYTES ", fout, &err);
        if (err != 0) break;
        if (fprintf(fout, "%lu\n", sizeof(char)) < 2) { /* At least one digit and \n */
            err = 1;
            break;
        }

        s_fwrite("#define SHORT_BYTES ", fout, &err);
        if (err != 0) break;
        if (fprintf(fout, "%lu\n", sizeof(short)) < 2) {
            err = 1;
            break;
        }

        s_fwrite("#define INT_BYTES ", fout, &err);
        if (err != 0) break;
        if (fprintf(fout, "%lu\n", sizeof(int)) < 2) {
            err = 1;
            break;
        }

        s_fwrite("#define LONG_BYTES ", fout, &err);
        if (err != 0) break;
        if (fprintf(fout, "%lu\n", sizeof(long)) < 2) {
            err = 1;
            break;
        }

        s_fwrite("\n", fout, &err);
        if (err != 0) break;
        s_fwrite("#endif\n", fout, &err);
    } while(0);

    if ((fclose(fout) != 0) || (err != 0)) {
        (void)(remove("detected_types.h")); /* We don't care if it fails */
        return 1;
    }

    return 0;
}
