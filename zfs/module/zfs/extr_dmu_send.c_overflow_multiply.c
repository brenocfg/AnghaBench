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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 

__attribute__((used)) static inline boolean_t
overflow_multiply(uint64_t a, uint64_t b, uint64_t *c)
{
	uint64_t temp = a * b;
	if (b != 0 && temp / b != a)
		return (B_FALSE);
	*c = temp;
	return (B_TRUE);
}