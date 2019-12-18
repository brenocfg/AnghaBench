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
struct TYPE_4__ {int /*<<< orphan*/  f_vnode; int /*<<< orphan*/  f_file; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vn_file_cache ; 
 int /*<<< orphan*/  vn_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void releasef_locked(file_t *fp)
{
	ASSERT(fp->f_file);
	ASSERT(fp->f_vnode);

	/* Unlinked from list, no refs, safe to free outside mutex */
	fput(fp->f_file);
	vn_free(fp->f_vnode);

	kmem_cache_free(vn_file_cache, fp);
}