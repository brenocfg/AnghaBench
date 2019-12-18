#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_8__* tccps; int /*<<< orphan*/  mct; int /*<<< orphan*/  numlayers; int /*<<< orphan*/  prg; int /*<<< orphan*/  csty; } ;
typedef  TYPE_7__ opj_tcp_t ;
struct TYPE_24__ {scalar_t__ numresolutions; scalar_t__ qntsty; int /*<<< orphan*/  roishift; TYPE_6__* stepsizes; int /*<<< orphan*/  numgbits; int /*<<< orphan*/  prcw; int /*<<< orphan*/  prch; int /*<<< orphan*/  qmfbid; int /*<<< orphan*/  cblksty; int /*<<< orphan*/  cblkh; int /*<<< orphan*/  cblkw; int /*<<< orphan*/  csty; } ;
typedef  TYPE_8__ opj_tccp_t ;
struct TYPE_25__ {scalar_t__ numresolutions; scalar_t__ qntsty; size_t* stepsizes_mant; size_t* stepsizes_expn; int /*<<< orphan*/  roishift; int /*<<< orphan*/  numgbits; int /*<<< orphan*/  prcw; int /*<<< orphan*/  prch; int /*<<< orphan*/  qmfbid; int /*<<< orphan*/  cblksty; int /*<<< orphan*/  cblkh; int /*<<< orphan*/  cblkw; int /*<<< orphan*/  csty; } ;
typedef  TYPE_9__ opj_tccp_info_t ;
struct TYPE_19__ {TYPE_7__* m_default_tcp; } ;
struct TYPE_20__ {TYPE_3__ m_decoder; } ;
struct TYPE_18__ {int /*<<< orphan*/  th; int /*<<< orphan*/  tw; int /*<<< orphan*/  tdy; int /*<<< orphan*/  tdx; int /*<<< orphan*/  ty0; int /*<<< orphan*/  tx0; } ;
struct TYPE_15__ {TYPE_4__ m_specific_param; TYPE_2__ m_cp; TYPE_1__* m_private_image; } ;
typedef  TYPE_10__ opj_j2k_t ;
struct TYPE_21__ {TYPE_9__* tccp_info; int /*<<< orphan*/  mct; int /*<<< orphan*/  numlayers; int /*<<< orphan*/  prg; int /*<<< orphan*/  csty; } ;
struct TYPE_16__ {int nbcomps; TYPE_5__ m_default_tile_info; int /*<<< orphan*/ * tile_info; int /*<<< orphan*/  th; int /*<<< orphan*/  tw; int /*<<< orphan*/  tdy; int /*<<< orphan*/  tdx; int /*<<< orphan*/  ty0; int /*<<< orphan*/  tx0; } ;
typedef  TYPE_11__ opj_codestream_info_v2_t ;
struct TYPE_22__ {scalar_t__ expn; scalar_t__ mant; } ;
struct TYPE_17__ {size_t numcomps; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int OPJ_INT32 ;

/* Variables and functions */
 scalar_t__ J2K_CCP_QNTSTY_SIQNT ; 
 int OPJ_J2K_MAXBANDS ; 
 scalar_t__ OPJ_J2K_MAXRLVLS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ opj_calloc (int,int) ; 
 int /*<<< orphan*/  opj_destroy_cstr_info (TYPE_11__**) ; 

opj_codestream_info_v2_t* j2k_get_cstr_info(opj_j2k_t* p_j2k)
{
    OPJ_UINT32 compno;
    OPJ_UINT32 numcomps = p_j2k->m_private_image->numcomps;
    opj_tcp_t *l_default_tile;
    opj_codestream_info_v2_t* cstr_info = (opj_codestream_info_v2_t*) opj_calloc(1,
                                          sizeof(opj_codestream_info_v2_t));
    if (!cstr_info) {
        return NULL;
    }

    cstr_info->nbcomps = p_j2k->m_private_image->numcomps;

    cstr_info->tx0 = p_j2k->m_cp.tx0;
    cstr_info->ty0 = p_j2k->m_cp.ty0;
    cstr_info->tdx = p_j2k->m_cp.tdx;
    cstr_info->tdy = p_j2k->m_cp.tdy;
    cstr_info->tw = p_j2k->m_cp.tw;
    cstr_info->th = p_j2k->m_cp.th;

    cstr_info->tile_info = NULL; /* Not fill from the main header*/

    l_default_tile = p_j2k->m_specific_param.m_decoder.m_default_tcp;

    cstr_info->m_default_tile_info.csty = l_default_tile->csty;
    cstr_info->m_default_tile_info.prg = l_default_tile->prg;
    cstr_info->m_default_tile_info.numlayers = l_default_tile->numlayers;
    cstr_info->m_default_tile_info.mct = l_default_tile->mct;

    cstr_info->m_default_tile_info.tccp_info = (opj_tccp_info_t*) opj_calloc(
                cstr_info->nbcomps, sizeof(opj_tccp_info_t));
    if (!cstr_info->m_default_tile_info.tccp_info) {
        opj_destroy_cstr_info(&cstr_info);
        return NULL;
    }

    for (compno = 0; compno < numcomps; compno++) {
        opj_tccp_t *l_tccp = &(l_default_tile->tccps[compno]);
        opj_tccp_info_t *l_tccp_info = &
                                       (cstr_info->m_default_tile_info.tccp_info[compno]);
        OPJ_INT32 bandno, numbands;

        /* coding style*/
        l_tccp_info->csty = l_tccp->csty;
        l_tccp_info->numresolutions = l_tccp->numresolutions;
        l_tccp_info->cblkw = l_tccp->cblkw;
        l_tccp_info->cblkh = l_tccp->cblkh;
        l_tccp_info->cblksty = l_tccp->cblksty;
        l_tccp_info->qmfbid = l_tccp->qmfbid;
        if (l_tccp->numresolutions < OPJ_J2K_MAXRLVLS) {
            memcpy(l_tccp_info->prch, l_tccp->prch, l_tccp->numresolutions);
            memcpy(l_tccp_info->prcw, l_tccp->prcw, l_tccp->numresolutions);
        }

        /* quantization style*/
        l_tccp_info->qntsty = l_tccp->qntsty;
        l_tccp_info->numgbits = l_tccp->numgbits;

        numbands = (l_tccp->qntsty == J2K_CCP_QNTSTY_SIQNT) ? 1 :
                   (OPJ_INT32)l_tccp->numresolutions * 3 - 2;
        if (numbands < OPJ_J2K_MAXBANDS) {
            for (bandno = 0; bandno < numbands; bandno++) {
                l_tccp_info->stepsizes_mant[bandno] = (OPJ_UINT32)
                                                      l_tccp->stepsizes[bandno].mant;
                l_tccp_info->stepsizes_expn[bandno] = (OPJ_UINT32)
                                                      l_tccp->stepsizes[bandno].expn;
            }
        }

        /* RGN value*/
        l_tccp_info->roishift = l_tccp->roishift;
    }

    return cstr_info;
}