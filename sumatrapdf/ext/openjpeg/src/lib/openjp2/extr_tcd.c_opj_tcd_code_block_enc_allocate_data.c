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
struct TYPE_3__ {int x1; int x0; int y1; int y0; scalar_t__ data_size; scalar_t__* data; } ;
typedef  TYPE_1__ opj_tcd_cblk_enc_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_INT32 ;
typedef  scalar_t__ OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_free (scalar_t__*) ; 
 scalar_t__ opj_malloc (scalar_t__) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_code_block_enc_allocate_data(opj_tcd_cblk_enc_t *
        p_code_block)
{
    OPJ_UINT32 l_data_size;

    /* +1 is needed for https://github.com/uclouvain/openjpeg/issues/835 */
    /* and actually +2 required for https://github.com/uclouvain/openjpeg/issues/982 */
    /* TODO: is there a theoretical upper-bound for the compressed code */
    /* block size ? */
    l_data_size = 2 + (OPJ_UINT32)((p_code_block->x1 - p_code_block->x0) *
                                   (p_code_block->y1 - p_code_block->y0) * (OPJ_INT32)sizeof(OPJ_UINT32));

    if (l_data_size > p_code_block->data_size) {
        if (p_code_block->data) {
            /* We refer to data - 1 since below we incremented it */
            opj_free(p_code_block->data - 1);
        }
        p_code_block->data = (OPJ_BYTE*) opj_malloc(l_data_size + 1);
        if (! p_code_block->data) {
            p_code_block->data_size = 0U;
            return OPJ_FALSE;
        }
        p_code_block->data_size = l_data_size;

        /* We reserve the initial byte as a fake byte to a non-FF value */
        /* and increment the data pointer, so that opj_mqc_init_enc() */
        /* can do bp = data - 1, and opj_mqc_byteout() can safely dereference */
        /* it. */
        p_code_block->data[0] = 0;
        p_code_block->data += 1; /*why +1 ?*/
    }
    return OPJ_TRUE;
}