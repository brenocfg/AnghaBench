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
typedef  int /*<<< orphan*/  uf_info_t ;
struct task_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  f_list; int /*<<< orphan*/  f_ref; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* file_find (int,struct task_struct*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releasef_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_file_lock ; 

void
vn_areleasef(int fd, uf_info_t *fip)
{
	file_t *fp;
	struct task_struct *task = (struct task_struct *)fip;

	if (fd < 0)
		return;

	spin_lock(&vn_file_lock);
	fp = file_find(fd, task);
	if (fp) {
		atomic_dec(&fp->f_ref);
		if (atomic_read(&fp->f_ref) > 0) {
			spin_unlock(&vn_file_lock);
			return;
		}

		list_del(&fp->f_list);
		releasef_locked(fp);
	}
	spin_unlock(&vn_file_lock);
}