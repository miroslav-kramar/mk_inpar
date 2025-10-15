#include <stdio.h>
#include <stdbool.h>
#include "../mk_inpar.h"

int main() {
    const char * fname = "e03.csv";
    FILE * fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Failed to open file %s!\n", fname);
        return -1;
    }

    printf("Scanning file...\n");
    mk_scanner_t sc = mk_scanner_create(fp, ",");
    int a[4], b[4], c[4], d[4];
    bool success = true;

    for (int i = 0; i < 4; i++) {
        a[i] = mk_scanner_get_i32(&sc);
        b[i] = mk_scanner_get_i32(&sc);
        c[i] = mk_scanner_get_i32(&sc);
        d[i] = mk_scanner_get_i32(&sc);
        
        const mk_status_t status = mk_scanner_get_status(&sc);
        if (status == MK_STATUS_STREAM_EOF) {
            break;
        }
        else if (status != MK_STATUS_OK) {
            printf("ERROR: %s\n", mk_status_get_message(status));
            success = false;
            break;
        }
    }

    if (success) {
        printf("File scanned successfully.\n");
        for (int i = 0; i < 4; i++) {
            printf("a[%d] = %d\n", i, a[i]);
            printf("b[%d] = %d\n", i, b[i]);
            printf("c[%d] = %d\n", i, c[i]);
            printf("d[%d] = %d\n", i, d[i]);
            printf("\n");
        }
    }

    fclose(fp);
    printf("File %s closed.\n", fname);
    return 0;
}