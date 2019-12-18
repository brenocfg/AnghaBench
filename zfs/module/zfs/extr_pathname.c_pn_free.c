#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pathname {scalar_t__ pn_pathlen; int /*<<< orphan*/ * pn_path; scalar_t__ pn_bufsize; int /*<<< orphan*/ * pn_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,scalar_t__) ; 

void
pn_free(struct pathname *pnp)
{
	/* pn_bufsize is usually MAXPATHLEN, but may not be */
	kmem_free(pnp->pn_buf, pnp->pn_bufsize);
	pnp->pn_buf = NULL;
	pnp->pn_bufsize = 0;
#if 0 /* unused in ZoL */
	pnp->pn_path = NULL;
	pnp->pn_pathlen = 0;
#endif
}