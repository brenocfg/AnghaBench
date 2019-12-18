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
struct _buf {int /*<<< orphan*/  vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOP_CLOSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct _buf*) ; 

void
kobj_close_file(struct _buf *file)
{
	VOP_CLOSE(file->vp, 0, 0, 0, 0, 0);
	kfree(file);
}