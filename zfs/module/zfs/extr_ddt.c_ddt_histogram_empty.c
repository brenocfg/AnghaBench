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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ddt_histogram_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 

boolean_t
ddt_histogram_empty(const ddt_histogram_t *ddh)
{
	const uint64_t *s = (const uint64_t *)ddh;
	const uint64_t *s_end = (const uint64_t *)(ddh + 1);

	while (s < s_end)
		if (*s++ != 0)
			return (B_FALSE);

	return (B_TRUE);
}