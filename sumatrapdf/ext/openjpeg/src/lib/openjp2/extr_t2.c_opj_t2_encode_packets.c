#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {int end_header; TYPE_9__* packet; } ;
typedef  TYPE_4__ opj_tile_info_t ;
struct TYPE_34__ {size_t numpocs; int POC; } ;
typedef  TYPE_5__ opj_tcp_t ;
struct TYPE_35__ {int /*<<< orphan*/  packno; } ;
typedef  TYPE_6__ opj_tcd_tile_t ;
struct TYPE_36__ {TYPE_11__* cp; TYPE_10__* image; } ;
typedef  TYPE_7__ opj_t2_t ;
struct TYPE_30__ {scalar_t__ prg; } ;
struct TYPE_37__ {size_t layno; TYPE_1__ poc; } ;
typedef  TYPE_8__ opj_pi_iterator_t ;
struct TYPE_38__ {int start_pos; int end_pos; int /*<<< orphan*/  end_ph_pos; } ;
typedef  TYPE_9__ opj_packet_info_t ;
struct TYPE_27__ {int numcomps; } ;
typedef  TYPE_10__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_31__ {scalar_t__ m_max_comp_size; int m_tp_on; } ;
struct TYPE_32__ {TYPE_2__ m_enc; } ;
struct TYPE_28__ {scalar_t__ rsiz; TYPE_3__ m_specific_param; TYPE_5__* tcps; } ;
typedef  TYPE_11__ opj_cp_t ;
struct TYPE_29__ {size_t packno; TYPE_4__* tile; scalar_t__ index_write; } ;
typedef  TYPE_12__ opj_codestream_info_t ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;
typedef  int /*<<< orphan*/  J2K_T2_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 scalar_t__ OPJ_PROFILE_CINEMA_4K ; 
 scalar_t__ OPJ_PROG_UNKNOWN ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  THRESH_CALC ; 
 int /*<<< orphan*/  opj_pi_create_encode (TYPE_8__*,TYPE_11__*,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_pi_destroy (TYPE_8__*,size_t) ; 
 TYPE_8__* opj_pi_initialise_encode (TYPE_10__*,TYPE_11__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ opj_pi_next (TYPE_8__*) ; 
 int /*<<< orphan*/  opj_t2_encode_packet (size_t,TYPE_6__*,TYPE_5__*,TYPE_8__*,int /*<<< orphan*/ *,size_t*,size_t,TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_t2_encode_packets(opj_t2_t* p_t2,
                               OPJ_UINT32 p_tile_no,
                               opj_tcd_tile_t *p_tile,
                               OPJ_UINT32 p_maxlayers,
                               OPJ_BYTE *p_dest,
                               OPJ_UINT32 * p_data_written,
                               OPJ_UINT32 p_max_len,
                               opj_codestream_info_t *cstr_info,
                               OPJ_UINT32 p_tp_num,
                               OPJ_INT32 p_tp_pos,
                               OPJ_UINT32 p_pino,
                               J2K_T2_MODE p_t2_mode,
                               opj_event_mgr_t *p_manager)
{
    OPJ_BYTE *l_current_data = p_dest;
    OPJ_UINT32 l_nb_bytes = 0;
    OPJ_UINT32 compno;
    OPJ_UINT32 poc;
    opj_pi_iterator_t *l_pi = 00;
    opj_pi_iterator_t *l_current_pi = 00;
    opj_image_t *l_image = p_t2->image;
    opj_cp_t *l_cp = p_t2->cp;
    opj_tcp_t *l_tcp = &l_cp->tcps[p_tile_no];
    OPJ_UINT32 pocno = (l_cp->rsiz == OPJ_PROFILE_CINEMA_4K) ? 2 : 1;
    OPJ_UINT32 l_max_comp = l_cp->m_specific_param.m_enc.m_max_comp_size > 0 ?
                            l_image->numcomps : 1;
    OPJ_UINT32 l_nb_pocs = l_tcp->numpocs + 1;

    l_pi = opj_pi_initialise_encode(l_image, l_cp, p_tile_no, p_t2_mode);
    if (!l_pi) {
        return OPJ_FALSE;
    }

    * p_data_written = 0;

    if (p_t2_mode == THRESH_CALC) { /* Calculating threshold */
        l_current_pi = l_pi;

        for (compno = 0; compno < l_max_comp; ++compno) {
            OPJ_UINT32 l_comp_len = 0;
            l_current_pi = l_pi;

            for (poc = 0; poc < pocno ; ++poc) {
                OPJ_UINT32 l_tp_num = compno;

                /* TODO MSD : check why this function cannot fail (cf. v1) */
                opj_pi_create_encode(l_pi, l_cp, p_tile_no, poc, l_tp_num, p_tp_pos, p_t2_mode);

                if (l_current_pi->poc.prg == OPJ_PROG_UNKNOWN) {
                    /* TODO ADE : add an error */
                    opj_pi_destroy(l_pi, l_nb_pocs);
                    return OPJ_FALSE;
                }
                while (opj_pi_next(l_current_pi)) {
                    if (l_current_pi->layno < p_maxlayers) {
                        l_nb_bytes = 0;

                        if (! opj_t2_encode_packet(p_tile_no, p_tile, l_tcp, l_current_pi,
                                                   l_current_data, &l_nb_bytes,
                                                   p_max_len, cstr_info,
                                                   p_t2_mode,
                                                   p_manager)) {
                            opj_pi_destroy(l_pi, l_nb_pocs);
                            return OPJ_FALSE;
                        }

                        l_comp_len += l_nb_bytes;
                        l_current_data += l_nb_bytes;
                        p_max_len -= l_nb_bytes;

                        * p_data_written += l_nb_bytes;
                    }
                }

                if (l_cp->m_specific_param.m_enc.m_max_comp_size) {
                    if (l_comp_len > l_cp->m_specific_param.m_enc.m_max_comp_size) {
                        opj_pi_destroy(l_pi, l_nb_pocs);
                        return OPJ_FALSE;
                    }
                }

                ++l_current_pi;
            }
        }
    } else { /* t2_mode == FINAL_PASS  */
        opj_pi_create_encode(l_pi, l_cp, p_tile_no, p_pino, p_tp_num, p_tp_pos,
                             p_t2_mode);

        l_current_pi = &l_pi[p_pino];
        if (l_current_pi->poc.prg == OPJ_PROG_UNKNOWN) {
            /* TODO ADE : add an error */
            opj_pi_destroy(l_pi, l_nb_pocs);
            return OPJ_FALSE;
        }
        while (opj_pi_next(l_current_pi)) {
            if (l_current_pi->layno < p_maxlayers) {
                l_nb_bytes = 0;

                if (! opj_t2_encode_packet(p_tile_no, p_tile, l_tcp, l_current_pi,
                                           l_current_data, &l_nb_bytes, p_max_len,
                                           cstr_info, p_t2_mode, p_manager)) {
                    opj_pi_destroy(l_pi, l_nb_pocs);
                    return OPJ_FALSE;
                }

                l_current_data += l_nb_bytes;
                p_max_len -= l_nb_bytes;

                * p_data_written += l_nb_bytes;

                /* INDEX >> */
                if (cstr_info) {
                    if (cstr_info->index_write) {
                        opj_tile_info_t *info_TL = &cstr_info->tile[p_tile_no];
                        opj_packet_info_t *info_PK = &info_TL->packet[cstr_info->packno];
                        if (!cstr_info->packno) {
                            info_PK->start_pos = info_TL->end_header + 1;
                        } else {
                            info_PK->start_pos = ((l_cp->m_specific_param.m_enc.m_tp_on | l_tcp->POC) &&
                                                  info_PK->start_pos) ? info_PK->start_pos : info_TL->packet[cstr_info->packno -
                                                                            1].end_pos + 1;
                        }
                        info_PK->end_pos = info_PK->start_pos + l_nb_bytes - 1;
                        info_PK->end_ph_pos += info_PK->start_pos -
                                               1;  /* End of packet header which now only represents the distance
                                                                                                                                                                                                                                                   to start of packet is incremented by value of start of packet*/
                    }

                    cstr_info->packno++;
                }
                /* << INDEX */
                ++p_tile->packno;
            }
        }
    }

    opj_pi_destroy(l_pi, l_nb_pocs);

    return OPJ_TRUE;
}