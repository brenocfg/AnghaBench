#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {TYPE_10__* tccps; } ;
typedef  TYPE_6__ opj_tcp_t ;
struct TYPE_30__ {int minimum_num_resolutions; int data_size_needed; scalar_t__ win_x0; scalar_t__ win_y0; scalar_t__ win_x1; scalar_t__ win_y1; size_t numresolutions; int /*<<< orphan*/ * data_win; TYPE_9__* resolutions; scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_7__ opj_tcd_tilecomp_t ;
struct TYPE_31__ {size_t tcd_tileno; size_t win_x0; size_t win_y0; size_t win_x1; size_t win_y1; void** used_component; TYPE_4__* image; TYPE_3__* tcd_image; void* whole_tile_decoding; TYPE_5__* cp; TYPE_6__* tcp; } ;
typedef  TYPE_8__ opj_tcd_t ;
struct TYPE_32__ {int win_x0; int win_y0; int win_x1; int win_y1; size_t pw; size_t ph; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_9__ opj_tcd_resolution_t ;
struct TYPE_21__ {int /*<<< orphan*/ * prch; int /*<<< orphan*/ * prcw; } ;
typedef  TYPE_10__ opj_tccp_t ;
typedef  int /*<<< orphan*/  opj_packet_info_t ;
struct TYPE_22__ {int resno_decoded; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
typedef  TYPE_11__ opj_image_comp_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  opj_codestream_index_t ;
struct TYPE_28__ {TYPE_6__* tcps; } ;
struct TYPE_27__ {size_t numcomps; TYPE_11__* comps; } ;
struct TYPE_26__ {TYPE_2__* tiles; } ;
struct TYPE_25__ {TYPE_7__* comps; } ;
struct TYPE_24__ {size_t* pw; size_t* ph; int /*<<< orphan*/ * packet; int /*<<< orphan*/ * pdy; int /*<<< orphan*/ * pdx; } ;
struct TYPE_23__ {size_t numlayers; scalar_t__ packno; TYPE_1__* tile; scalar_t__ numcomps; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  void* OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 void* OPJ_FALSE ; 
 void* OPJ_TRUE ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  opj_alloc_tile_component_data (TYPE_7__*) ; 
 scalar_t__ opj_calloc (int,size_t) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  opj_free (void**) ; 
 scalar_t__ opj_image_data_alloc (int) ; 
 int /*<<< orphan*/  opj_image_data_free (int /*<<< orphan*/ *) ; 
 scalar_t__ opj_malloc (size_t) ; 
 int /*<<< orphan*/  opj_tcd_dc_level_shift_decode (TYPE_8__*) ; 
 int /*<<< orphan*/  opj_tcd_dwt_decode (TYPE_8__*) ; 
 int /*<<< orphan*/  opj_tcd_is_whole_tilecomp_decoding (TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  opj_tcd_mct_decode (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_tcd_t1_decode (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_tcd_t2_decode (TYPE_8__*,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_uint_ceildiv (size_t,int /*<<< orphan*/ ) ; 
 void* opj_uint_ceildivpow2 (scalar_t__,int) ; 
 void* opj_uint_max (size_t,int /*<<< orphan*/ ) ; 
 void* opj_uint_min (size_t,int /*<<< orphan*/ ) ; 
 TYPE_12__* p_cstr_info ; 

OPJ_BOOL opj_tcd_decode_tile(opj_tcd_t *p_tcd,
                             OPJ_UINT32 win_x0,
                             OPJ_UINT32 win_y0,
                             OPJ_UINT32 win_x1,
                             OPJ_UINT32 win_y1,
                             OPJ_UINT32 numcomps_to_decode,
                             const OPJ_UINT32 *comps_indices,
                             OPJ_BYTE *p_src,
                             OPJ_UINT32 p_max_length,
                             OPJ_UINT32 p_tile_no,
                             opj_codestream_index_t *p_cstr_index,
                             opj_event_mgr_t *p_manager
                            )
{
    OPJ_UINT32 l_data_read;
    OPJ_UINT32 compno;

    p_tcd->tcd_tileno = p_tile_no;
    p_tcd->tcp = &(p_tcd->cp->tcps[p_tile_no]);
    p_tcd->win_x0 = win_x0;
    p_tcd->win_y0 = win_y0;
    p_tcd->win_x1 = win_x1;
    p_tcd->win_y1 = win_y1;
    p_tcd->whole_tile_decoding = OPJ_TRUE;

    opj_free(p_tcd->used_component);
    p_tcd->used_component = NULL;

    if (numcomps_to_decode) {
        OPJ_BOOL* used_component = (OPJ_BOOL*) opj_calloc(sizeof(OPJ_BOOL),
                                   p_tcd->image->numcomps);
        if (used_component == NULL) {
            return OPJ_FALSE;
        }
        for (compno = 0; compno < numcomps_to_decode; compno++) {
            used_component[ comps_indices[compno] ] = OPJ_TRUE;
        }

        p_tcd->used_component = used_component;
    }

    for (compno = 0; compno < p_tcd->image->numcomps; compno++) {
        if (p_tcd->used_component != NULL && !p_tcd->used_component[compno]) {
            continue;
        }

        if (!opj_tcd_is_whole_tilecomp_decoding(p_tcd, compno)) {
            p_tcd->whole_tile_decoding = OPJ_FALSE;
            break;
        }
    }

    if (p_tcd->whole_tile_decoding) {
        for (compno = 0; compno < p_tcd->image->numcomps; compno++) {
            opj_tcd_tilecomp_t* tilec = &(p_tcd->tcd_image->tiles->comps[compno]);
            opj_tcd_resolution_t *l_res = &
                                          (tilec->resolutions[tilec->minimum_num_resolutions - 1]);
            OPJ_SIZE_T l_data_size;

            /* compute l_data_size with overflow check */
            OPJ_SIZE_T res_w = (OPJ_SIZE_T)(l_res->x1 - l_res->x0);
            OPJ_SIZE_T res_h = (OPJ_SIZE_T)(l_res->y1 - l_res->y0);

            if (p_tcd->used_component != NULL && !p_tcd->used_component[compno]) {
                continue;
            }

            /* issue 733, l_data_size == 0U, probably something wrong should be checked before getting here */
            if (res_h > 0 && res_w > SIZE_MAX / res_h) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Size of tile data exceeds system limits\n");
                return OPJ_FALSE;
            }
            l_data_size = res_w * res_h;

            if (SIZE_MAX / sizeof(OPJ_UINT32) < l_data_size) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Size of tile data exceeds system limits\n");
                return OPJ_FALSE;
            }
            l_data_size *= sizeof(OPJ_UINT32);

            tilec->data_size_needed = l_data_size;

            if (!opj_alloc_tile_component_data(tilec)) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Size of tile data exceeds system limits\n");
                return OPJ_FALSE;
            }
        }
    } else {
        /* Compute restricted tile-component and tile-resolution coordinates */
        /* of the window of interest, but defer the memory allocation until */
        /* we know the resno_decoded */
        for (compno = 0; compno < p_tcd->image->numcomps; compno++) {
            OPJ_UINT32 resno;
            opj_tcd_tilecomp_t* tilec = &(p_tcd->tcd_image->tiles->comps[compno]);
            opj_image_comp_t* image_comp = &(p_tcd->image->comps[compno]);

            if (p_tcd->used_component != NULL && !p_tcd->used_component[compno]) {
                continue;
            }

            /* Compute the intersection of the area of interest, expressed in tile coordinates */
            /* with the tile coordinates */
            tilec->win_x0 = opj_uint_max(
                                (OPJ_UINT32)tilec->x0,
                                opj_uint_ceildiv(p_tcd->win_x0, image_comp->dx));
            tilec->win_y0 = opj_uint_max(
                                (OPJ_UINT32)tilec->y0,
                                opj_uint_ceildiv(p_tcd->win_y0, image_comp->dy));
            tilec->win_x1 = opj_uint_min(
                                (OPJ_UINT32)tilec->x1,
                                opj_uint_ceildiv(p_tcd->win_x1, image_comp->dx));
            tilec->win_y1 = opj_uint_min(
                                (OPJ_UINT32)tilec->y1,
                                opj_uint_ceildiv(p_tcd->win_y1, image_comp->dy));
            if (tilec->win_x1 < tilec->win_x0 ||
                    tilec->win_y1 < tilec->win_y0) {
                /* We should not normally go there. The circumstance is when */
                /* the tile coordinates do not intersect the area of interest */
                /* Upper level logic should not even try to decode that tile */
                opj_event_msg(p_manager, EVT_ERROR,
                              "Invalid tilec->win_xxx values\n");
                return OPJ_FALSE;
            }

            for (resno = 0; resno < tilec->numresolutions; ++resno) {
                opj_tcd_resolution_t *res = tilec->resolutions + resno;
                res->win_x0 = opj_uint_ceildivpow2(tilec->win_x0,
                                                   tilec->numresolutions - 1 - resno);
                res->win_y0 = opj_uint_ceildivpow2(tilec->win_y0,
                                                   tilec->numresolutions - 1 - resno);
                res->win_x1 = opj_uint_ceildivpow2(tilec->win_x1,
                                                   tilec->numresolutions - 1 - resno);
                res->win_y1 = opj_uint_ceildivpow2(tilec->win_y1,
                                                   tilec->numresolutions - 1 - resno);
            }
        }
    }

#ifdef TODO_MSD /* FIXME */
    /* INDEX >>  */
    if (p_cstr_info) {
        OPJ_UINT32 resno, compno, numprec = 0;
        for (compno = 0; compno < (OPJ_UINT32) p_cstr_info->numcomps; compno++) {
            opj_tcp_t *tcp = &p_tcd->cp->tcps[0];
            opj_tccp_t *tccp = &tcp->tccps[compno];
            opj_tcd_tilecomp_t *tilec_idx = &p_tcd->tcd_image->tiles->comps[compno];
            for (resno = 0; resno < tilec_idx->numresolutions; resno++) {
                opj_tcd_resolution_t *res_idx = &tilec_idx->resolutions[resno];
                p_cstr_info->tile[p_tile_no].pw[resno] = res_idx->pw;
                p_cstr_info->tile[p_tile_no].ph[resno] = res_idx->ph;
                numprec += res_idx->pw * res_idx->ph;
                p_cstr_info->tile[p_tile_no].pdx[resno] = tccp->prcw[resno];
                p_cstr_info->tile[p_tile_no].pdy[resno] = tccp->prch[resno];
            }
        }
        p_cstr_info->tile[p_tile_no].packet = (opj_packet_info_t *) opj_malloc(
                p_cstr_info->numlayers * numprec * sizeof(opj_packet_info_t));
        p_cstr_info->packno = 0;
    }
    /* << INDEX */
#endif

    /*--------------TIER2------------------*/
    /* FIXME _ProfStart(PGROUP_T2); */
    l_data_read = 0;
    if (! opj_tcd_t2_decode(p_tcd, p_src, &l_data_read, p_max_length, p_cstr_index,
                            p_manager)) {
        return OPJ_FALSE;
    }
    /* FIXME _ProfStop(PGROUP_T2); */

    /*------------------TIER1-----------------*/

    /* FIXME _ProfStart(PGROUP_T1); */
    if (! opj_tcd_t1_decode(p_tcd, p_manager)) {
        return OPJ_FALSE;
    }
    /* FIXME _ProfStop(PGROUP_T1); */


    /* For subtile decoding, now we know the resno_decoded, we can allocate */
    /* the tile data buffer */
    if (!p_tcd->whole_tile_decoding) {
        for (compno = 0; compno < p_tcd->image->numcomps; compno++) {
            opj_tcd_tilecomp_t* tilec = &(p_tcd->tcd_image->tiles->comps[compno]);
            opj_image_comp_t* image_comp = &(p_tcd->image->comps[compno]);
            opj_tcd_resolution_t *res = tilec->resolutions + image_comp->resno_decoded;
            OPJ_SIZE_T w = res->win_x1 - res->win_x0;
            OPJ_SIZE_T h = res->win_y1 - res->win_y0;
            OPJ_SIZE_T l_data_size;

            opj_image_data_free(tilec->data_win);
            tilec->data_win = NULL;

            if (p_tcd->used_component != NULL && !p_tcd->used_component[compno]) {
                continue;
            }

            if (w > 0 && h > 0) {
                if (w > SIZE_MAX / h) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "Size of tile data exceeds system limits\n");
                    return OPJ_FALSE;
                }
                l_data_size = w * h;
                if (l_data_size > SIZE_MAX / sizeof(OPJ_INT32)) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "Size of tile data exceeds system limits\n");
                    return OPJ_FALSE;
                }
                l_data_size *= sizeof(OPJ_INT32);

                tilec->data_win = (OPJ_INT32*) opj_image_data_alloc(l_data_size);
                if (tilec->data_win == NULL) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "Size of tile data exceeds system limits\n");
                    return OPJ_FALSE;
                }
            }
        }
    }

    /*----------------DWT---------------------*/

    /* FIXME _ProfStart(PGROUP_DWT); */
    if
    (! opj_tcd_dwt_decode(p_tcd)) {
        return OPJ_FALSE;
    }
    /* FIXME _ProfStop(PGROUP_DWT); */

    /*----------------MCT-------------------*/
    /* FIXME _ProfStart(PGROUP_MCT); */
    if
    (! opj_tcd_mct_decode(p_tcd, p_manager)) {
        return OPJ_FALSE;
    }
    /* FIXME _ProfStop(PGROUP_MCT); */

    /* FIXME _ProfStart(PGROUP_DC_SHIFT); */
    if
    (! opj_tcd_dc_level_shift_decode(p_tcd)) {
        return OPJ_FALSE;
    }
    /* FIXME _ProfStop(PGROUP_DC_SHIFT); */


    /*---------------TILE-------------------*/
    return OPJ_TRUE;
}