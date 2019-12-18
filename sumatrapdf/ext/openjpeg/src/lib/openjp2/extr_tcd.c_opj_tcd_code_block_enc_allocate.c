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
typedef  int /*<<< orphan*/  opj_tcd_pass_t ;
typedef  int /*<<< orphan*/  opj_tcd_layer_t ;
struct TYPE_3__ {int /*<<< orphan*/ * passes; int /*<<< orphan*/ * layers; } ;
typedef  TYPE_1__ opj_tcd_cblk_enc_t ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 scalar_t__ opj_calloc (int,int) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_code_block_enc_allocate(opj_tcd_cblk_enc_t *
        p_code_block)
{
    if (! p_code_block->layers) {
        /* no memset since data */
        p_code_block->layers = (opj_tcd_layer_t*) opj_calloc(100,
                               sizeof(opj_tcd_layer_t));
        if (! p_code_block->layers) {
            return OPJ_FALSE;
        }
    }
    if (! p_code_block->passes) {
        p_code_block->passes = (opj_tcd_pass_t*) opj_calloc(100,
                               sizeof(opj_tcd_pass_t));
        if (! p_code_block->passes) {
            return OPJ_FALSE;
        }
    }
    return OPJ_TRUE;
}