#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_8__ {int i_buffer; scalar_t__ p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_CopyProperties (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *S32toFl64(filter_t *filter, block_t *bsrc)
{
    block_t *bdst = block_Alloc(bsrc->i_buffer * 2);
    if (unlikely(bdst == NULL))
        goto out;

    block_CopyProperties(bdst, bsrc);
    int32_t *src = (int32_t*)bsrc->p_buffer;
    double  *dst = (double *)bdst->p_buffer;
    for (size_t i = bsrc->i_buffer / 4; i--;)
        *dst++ = (double)(*src++) / 2147483648.;
out:
    VLC_UNUSED(filter);
    block_Release(bsrc);
    return bdst;
}