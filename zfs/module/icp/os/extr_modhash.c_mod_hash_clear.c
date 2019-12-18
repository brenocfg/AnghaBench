#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mh_contents; } ;
typedef  TYPE_1__ mod_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  i_mod_hash_clear_nosync (TYPE_1__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

void
mod_hash_clear(mod_hash_t *hash)
{
	ASSERT(hash);
	rw_enter(&hash->mh_contents, RW_WRITER);
	i_mod_hash_clear_nosync(hash);
	rw_exit(&hash->mh_contents);
}