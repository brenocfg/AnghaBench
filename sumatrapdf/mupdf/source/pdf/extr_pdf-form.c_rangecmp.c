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
struct TYPE_2__ {scalar_t__ offset; } ;
typedef  TYPE_1__ fz_range ;

/* Variables and functions */

__attribute__((used)) static int rangecmp(const void *a_, const void *b_)
{
	const fz_range *a = (const fz_range *) a_;
	const fz_range *b = (const fz_range *) b_;
	return (int) (a->offset - b->offset);
}