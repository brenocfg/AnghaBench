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
 unsigned int opj_bio_getbit (int /*<<< orphan*/ *) ; 

OPJ_UINT32 opj_bio_read(opj_bio_t *bio, OPJ_UINT32 n)
{
    OPJ_INT32 i;
    OPJ_UINT32 v;

    assert((n > 0U) /* && (n <= 32U)*/);
#ifdef OPJ_UBSAN_BUILD
    /* This assert fails for some corrupted images which are gracefully rejected */
    /* Add this assert only for ubsan build. */
    /* This is the condition for overflow not to occur below which is needed because of OPJ_NOSANITIZE */
    assert(n <= 32U);
#endif
    v = 0U;
    for (i = (OPJ_INT32)n - 1; i >= 0; i--) {
        v |= opj_bio_getbit(bio) <<
             i; /* can't overflow, opj_bio_getbit returns 0 or 1 */
    }
    return v;
}