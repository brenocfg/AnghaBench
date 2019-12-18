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
struct bio {int dummy; } ;
struct TYPE_4__ {int dr_bio_count; int /*<<< orphan*/ ** dr_bio; scalar_t__ dr_error; int /*<<< orphan*/  dr_ref; } ;
typedef  TYPE_1__ dio_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dio_request_t *
vdev_disk_dio_alloc(int bio_count)
{
	dio_request_t *dr;
	int i;

	dr = kmem_zalloc(sizeof (dio_request_t) +
	    sizeof (struct bio *) * bio_count, KM_SLEEP);
	if (dr) {
		atomic_set(&dr->dr_ref, 0);
		dr->dr_bio_count = bio_count;
		dr->dr_error = 0;

		for (i = 0; i < dr->dr_bio_count; i++)
			dr->dr_bio[i] = NULL;
	}

	return (dr);
}