#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct uart_softc {void* dlh; void* dll; } ;

/* Variables and functions */
 int DEFAULT_BAUD ; 
 int DEFAULT_RCLK ; 
 int /*<<< orphan*/  rxfifo_reset (struct uart_softc*,int) ; 

__attribute__((used)) static void
uart_reset(struct uart_softc *sc)
{
	uint16_t divisor;

	divisor = DEFAULT_RCLK / DEFAULT_BAUD / 16;
	sc->dll = (uint8_t) divisor;
	sc->dlh = (uint8_t) (divisor >> 16);

	rxfifo_reset(sc, 1);	/* no fifo until enabled by software */
}