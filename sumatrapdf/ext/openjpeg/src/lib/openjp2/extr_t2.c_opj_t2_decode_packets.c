#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_59__   TYPE_9__ ;
typedef  struct TYPE_58__   TYPE_8__ ;
typedef  struct TYPE_57__   TYPE_7__ ;
typedef  struct TYPE_56__   TYPE_6__ ;
typedef  struct TYPE_55__   TYPE_5__ ;
typedef  struct TYPE_54__   TYPE_4__ ;
typedef  struct TYPE_53__   TYPE_3__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_20__ ;
typedef  struct TYPE_50__   TYPE_1__ ;
typedef  struct TYPE_49__   TYPE_19__ ;
typedef  struct TYPE_48__   TYPE_18__ ;
typedef  struct TYPE_47__   TYPE_17__ ;
typedef  struct TYPE_46__   TYPE_16__ ;
typedef  struct TYPE_45__   TYPE_15__ ;
typedef  struct TYPE_44__   TYPE_14__ ;
typedef  struct TYPE_43__   TYPE_13__ ;
typedef  struct TYPE_42__   TYPE_12__ ;
typedef  struct TYPE_41__   TYPE_11__ ;
typedef  struct TYPE_40__   TYPE_10__ ;

/* Type definitions */
struct TYPE_56__ {int end_header; TYPE_3__* tp; TYPE_15__* packet; } ;
typedef  TYPE_6__ opj_tile_info_v2_t ;
struct TYPE_57__ {size_t numpocs; scalar_t__ num_layers_to_decode; } ;
typedef  TYPE_7__ opj_tcp_t ;
struct TYPE_58__ {scalar_t__ minimum_num_resolutions; TYPE_10__* resolutions; } ;
typedef  TYPE_8__ opj_tcd_tilecomp_t ;
struct TYPE_59__ {TYPE_8__* comps; } ;
typedef  TYPE_9__ opj_tcd_tile_t ;
typedef  int /*<<< orphan*/  opj_tcd_t ;
struct TYPE_40__ {size_t numbands; TYPE_12__* bands; } ;
typedef  TYPE_10__ opj_tcd_resolution_t ;
struct TYPE_41__ {scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_11__ opj_tcd_precinct_t ;
struct TYPE_42__ {int /*<<< orphan*/  bandno; TYPE_11__* precincts; } ;
typedef  TYPE_12__ opj_tcd_band_t ;
struct TYPE_43__ {TYPE_18__* cp; TYPE_16__* image; } ;
typedef  TYPE_13__ opj_t2_t ;
struct TYPE_55__ {scalar_t__ prg; int /*<<< orphan*/  prg1; } ;
struct TYPE_44__ {size_t compno; scalar_t__ resno; size_t precno; scalar_t__ layno; TYPE_5__ poc; } ;
typedef  TYPE_14__ opj_pi_iterator_t ;
struct TYPE_45__ {int start_pos; scalar_t__ end_pos; int /*<<< orphan*/  end_ph_pos; } ;
typedef  TYPE_15__ opj_packet_info_t ;
struct TYPE_46__ {int numcomps; TYPE_17__* comps; } ;
typedef  TYPE_16__ opj_image_t ;
struct TYPE_47__ {scalar_t__ resno_decoded; } ;
typedef  TYPE_17__ opj_image_comp_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_50__ {scalar_t__ m_tp_on; } ;
struct TYPE_52__ {TYPE_1__ m_enc; } ;
struct TYPE_48__ {TYPE_2__ m_specific_param; TYPE_7__* tcps; } ;
typedef  TYPE_18__ opj_cp_t ;
struct TYPE_49__ {TYPE_4__* tile_index; } ;
typedef  TYPE_19__ opj_codestream_index_t ;
struct TYPE_54__ {TYPE_15__* packet; } ;
struct TYPE_53__ {size_t tp_numpacks; int tp_end_header; scalar_t__ tp_end_pos; } ;
struct TYPE_51__ {size_t packno; TYPE_6__* tile; } ;
typedef  size_t OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  JAS_FPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,scalar_t__,size_t,scalar_t__) ; 
 int /*<<< orphan*/  OPJ_ARG_NOT_USED (TYPE_19__*) ; 
 scalar_t__ OPJ_FALSE ; 
 scalar_t__ OPJ_PROG_UNKNOWN ; 
 scalar_t__ OPJ_TRUE ; 
 int /*<<< orphan*/  memset (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  opj_free (scalar_t__*) ; 
 scalar_t__ opj_malloc (int) ; 
 TYPE_14__* opj_pi_create_decode (TYPE_16__*,TYPE_18__*,size_t) ; 
 int /*<<< orphan*/  opj_pi_destroy (TYPE_14__*,size_t) ; 
 scalar_t__ opj_pi_next (TYPE_14__*) ; 
 int /*<<< orphan*/  opj_t2_decode_packet (TYPE_13__*,TYPE_9__*,TYPE_7__*,TYPE_14__*,int /*<<< orphan*/ *,size_t*,size_t,TYPE_15__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_t2_skip_packet (TYPE_13__*,TYPE_9__*,TYPE_7__*,TYPE_14__*,int /*<<< orphan*/ *,size_t*,size_t,TYPE_15__*,int /*<<< orphan*/ *) ; 
 scalar_t__ opj_tcd_is_subband_area_of_interest (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ,size_t,size_t,size_t,size_t) ; 
 scalar_t__ opj_uint_max (size_t,scalar_t__) ; 
 TYPE_20__* p_cstr_info ; 
 int /*<<< orphan*/  stderr ; 

OPJ_BOOL opj_t2_decode_packets(opj_tcd_t* tcd,
                               opj_t2_t *p_t2,
                               OPJ_UINT32 p_tile_no,
                               opj_tcd_tile_t *p_tile,
                               OPJ_BYTE *p_src,
                               OPJ_UINT32 * p_data_read,
                               OPJ_UINT32 p_max_len,
                               opj_codestream_index_t *p_cstr_index,
                               opj_event_mgr_t *p_manager)
{
    OPJ_BYTE *l_current_data = p_src;
    opj_pi_iterator_t *l_pi = 00;
    OPJ_UINT32 pino;
    opj_image_t *l_image = p_t2->image;
    opj_cp_t *l_cp = p_t2->cp;
    opj_tcp_t *l_tcp = &(p_t2->cp->tcps[p_tile_no]);
    OPJ_UINT32 l_nb_bytes_read;
    OPJ_UINT32 l_nb_pocs = l_tcp->numpocs + 1;
    opj_pi_iterator_t *l_current_pi = 00;
#ifdef TODO_MSD
    OPJ_UINT32 curtp = 0;
    OPJ_UINT32 tp_start_packno;
#endif
    opj_packet_info_t *l_pack_info = 00;
    opj_image_comp_t* l_img_comp = 00;

    OPJ_ARG_NOT_USED(p_cstr_index);

#ifdef TODO_MSD
    if (p_cstr_index) {
        l_pack_info = p_cstr_index->tile_index[p_tile_no].packet;
    }
#endif

    /* create a packet iterator */
    l_pi = opj_pi_create_decode(l_image, l_cp, p_tile_no);
    if (!l_pi) {
        return OPJ_FALSE;
    }


    l_current_pi = l_pi;

    for (pino = 0; pino <= l_tcp->numpocs; ++pino) {

        /* if the resolution needed is too low, one dim of the tilec could be equal to zero
         * and no packets are used to decode this resolution and
         * l_current_pi->resno is always >= p_tile->comps[l_current_pi->compno].minimum_num_resolutions
         * and no l_img_comp->resno_decoded are computed
         */
        OPJ_BOOL* first_pass_failed = NULL;

        if (l_current_pi->poc.prg == OPJ_PROG_UNKNOWN) {
            /* TODO ADE : add an error */
            opj_pi_destroy(l_pi, l_nb_pocs);
            return OPJ_FALSE;
        }

        first_pass_failed = (OPJ_BOOL*)opj_malloc(l_image->numcomps * sizeof(OPJ_BOOL));
        if (!first_pass_failed) {
            opj_pi_destroy(l_pi, l_nb_pocs);
            return OPJ_FALSE;
        }
        memset(first_pass_failed, OPJ_TRUE, l_image->numcomps * sizeof(OPJ_BOOL));

        while (opj_pi_next(l_current_pi)) {
            OPJ_BOOL skip_packet = OPJ_FALSE;
            JAS_FPRINTF(stderr,
                        "packet offset=00000166 prg=%d cmptno=%02d rlvlno=%02d prcno=%03d lyrno=%02d\n\n",
                        l_current_pi->poc.prg1, l_current_pi->compno, l_current_pi->resno,
                        l_current_pi->precno, l_current_pi->layno);

            /* If the packet layer is greater or equal than the maximum */
            /* number of layers, skip the packet */
            if (l_current_pi->layno >= l_tcp->num_layers_to_decode) {
                skip_packet = OPJ_TRUE;
            }
            /* If the packet resolution number is greater than the minimum */
            /* number of resolution allowed, skip the packet */
            else if (l_current_pi->resno >=
                     p_tile->comps[l_current_pi->compno].minimum_num_resolutions) {
                skip_packet = OPJ_TRUE;
            } else {
                /* If no precincts of any band intersects the area of interest, */
                /* skip the packet */
                OPJ_UINT32 bandno;
                opj_tcd_tilecomp_t *tilec = &p_tile->comps[l_current_pi->compno];
                opj_tcd_resolution_t *res = &tilec->resolutions[l_current_pi->resno];

                skip_packet = OPJ_TRUE;
                for (bandno = 0; bandno < res->numbands; ++bandno) {
                    opj_tcd_band_t* band = &res->bands[bandno];
                    opj_tcd_precinct_t* prec = &band->precincts[l_current_pi->precno];

                    if (opj_tcd_is_subband_area_of_interest(tcd,
                                                            l_current_pi->compno,
                                                            l_current_pi->resno,
                                                            band->bandno,
                                                            (OPJ_UINT32)prec->x0,
                                                            (OPJ_UINT32)prec->y0,
                                                            (OPJ_UINT32)prec->x1,
                                                            (OPJ_UINT32)prec->y1)) {
                        skip_packet = OPJ_FALSE;
                        break;
                    }
                }
                /*
                                printf("packet cmptno=%02d rlvlno=%02d prcno=%03d lyrno=%02d -> %s\n",
                                    l_current_pi->compno, l_current_pi->resno,
                                    l_current_pi->precno, l_current_pi->layno, skip_packet ? "skipped" : "kept");
                */
            }

            if (!skip_packet) {
                l_nb_bytes_read = 0;

                first_pass_failed[l_current_pi->compno] = OPJ_FALSE;

                if (! opj_t2_decode_packet(p_t2, p_tile, l_tcp, l_current_pi, l_current_data,
                                           &l_nb_bytes_read, p_max_len, l_pack_info, p_manager)) {
                    opj_pi_destroy(l_pi, l_nb_pocs);
                    opj_free(first_pass_failed);
                    return OPJ_FALSE;
                }

                l_img_comp = &(l_image->comps[l_current_pi->compno]);
                l_img_comp->resno_decoded = opj_uint_max(l_current_pi->resno,
                                            l_img_comp->resno_decoded);
            } else {
                l_nb_bytes_read = 0;
                if (! opj_t2_skip_packet(p_t2, p_tile, l_tcp, l_current_pi, l_current_data,
                                         &l_nb_bytes_read, p_max_len, l_pack_info, p_manager)) {
                    opj_pi_destroy(l_pi, l_nb_pocs);
                    opj_free(first_pass_failed);
                    return OPJ_FALSE;
                }
            }

            if (first_pass_failed[l_current_pi->compno]) {
                l_img_comp = &(l_image->comps[l_current_pi->compno]);
                if (l_img_comp->resno_decoded == 0) {
                    l_img_comp->resno_decoded =
                        p_tile->comps[l_current_pi->compno].minimum_num_resolutions - 1;
                }
            }

            l_current_data += l_nb_bytes_read;
            p_max_len -= l_nb_bytes_read;

            /* INDEX >> */
#ifdef TODO_MSD
            if (p_cstr_info) {
                opj_tile_info_v2_t *info_TL = &p_cstr_info->tile[p_tile_no];
                opj_packet_info_t *info_PK = &info_TL->packet[p_cstr_info->packno];
                tp_start_packno = 0;
                if (!p_cstr_info->packno) {
                    info_PK->start_pos = info_TL->end_header + 1;
                } else if (info_TL->packet[p_cstr_info->packno - 1].end_pos >=
                           (OPJ_INT32)
                           p_cstr_info->tile[p_tile_no].tp[curtp].tp_end_pos) { /* New tile part */
                    info_TL->tp[curtp].tp_numpacks = p_cstr_info->packno -
                                                     tp_start_packno; /* Number of packets in previous tile-part */
                    tp_start_packno = p_cstr_info->packno;
                    curtp++;
                    info_PK->start_pos = p_cstr_info->tile[p_tile_no].tp[curtp].tp_end_header + 1;
                } else {
                    info_PK->start_pos = (l_cp->m_specific_param.m_enc.m_tp_on &&
                                          info_PK->start_pos) ? info_PK->start_pos : info_TL->packet[p_cstr_info->packno -
                                                                      1].end_pos + 1;
                }
                info_PK->end_pos = info_PK->start_pos + l_nb_bytes_read - 1;
                info_PK->end_ph_pos += info_PK->start_pos -
                                       1;  /* End of packet header which now only represents the distance */
                ++p_cstr_info->packno;
            }
#endif
            /* << INDEX */
        }
        ++l_current_pi;

        opj_free(first_pass_failed);
    }
    /* INDEX >> */
#ifdef TODO_MSD
    if
    (p_cstr_info) {
        p_cstr_info->tile[p_tile_no].tp[curtp].tp_numpacks = p_cstr_info->packno -
                tp_start_packno; /* Number of packets in last tile-part */
    }
#endif
    /* << INDEX */

    /* don't forget to release pi */
    opj_pi_destroy(l_pi, l_nb_pocs);
    *p_data_read = (OPJ_UINT32)(l_current_data - p_src);
    return OPJ_TRUE;
}