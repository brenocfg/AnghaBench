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
typedef  int /*<<< orphan*/  mod_hash_t ;
typedef  scalar_t__ mod_hash_hndl_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mh_e_cache ; 

void
mod_hash_cancel(mod_hash_t *hash, mod_hash_hndl_t *handlep)
{
	kmem_cache_free(mh_e_cache, *handlep);
	*handlep = (mod_hash_hndl_t)0;
}