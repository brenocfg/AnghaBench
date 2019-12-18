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
typedef  int /*<<< orphan*/  zstream_t ;
struct TYPE_4__ {int /*<<< orphan*/ * zf_dnode; int /*<<< orphan*/  zf_lock; int /*<<< orphan*/  zf_stream; } ;
typedef  TYPE_1__ zfetch_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_zfetch_stream_remove (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dmu_zfetch_fini(zfetch_t *zf)
{
	zstream_t *zs;

	mutex_enter(&zf->zf_lock);
	while ((zs = list_head(&zf->zf_stream)) != NULL)
		dmu_zfetch_stream_remove(zf, zs);
	mutex_exit(&zf->zf_lock);
	list_destroy(&zf->zf_stream);
	mutex_destroy(&zf->zf_lock);

	zf->zf_dnode = NULL;
}