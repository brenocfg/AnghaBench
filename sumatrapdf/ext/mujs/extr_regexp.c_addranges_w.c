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
 int /*<<< orphan*/  addrange (struct cstate*,char,char) ; 

__attribute__((used)) static void addranges_w(struct cstate *g)
{
	addrange(g, '0', '9');
	addrange(g, 'A', 'Z');
	addrange(g, '_', '_');
	addrange(g, 'a', 'z');
}