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
typedef  scalar_t__ uchar_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ U8_COMBINING_CLASS_STARTER ; 

__attribute__((used)) static boolean_t
blocked(uchar_t *comb_class, size_t last)
{
	uchar_t my_comb_class;
	size_t i;

	my_comb_class = comb_class[last];
	for (i = 1; i < last; i++)
		if (comb_class[i] >= my_comb_class ||
		    comb_class[i] == U8_COMBINING_CLASS_STARTER)
			return (B_TRUE);

	return (B_FALSE);
}