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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_hash_destroy_hash (int /*<<< orphan*/ *) ; 

void
mod_hash_destroy_ptrhash(mod_hash_t *hash)
{
	ASSERT(hash);
	mod_hash_destroy_hash(hash);
}