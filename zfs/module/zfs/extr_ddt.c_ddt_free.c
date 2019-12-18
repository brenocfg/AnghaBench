#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dde_cv; int /*<<< orphan*/ * dde_repair_abd; int /*<<< orphan*/ ** dde_lead_zio; int /*<<< orphan*/  dde_loading; } ;
typedef  TYPE_1__ ddt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DDT_PHYS_TYPES ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_entry_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
ddt_free(ddt_entry_t *dde)
{
	ASSERT(!dde->dde_loading);

	for (int p = 0; p < DDT_PHYS_TYPES; p++)
		ASSERT(dde->dde_lead_zio[p] == NULL);

	if (dde->dde_repair_abd != NULL)
		abd_free(dde->dde_repair_abd);

	cv_destroy(&dde->dde_cv);
	kmem_cache_free(ddt_entry_cache, dde);
}