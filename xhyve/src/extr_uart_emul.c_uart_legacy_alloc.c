#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int inuse; int baseaddr; int irq; } ;

/* Variables and functions */
 unsigned int UART_NLDEVS ; 
 TYPE_1__* uart_lres ; 

int
uart_legacy_alloc(int which, int *baseaddr, int *irq)
{

	if ((which < 0) || (((unsigned) which) >= UART_NLDEVS) ||
		uart_lres[which].inuse)
	{
		return (-1);
	}

	uart_lres[which].inuse = true;
	*baseaddr = uart_lres[which].baseaddr;
	*irq = uart_lres[which].irq;

	return (0);
}