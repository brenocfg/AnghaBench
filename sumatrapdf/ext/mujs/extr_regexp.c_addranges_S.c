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
struct cstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addrange (struct cstate*,int,int) ; 

__attribute__((used)) static void addranges_S(struct cstate *g)
{
	addrange(g, 0, 0x9-1);
	addrange(g, 0xD+1, 0x20-1);
	addrange(g, 0x20+1, 0xA0-1);
	addrange(g, 0xA0+1, 0x2028-1);
	addrange(g, 0x2029+1, 0xFEFF-1);
	addrange(g, 0xFEFF+1, 0xFFFF);
}