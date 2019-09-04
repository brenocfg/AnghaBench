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
typedef  scalar_t__ paddr_t ;

/* Variables and functions */
 scalar_t__ BAUDHIGH ; 
 scalar_t__ BAUDLOW ; 
 scalar_t__ LCR ; 
 int /*<<< orphan*/  SetPhysByte (scalar_t__,int) ; 
 int /*<<< orphan*/  sync () ; 

void setup(char *serport, int baud) {
	int x = 115200 / baud;
	SetPhysByte((paddr_t)serport+LCR, 128);
	sync();
	SetPhysByte((paddr_t)serport+BAUDLOW, x & 255);
	sync();
	SetPhysByte((paddr_t)serport+BAUDHIGH, x >> 8);
	sync();
	SetPhysByte((paddr_t)serport+LCR, 3);
	sync();
}