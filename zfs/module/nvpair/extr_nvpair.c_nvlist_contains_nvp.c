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

/* Variables and functions */

__attribute__((used)) static int
nvlist_contains_nvp(nvlist_t *nvl, nvpair_t *nvp)
{
	nvpriv_t *priv = (nvpriv_t *)(uintptr_t)nvl->nvl_priv;
	i_nvp_t *curr;

	if (nvp == NULL)
		return (0);

	for (curr = priv->nvp_list; curr != NULL; curr = curr->nvi_next)
		if (&curr->nvi_nvp == nvp)
			return (1);

	return (0);
}