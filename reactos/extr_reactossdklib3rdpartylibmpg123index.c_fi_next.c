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
struct frame_index {int step; scalar_t__ fill; } ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static off_t fi_next(struct frame_index *fi)
{
	return (off_t)fi->fill*fi->step;
}