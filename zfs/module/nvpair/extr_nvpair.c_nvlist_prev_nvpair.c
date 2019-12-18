#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* nvp_curr; TYPE_3__* nvp_last; } ;
typedef  TYPE_1__ nvpriv_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_8__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_2__ nvlist_t ;
struct TYPE_9__ {int /*<<< orphan*/  nvi_nvp; struct TYPE_9__* nvi_prev; } ;
typedef  TYPE_3__ i_nvp_t ;

/* Variables and functions */
 TYPE_3__* NVPAIR2I_NVP (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_contains_nvp (TYPE_2__*,int /*<<< orphan*/ *) ; 

nvpair_t *
nvlist_prev_nvpair(nvlist_t *nvl, nvpair_t *nvp)
{
	nvpriv_t *priv;
	i_nvp_t *curr;

	if (nvl == NULL ||
	    (priv = (nvpriv_t *)(uintptr_t)nvl->nvl_priv) == NULL)
		return (NULL);

	curr = NVPAIR2I_NVP(nvp);

	if (nvp == NULL)
		curr = priv->nvp_last;
	else if (priv->nvp_curr == curr || nvlist_contains_nvp(nvl, nvp))
		curr = curr->nvi_prev;
	else
		curr = NULL;

	priv->nvp_curr = curr;

	return (curr != NULL ? &curr->nvi_nvp : NULL);
}