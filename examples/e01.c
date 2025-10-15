#include <stdio.h>
#include "../mk_inpar.h"

int main() {
    // Create scanner object
    mk_scanner_t sc = mk_scanner_create_default();

    printf("Please enter a positive number:\n");

    // Scan for a 32-bit unsigned integer
    unsigned int n = mk_scanner_get_u32(&sc);

    // Get the status code of last scanning
    const mk_status_t status = mk_scanner_get_status(&sc);

    if (status == MK_STATUS_OK) {
        printf("Entered number: %d\n", n);
    }
    else {
        // Get textual representation of status code
        printf("ERROR: %s\n", mk_status_get_message(status));
    }
    return 0;
}