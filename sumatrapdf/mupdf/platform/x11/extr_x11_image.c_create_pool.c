#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  visual; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** pool; TYPE_1__ visual; int /*<<< orphan*/ * shminfo; int /*<<< orphan*/  display; scalar_t__ lastused; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIGHT ; 
 int POOLSIZE ; 
 int /*<<< orphan*/  WIDTH ; 
 int /*<<< orphan*/ * createximage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ info ; 

__attribute__((used)) static int
create_pool(void)
{
	int i;

	info.lastused = 0;

	for (i = 0; i < POOLSIZE; i++) {
		info.pool[i] = NULL;
	}

	for (i = 0; i < POOLSIZE; i++) {
		info.pool[i] = createximage(info.display,
			info.visual.visual, &info.shminfo[i], info.visual.depth,
			WIDTH, HEIGHT);
		if (!info.pool[i]) {
			return 0;
		}
	}

	return 1;
}