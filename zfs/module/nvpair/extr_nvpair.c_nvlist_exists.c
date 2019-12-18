#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* nvp_list; } ;
typedef  TYPE_1__ nvpriv_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_6__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_2__ nvlist_t ;
struct TYPE_7__ {int /*<<< orphan*/  nvi_nvp; struct TYPE_7__* nvi_next; } ;
typedef  TYPE_3__ i_nvp_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  NVP_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

boolean_t
nvlist_exists(nvlist_t *nvl, const char *name)
{
	nvpriv_t *priv;
	nvpair_t *nvp;
	i_nvp_t *curr;

	if (name == NULL || nvl == NULL ||
	    (priv = (nvpriv_t *)(uintptr_t)nvl->nvl_priv) == NULL)
		return (B_FALSE);

	for (curr = priv->nvp_list; curr != NULL; curr = curr->nvi_next) {
		nvp = &curr->nvi_nvp;

		if (strcmp(name, NVP_NAME(nvp)) == 0)
			return (B_TRUE);
	}

	return (B_FALSE);
}