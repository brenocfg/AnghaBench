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
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DecodeBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  decoder_QueueSub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DecodeSubtitle(decoder_t *dec, block_t *block)
{
    block_t **block_ptr = block ? &block : NULL;
    subpicture_t *spu;
    while ((spu = DecodeBlock(dec, block_ptr)) != NULL)
        decoder_QueueSub(dec, spu);
    return VLCDEC_SUCCESS;
}