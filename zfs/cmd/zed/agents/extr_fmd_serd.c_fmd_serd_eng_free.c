#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sg_list; struct TYPE_5__* sg_name; } ;
typedef  TYPE_1__ fmd_serd_eng_t ;

/* Variables and functions */
 int /*<<< orphan*/  fmd_serd_eng_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fmd_serd_eng_free(fmd_serd_eng_t *sgp)
{
	fmd_serd_eng_reset(sgp);
	free(sgp->sg_name);
	list_destroy(&sgp->sg_list);
	free(sgp);
}