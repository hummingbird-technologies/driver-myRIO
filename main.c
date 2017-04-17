#include <stdio.h>

#include "MyRio.h"
#include "digital_input.h"

int main(int argc, char **argv)
{
    status_t status;
    struct digital_input_t d;
    digital_input_init(&d, 35);

    status = device_setup();
    if (status != status_ok) {
        return status;
    }

    printf("Reading: %d\n", digital_input_read(&d));

    return device_teardown();
}
