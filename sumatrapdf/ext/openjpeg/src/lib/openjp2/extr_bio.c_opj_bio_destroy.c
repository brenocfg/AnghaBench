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
typedef  int /*<<< orphan*/  opj_bio_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (int /*<<< orphan*/ *) ; 

void opj_bio_destroy(opj_bio_t *bio)
{
    if (bio) {
        opj_free(bio);
    }
}