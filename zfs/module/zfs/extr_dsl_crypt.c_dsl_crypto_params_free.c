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
struct TYPE_4__ {int /*<<< orphan*/ * cp_wkey; int /*<<< orphan*/ * cp_keylocation; } ;
typedef  TYPE_1__ dsl_crypto_params_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_wrapping_key_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spa_strfree (int /*<<< orphan*/ *) ; 

void
dsl_crypto_params_free(dsl_crypto_params_t *dcp, boolean_t unload)
{
	if (dcp == NULL)
		return;

	if (dcp->cp_keylocation != NULL)
		spa_strfree(dcp->cp_keylocation);
	if (unload && dcp->cp_wkey != NULL)
		dsl_wrapping_key_free(dcp->cp_wkey);

	kmem_free(dcp, sizeof (dsl_crypto_params_t));
}