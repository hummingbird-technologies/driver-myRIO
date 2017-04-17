/*
 * Copyright (c) 2015,
 * National Instruments Corporation.
 * All rights reserved.
 */

#include <stdio.h>

#include "MyRio.h"
#include "digital_input.h"

int main(int argc, char **argv)
{
    NiFpga_Status status;
    struct digital_input_t d;

    status = MyRio_Open();
    MyRio_ReturnStatusIfNotSuccess(status, "Could not open myRIO session.");

    digital_input_init(&d, 35);
    d.setup();

    printf("Reading: %d\n", digital_input_read(&d));

    status = MyRio_Close();
    return status;
}
