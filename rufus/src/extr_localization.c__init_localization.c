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
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  LOC_HTAB_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  htab_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_loc ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* loc_dlg ; 
 int /*<<< orphan*/  locale_list ; 
 int /*<<< orphan*/  localization_initialized ; 

void _init_localization(BOOL reinit) {
	size_t i;
	for (i=0; i<ARRAYSIZE(loc_dlg); i++)
		list_init(&loc_dlg[i].list);
	if (!reinit)
		list_init(&locale_list);
	htab_create(LOC_HTAB_SIZE, &htab_loc);
	localization_initialized = TRUE;
}