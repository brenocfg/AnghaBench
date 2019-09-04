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

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/ * size2mask ; 

uint64_t
vie_size2mask(int size)
{
	KASSERT(size == 1 || size == 2 || size == 4 || size == 8,
	    ("vie_size2mask: invalid size %d", size));
	return (size2mask[size]);
}