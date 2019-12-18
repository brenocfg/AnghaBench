#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  nvp_nva; } ;
typedef  TYPE_1__ nvpriv_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_STAT_EMBEDDED ; 
 TYPE_1__* nv_mem_zalloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  nv_priv_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static nvpriv_t *
nv_priv_alloc_embedded(nvpriv_t *priv)
{
	nvpriv_t *emb_priv;

	if ((emb_priv = nv_mem_zalloc(priv, sizeof (nvpriv_t))) == NULL)
		return (NULL);

	nv_priv_init(emb_priv, priv->nvp_nva, NV_STAT_EMBEDDED);

	return (emb_priv);
}