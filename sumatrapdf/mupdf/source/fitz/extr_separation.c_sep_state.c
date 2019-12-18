#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* state; } ;
typedef  TYPE_1__ fz_separations ;
typedef  int /*<<< orphan*/  fz_separation_behavior ;

/* Variables and functions */

__attribute__((used)) static inline fz_separation_behavior
sep_state(const fz_separations *sep, int i)
{
	return (fz_separation_behavior)((sep->state[i>>5]>>((2*i) & 31)) & 3);
}