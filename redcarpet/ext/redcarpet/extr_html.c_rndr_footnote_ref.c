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
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufprintf (struct buf*,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int
rndr_footnote_ref(struct buf *ob, unsigned int num, void *opaque)
{
	bufprintf(ob, "<sup id=\"fnref%d\"><a href=\"#fn%d\">%d</a></sup>", num, num, num);
	return 1;
}