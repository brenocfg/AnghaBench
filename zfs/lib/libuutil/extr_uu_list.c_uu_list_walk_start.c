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
typedef  int /*<<< orphan*/  uu_list_walk_t ;
typedef  int /*<<< orphan*/  uu_list_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  UU_ERROR_UNKNOWN_FLAG ; 
 int UU_WALK_REVERSE ; 
 int UU_WALK_ROBUST ; 
 int /*<<< orphan*/  list_walk_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uu_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uu_zalloc (int) ; 

uu_list_walk_t *
uu_list_walk_start(uu_list_t *lp, uint32_t flags)
{
	uu_list_walk_t *wp;

	if (flags & ~(UU_WALK_ROBUST | UU_WALK_REVERSE)) {
		uu_set_error(UU_ERROR_UNKNOWN_FLAG);
		return (NULL);
	}

	wp = uu_zalloc(sizeof (*wp));
	if (wp == NULL) {
		uu_set_error(UU_ERROR_NO_MEMORY);
		return (NULL);
	}

	list_walk_init(wp, lp, flags);
	return (wp);
}