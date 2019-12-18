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
struct winlinks {int dummy; } ;
struct winlink {int idx; } ;

/* Variables and functions */
 struct winlink* RB_FIND (int /*<<< orphan*/ ,struct winlinks*,struct winlink*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  winlinks ; 

struct winlink *
winlink_find_by_index(struct winlinks *wwl, int idx)
{
	struct winlink	wl;

	if (idx < 0)
		fatalx("bad index");

	wl.idx = idx;
	return (RB_FIND(winlinks, wwl, &wl));
}