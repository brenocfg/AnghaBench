#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zap_avl; } ;
struct TYPE_5__ {TYPE_1__ zap_m; } ;
typedef  TYPE_2__ zap_t ;
typedef  int /*<<< orphan*/  mzap_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mze_destroy(zap_t *zap)
{
	mzap_ent_t *mze;
	void *avlcookie = NULL;

	while ((mze = avl_destroy_nodes(&zap->zap_m.zap_avl, &avlcookie)))
		kmem_free(mze, sizeof (mzap_ent_t));
	avl_destroy(&zap->zap_m.zap_avl);
}