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
typedef  int /*<<< orphan*/  opj_tcd_seg_t ;
typedef  int /*<<< orphan*/  opj_tcd_seg_data_chunk_t ;
struct TYPE_4__ {size_t m_current_max_segs; size_t numchunksalloc; int decoded_data; int /*<<< orphan*/ * chunks; int /*<<< orphan*/ * segs; } ;
typedef  TYPE_1__ opj_tcd_cblk_dec_t ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 size_t OPJ_J2K_DEFAULT_NB_SEGS ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_aligned_free (int) ; 
 scalar_t__ opj_calloc (size_t,int) ; 
 int /*<<< orphan*/  opj_tcd_reinit_segment (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_code_block_dec_allocate(opj_tcd_cblk_dec_t *
        p_code_block)
{
    if (! p_code_block->segs) {

        p_code_block->segs = (opj_tcd_seg_t *) opj_calloc(OPJ_J2K_DEFAULT_NB_SEGS,
                             sizeof(opj_tcd_seg_t));
        if (! p_code_block->segs) {
            return OPJ_FALSE;
        }
        /*fprintf(stderr, "Allocate %d elements of code_block->data\n", OPJ_J2K_DEFAULT_NB_SEGS * sizeof(opj_tcd_seg_t));*/

        p_code_block->m_current_max_segs = OPJ_J2K_DEFAULT_NB_SEGS;
        /*fprintf(stderr, "m_current_max_segs of code_block->data = %d\n", p_code_block->m_current_max_segs);*/
    } else {
        /* sanitize */
        opj_tcd_seg_t * l_segs = p_code_block->segs;
        OPJ_UINT32 l_current_max_segs = p_code_block->m_current_max_segs;
        opj_tcd_seg_data_chunk_t* l_chunks = p_code_block->chunks;
        OPJ_UINT32 l_numchunksalloc = p_code_block->numchunksalloc;
        OPJ_UINT32 i;

        opj_aligned_free(p_code_block->decoded_data);
        p_code_block->decoded_data = 00;

        memset(p_code_block, 0, sizeof(opj_tcd_cblk_dec_t));
        p_code_block->segs = l_segs;
        p_code_block->m_current_max_segs = l_current_max_segs;
        for (i = 0; i < l_current_max_segs; ++i) {
            opj_tcd_reinit_segment(&l_segs[i]);
        }
        p_code_block->chunks = l_chunks;
        p_code_block->numchunksalloc = l_numchunksalloc;
    }

    return OPJ_TRUE;
}