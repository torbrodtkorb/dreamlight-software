/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "startup.h"
#include "types.h"
#include "led_driver.h"
#include "gpio.h"
#include "sleep.h"
#include "print.h"


int main(void)
{
	startup();

    while (1) {
		print("tor");
		
    }
}


