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
typedef  int /*<<< orphan*/  XImage ;
struct TYPE_2__ {scalar_t__ lastused; int /*<<< orphan*/ ** pool; int /*<<< orphan*/  display; scalar_t__ useshm; } ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ POOLSIZE ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ info ; 

__attribute__((used)) static XImage *
next_pool_image(void)
{
	if (info.lastused + 1 >= POOLSIZE) {
		if (info.useshm)
			XSync(info.display, False);
		else
			XFlush(info.display);
		info.lastused = 0;
	}
	return info.pool[info.lastused ++];
}