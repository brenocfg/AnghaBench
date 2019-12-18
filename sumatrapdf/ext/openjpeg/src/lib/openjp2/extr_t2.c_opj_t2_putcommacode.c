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
typedef  scalar_t__ OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_bio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void opj_t2_putcommacode(opj_bio_t *bio, OPJ_INT32 n)
{
    while (--n >= 0) {
        opj_bio_write(bio, 1, 1);
    }
    opj_bio_write(bio, 0, 1);
}