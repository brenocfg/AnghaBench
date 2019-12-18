#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct super_block {TYPE_1__* s_fs_info; } ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */

__attribute__((used)) static int
zpl_test_super(struct super_block *s, void *data)
{
	zfsvfs_t *zfsvfs = s->s_fs_info;
	objset_t *os = data;

	if (zfsvfs == NULL)
		return (0);

	return (os == zfsvfs->z_os);
}