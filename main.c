#include <stdio.h>
#include <unistd.h>

#include "MyRio.h"
#include "digital_input.h"
#include "quadrature_encoder.h"


int main(int argc, char **argv)
{
    status_t status;
    struct digital_input_t di;
    struct quadrature_encoder_t qe;

    digital_input_init(&di, 35);
    quadrature_encoder_init(&qe, 0);

    status = device_setup();
    if (status != status_ok) {
        return status;
    }

//    struct digital_input_run_args_t ra = {&di, 10};
//    digital_input_run(&ra);

    device_run();
    sleep(2);

    quadrature_encoder_update(&qe);
    printf("Reading: %d\n", qe.value);

    return device_teardown();
}
