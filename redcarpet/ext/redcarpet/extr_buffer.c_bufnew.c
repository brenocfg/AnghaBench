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
struct buf {size_t unit; scalar_t__ asize; scalar_t__ size; scalar_t__ data; } ;

/* Variables and functions */
 struct buf* malloc (int) ; 

struct buf *
bufnew(size_t unit)
{
	struct buf *ret;
	ret = malloc(sizeof (struct buf));

	if (ret) {
		ret->data = 0;
		ret->size = ret->asize = 0;
		ret->unit = unit;
	}
	return ret;
}