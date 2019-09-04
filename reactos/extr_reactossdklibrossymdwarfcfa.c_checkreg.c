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
struct TYPE_3__ {long nr; } ;
typedef  TYPE_1__ State ;

/* Variables and functions */
 int /*<<< orphan*/  werrstr (char*,long) ; 

__attribute__((used)) static int
checkreg(State *s, long r)
{
	if(r < 0 || r >= s->nr){
		werrstr("bad register number 0x%lux", r);
		return -1;
	}
	return 0;
}