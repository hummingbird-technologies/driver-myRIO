#include <stdio.h>
#include <unistd.h>

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

    struct digital_input_run_args_t ra = {&d, 10};
    digital_input_run(&ra);

    device_run();
    sleep(2);

    return device_teardown();
}
