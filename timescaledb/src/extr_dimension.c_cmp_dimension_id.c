#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ id; } ;
struct TYPE_4__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ Dimension ;

/* Variables and functions */

__attribute__((used)) static int
cmp_dimension_id(const void *left, const void *right)
{
	const Dimension *diml = (Dimension *) left;
	const Dimension *dimr = (Dimension *) right;

	if (diml->fd.id < dimr->fd.id)
		return -1;

	if (diml->fd.id > dimr->fd.id)
		return 1;

	return 0;
}