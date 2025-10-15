#include <stdio.h>
#include "../mk_inpar.h"

int main() {
    mk_scanner_t sc = mk_scanner_create_default();
    printf("Enter a number. Enter 0 to exit.\n");
    printf("> ");
    while (1) {
        int n = mk_scanner_get_i32(&sc);
        mk_status_t status = mk_scanner_get_status(&sc);
        if (status != MK_STATUS_OK) {
            printf("ERROR: %s\n", mk_status_get_message(status));
            mk_scanner_clear_status(&sc);
            mk_scanner_clear_input(&sc);
        }
        else if (n == 0) {
            printf("Bye!\n");
            break;
        }
        else {
            printf("%d\n", n);
        }

        if (mk_scanner_newline_found(&sc)) {
            printf("> ");
        }
    }
    return 0;
}