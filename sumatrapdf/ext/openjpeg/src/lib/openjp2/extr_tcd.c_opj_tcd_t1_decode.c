#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tcd_tilecomp_t ;
struct TYPE_11__ {size_t numcomps; int /*<<< orphan*/ * comps; } ;
typedef  TYPE_3__ opj_tcd_tile_t ;
struct TYPE_12__ {int /*<<< orphan*/  thread_pool; int /*<<< orphan*/ * used_component; TYPE_2__* tcp; TYPE_1__* tcd_image; } ;
typedef  TYPE_4__ opj_tcd_t ;
struct TYPE_13__ {int cblksty; } ;
typedef  TYPE_5__ opj_tccp_t ;
typedef  int /*<<< orphan*/  opj_mutex_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_10__ {scalar_t__ num_layers_to_decode; scalar_t__ numlayers; TYPE_5__* tccps; } ;
struct TYPE_9__ {TYPE_3__* tiles; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  volatile OPJ_BOOL ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_PTERM ; 
 int /*<<< orphan*/  volatile OPJ_FALSE ; 
 int /*<<< orphan*/  volatile OPJ_TRUE ; 
 int /*<<< orphan*/ * opj_mutex_create () ; 
 int /*<<< orphan*/  opj_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_t1_decode_cblks (TYPE_4__*,int /*<<< orphan*/  volatile*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  opj_thread_pool_wait_completion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_t1_decode(opj_tcd_t *p_tcd, opj_event_mgr_t *p_manager)
{
    OPJ_UINT32 compno;
    opj_tcd_tile_t * l_tile = p_tcd->tcd_image->tiles;
    opj_tcd_tilecomp_t* l_tile_comp = l_tile->comps;
    opj_tccp_t * l_tccp = p_tcd->tcp->tccps;
    volatile OPJ_BOOL ret = OPJ_TRUE;
    OPJ_BOOL check_pterm = OPJ_FALSE;
    opj_mutex_t* p_manager_mutex = NULL;

    p_manager_mutex = opj_mutex_create();

    /* Only enable PTERM check if we decode all layers */
    if (p_tcd->tcp->num_layers_to_decode == p_tcd->tcp->numlayers &&
            (l_tccp->cblksty & J2K_CCP_CBLKSTY_PTERM) != 0) {
        check_pterm = OPJ_TRUE;
    }

    for (compno = 0; compno < l_tile->numcomps;
            ++compno, ++l_tile_comp, ++l_tccp) {
        if (p_tcd->used_component != NULL && !p_tcd->used_component[compno]) {
            continue;
        }

        opj_t1_decode_cblks(p_tcd, &ret, l_tile_comp, l_tccp,
                            p_manager, p_manager_mutex, check_pterm);
        if (!ret) {
            break;
        }
    }

    opj_thread_pool_wait_completion(p_tcd->thread_pool, 0);
    if (p_manager_mutex) {
        opj_mutex_destroy(p_manager_mutex);
    }
    return ret;
}