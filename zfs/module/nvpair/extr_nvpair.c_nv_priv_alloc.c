#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpriv_t ;
struct TYPE_7__ {TYPE_1__* nva_ops; } ;
typedef  TYPE_2__ nv_alloc_t ;
struct TYPE_6__ {int /*<<< orphan*/ * (* nv_ao_alloc ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nv_priv_init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static nvpriv_t *
nv_priv_alloc(nv_alloc_t *nva)
{
	nvpriv_t *priv;

	/*
	 * nv_mem_alloc() cannot called here because it needs the priv
	 * argument.
	 */
	if ((priv = nva->nva_ops->nv_ao_alloc(nva, sizeof (nvpriv_t))) == NULL)
		return (NULL);

	nv_priv_init(priv, nva, 0);

	return (priv);
}