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
struct TYPE_2__ {scalar_t__ link_attributes; } ;
struct rb_redcarpet_rndr {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_gc_mark (scalar_t__) ; 

__attribute__((used)) static void rb_redcarpet_rbase_mark(struct rb_redcarpet_rndr *rndr)
{
	if (rndr->options.link_attributes)
		rb_gc_mark(rndr->options.link_attributes);
}