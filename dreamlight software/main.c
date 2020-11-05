/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "watchdog.h"
#include "flash.h"
#include "clock.h"
#include "gpio.h"
#include "sleep.h"
#include "print.h"
#include "gmalloc.h"
#include "led_driver.h"
#include "engine.h"
#include "list.h"

#define LED_CNT 50

/// Early initialization for the CPU
void early_init(void) 
{
	watchdog_disable();
	
	// Set flash wait states according to the CPU frequency
	flash_set_accsess_cycles(7);
	
	// Set system clock
	clock_source_enable(CRYSTAL_OCILLATOR, 0xFF);
	main_clock_select(CRYSTAL_OCILLATOR);
	plla_setup(25, 1, 0xFF);
	master_clock_config(PLLA_CLOCK, NO_PRES, DIV2);
	
	// Initialize the malloc
	gmalloc_init();
}

/// Initializes the drivers
void driver_init(void) 
{
	// Enable button
	gpio_set_function(PIOC, 8, FUNCTION_GPIO);
	gpio_set_direction(PIOC, 8, GPIO_OUTPUT);
	gpio_clear(PIOC, 8);
	
	// Enable delay
	sleep_init();
	
	// Enable console print
	print_init();
		
	// Enable the led strip
	led_strip_init();
}

struct pixel led_strip[LED_CNT];

struct graphics_engine e;

struct name {
	char* name;
	
	struct list_node node;
};

/// Main entry point
int main(void)
{
	early_init();
	driver_init();
	
	struct list_node list;
	list_init(&list);
	
	struct name name1 = { .name = "tor" };
	struct name name2 = { .name = "elsker" };
	struct name name3 = { .name = "mange" };
	struct name name4 = { .name = "lys" };
	
	list_insert_first(&name1.node, &list);
	list_insert_first(&name2.node, &list);
	list_insert_first(&name3.node, &list);
	list_insert_first(&name4.node, &list);
	
	struct list_node* it;
	
	list_iterate(it, &list) {
		struct name* name = list_get_entry(it, struct name, node);
		print(name->name);
		print(" ");
	}
	
	// =====================================
	// Test code for the graphics engine
	// =====================================
	engine_init(&e);
	
	e.update(&e);
	
	while (1) {
		
	
	}
}


