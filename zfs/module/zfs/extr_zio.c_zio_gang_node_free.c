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
struct TYPE_4__ {int /*<<< orphan*/  gn_gbh; int /*<<< orphan*/ ** gn_child; } ;
typedef  TYPE_1__ zio_gang_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_GANGBLOCKSIZE ; 
 int SPA_GBH_NBLKPTRS ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zio_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zio_gang_node_free(zio_gang_node_t **gnpp)
{
	zio_gang_node_t *gn = *gnpp;

	for (int g = 0; g < SPA_GBH_NBLKPTRS; g++)
		ASSERT(gn->gn_child[g] == NULL);

	zio_buf_free(gn->gn_gbh, SPA_GANGBLOCKSIZE);
	kmem_free(gn, sizeof (*gn));
	*gnpp = NULL;
}