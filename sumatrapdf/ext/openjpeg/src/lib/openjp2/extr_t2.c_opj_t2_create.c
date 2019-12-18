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
struct TYPE_3__ {int /*<<< orphan*/ * cp; int /*<<< orphan*/ * image; } ;
typedef  TYPE_1__ opj_t2_t ;
typedef  int /*<<< orphan*/  opj_image_t ;
typedef  int /*<<< orphan*/  opj_cp_t ;

/* Variables and functions */
 scalar_t__ opj_calloc (int,int) ; 

opj_t2_t* opj_t2_create(opj_image_t *p_image, opj_cp_t *p_cp)
{
    /* create the t2 structure */
    opj_t2_t *l_t2 = (opj_t2_t*)opj_calloc(1, sizeof(opj_t2_t));
    if (!l_t2) {
        return NULL;
    }

    l_t2->image = p_image;
    l_t2->cp = p_cp;

    return l_t2;
}