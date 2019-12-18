#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  os_release; int /*<<< orphan*/  machine_info; int /*<<< orphan*/  hostname; TYPE_1__* partitions; } ;
struct TYPE_7__ {int /*<<< orphan*/  decrypted_node; int /*<<< orphan*/  decrypted_fstype; int /*<<< orphan*/  node; int /*<<< orphan*/  fstype; } ;
typedef  TYPE_2__ DissectedImage ;

/* Variables and functions */
 unsigned int _PARTITION_DESIGNATOR_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

DissectedImage* dissected_image_unref(DissectedImage *m) {
        unsigned i;

        if (!m)
                return NULL;

        for (i = 0; i < _PARTITION_DESIGNATOR_MAX; i++) {
                free(m->partitions[i].fstype);
                free(m->partitions[i].node);
                free(m->partitions[i].decrypted_fstype);
                free(m->partitions[i].decrypted_node);
        }

        free(m->hostname);
        strv_free(m->machine_info);
        strv_free(m->os_release);

        return mfree(m);
}