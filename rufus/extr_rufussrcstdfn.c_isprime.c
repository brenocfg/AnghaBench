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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t isprime(uint32_t number)
{
	// no even number will be passed
	uint32_t divider = 3;

	while((divider * divider < number) && (number % divider != 0))
		divider += 2;

	return (number % divider != 0);
}