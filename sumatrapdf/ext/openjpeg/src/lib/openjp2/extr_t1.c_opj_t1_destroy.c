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
struct TYPE_4__ {int data; int flags; struct TYPE_4__* cblkdatabuffer; int /*<<< orphan*/  encoder; } ;
typedef  TYPE_1__ opj_t1_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_aligned_free (int) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 

void opj_t1_destroy(opj_t1_t *p_t1)
{
    if (! p_t1) {
        return;
    }

    /* encoder uses tile buffer, so no need to free */
    if (!p_t1->encoder && p_t1->data) {
        opj_aligned_free(p_t1->data);
        p_t1->data = 00;
    }

    if (p_t1->flags) {
        opj_aligned_free(p_t1->flags);
        p_t1->flags = 00;
    }

    opj_free(p_t1->cblkdatabuffer);

    opj_free(p_t1);
}