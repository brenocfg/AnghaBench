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
typedef  unsigned int OPJ_UINT32 ;
typedef  unsigned int OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  opj_bio_putbit (int /*<<< orphan*/ *,unsigned int) ; 

void opj_bio_write(opj_bio_t *bio, OPJ_UINT32 v, OPJ_UINT32 n)
{
    OPJ_INT32 i;

    assert((n > 0U) && (n <= 32U));
    for (i = (OPJ_INT32)n - 1; i >= 0; i--) {
        opj_bio_putbit(bio, (v >> i) & 1);
    }
}