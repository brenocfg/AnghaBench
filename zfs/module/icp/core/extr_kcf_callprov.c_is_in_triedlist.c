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
typedef  int /*<<< orphan*/  kcf_provider_desc_t ;
struct TYPE_3__ {struct TYPE_3__* pt_next; int /*<<< orphan*/ * pt_pd; } ;
typedef  TYPE_1__ kcf_prov_tried_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 

__attribute__((used)) static boolean_t
is_in_triedlist(kcf_provider_desc_t *pd, kcf_prov_tried_t *triedl)
{
	while (triedl != NULL) {
		if (triedl->pt_pd == pd)
			return (B_TRUE);
		triedl = triedl->pt_next;
	};

	return (B_FALSE);
}