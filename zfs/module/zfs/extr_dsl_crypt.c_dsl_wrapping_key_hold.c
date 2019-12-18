#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wk_refcnt; } ;
typedef  TYPE_1__ dsl_wrapping_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
dsl_wrapping_key_hold(dsl_wrapping_key_t *wkey, void *tag)
{
	(void) zfs_refcount_add(&wkey->wk_refcnt, tag);
}