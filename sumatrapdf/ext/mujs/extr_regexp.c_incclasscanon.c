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
struct TYPE_3__ {scalar_t__* end; scalar_t__* spans; } ;
typedef  scalar_t__ Rune ;
typedef  TYPE_1__ Reclass ;

/* Variables and functions */
 scalar_t__ canon (scalar_t__) ; 

__attribute__((used)) static int incclasscanon(Reclass *cc, Rune c)
{
	Rune *p, r;
	for (p = cc->spans; p < cc->end; p += 2)
		for (r = p[0]; r <= p[1]; ++r)
			if (c == canon(r))
				return 1;
	return 0;
}