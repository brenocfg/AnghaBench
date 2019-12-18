#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* comps; } ;
typedef  TYPE_3__ opj_tcd_tile_t ;
struct TYPE_15__ {scalar_t__ numpasses; scalar_t__ maxpasses; int newlen; scalar_t__ numnewpasses; } ;
typedef  TYPE_4__ opj_tcd_seg_t ;
struct TYPE_16__ {scalar_t__ numbands; TYPE_8__* bands; } ;
typedef  TYPE_5__ opj_tcd_resolution_t ;
struct TYPE_13__ {TYPE_7__* dec; } ;
struct TYPE_17__ {scalar_t__ cw; scalar_t__ ch; TYPE_2__ cblks; } ;
typedef  TYPE_6__ opj_tcd_precinct_t ;
struct TYPE_18__ {scalar_t__ numnewpasses; int numsegs; int len; TYPE_4__* segs; } ;
typedef  TYPE_7__ opj_tcd_cblk_dec_t ;
struct TYPE_19__ {scalar_t__ x1; scalar_t__ x0; scalar_t__ y1; scalar_t__ y0; TYPE_6__* precincts; } ;
typedef  TYPE_8__ opj_tcd_band_t ;
typedef  int /*<<< orphan*/  opj_t2_t ;
struct TYPE_20__ {size_t compno; size_t resno; size_t precno; } ;
typedef  TYPE_9__ opj_pi_iterator_t ;
typedef  int /*<<< orphan*/  opj_packet_info_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_12__ {TYPE_5__* resolutions; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 int /*<<< orphan*/  JAS_FPRINTF (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  JPWL_ASSUME ; 
 int /*<<< orphan*/  OPJ_ARG_NOT_USED (int /*<<< orphan*/ *) ; 
 int OPJ_FALSE ; 
 int OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static OPJ_BOOL opj_t2_skip_packet_data(opj_t2_t* p_t2,
                                        opj_tcd_tile_t *p_tile,
                                        opj_pi_iterator_t *p_pi,
                                        OPJ_UINT32 * p_data_read,
                                        OPJ_UINT32 p_max_length,
                                        opj_packet_info_t *pack_info,
                                        opj_event_mgr_t *p_manager)
{
    OPJ_UINT32 bandno, cblkno;
    OPJ_UINT32 l_nb_code_blocks;
    opj_tcd_band_t *l_band = 00;
    opj_tcd_cblk_dec_t* l_cblk = 00;
    opj_tcd_resolution_t* l_res =
        &p_tile->comps[p_pi->compno].resolutions[p_pi->resno];

    OPJ_ARG_NOT_USED(p_t2);
    OPJ_ARG_NOT_USED(pack_info);

    *p_data_read = 0;
    l_band = l_res->bands;

    for (bandno = 0; bandno < l_res->numbands; ++bandno) {
        opj_tcd_precinct_t *l_prc = &l_band->precincts[p_pi->precno];

        if ((l_band->x1 - l_band->x0 == 0) || (l_band->y1 - l_band->y0 == 0)) {
            ++l_band;
            continue;
        }

        l_nb_code_blocks = l_prc->cw * l_prc->ch;
        l_cblk = l_prc->cblks.dec;

        for (cblkno = 0; cblkno < l_nb_code_blocks; ++cblkno) {
            opj_tcd_seg_t *l_seg = 00;

            if (!l_cblk->numnewpasses) {
                /* nothing to do */
                ++l_cblk;
                continue;
            }

            if (!l_cblk->numsegs) {
                l_seg = l_cblk->segs;
                ++l_cblk->numsegs;
            } else {
                l_seg = &l_cblk->segs[l_cblk->numsegs - 1];

                if (l_seg->numpasses == l_seg->maxpasses) {
                    ++l_seg;
                    ++l_cblk->numsegs;
                }
            }

            do {
                /* Check possible overflow then size */
                if (((*p_data_read + l_seg->newlen) < (*p_data_read)) ||
                        ((*p_data_read + l_seg->newlen) > p_max_length)) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "skip: segment too long (%d) with max (%d) for codeblock %d (p=%d, b=%d, r=%d, c=%d)\n",
                                  l_seg->newlen, p_max_length, cblkno, p_pi->precno, bandno, p_pi->resno,
                                  p_pi->compno);
                    return OPJ_FALSE;
                }

#ifdef USE_JPWL
                /* we need here a j2k handle to verify if making a check to
                the validity of cblocks parameters is selected from user (-W) */

                /* let's check that we are not exceeding */
                if ((l_cblk->len + l_seg->newlen) > 8192) {
                    opj_event_msg(p_manager, EVT_WARNING,
                                  "JPWL: segment too long (%d) for codeblock %d (p=%d, b=%d, r=%d, c=%d)\n",
                                  l_seg->newlen, cblkno, p_pi->precno, bandno, p_pi->resno, p_pi->compno);
                    if (!JPWL_ASSUME) {
                        opj_event_msg(p_manager, EVT_ERROR, "JPWL: giving up\n");
                        return -999;
                    }
                    l_seg->newlen = 8192 - l_cblk->len;
                    opj_event_msg(p_manager, EVT_WARNING, "      - truncating segment to %d\n",
                                  l_seg->newlen);
                    break;
                };

#endif /* USE_JPWL */
                JAS_FPRINTF(stderr, "p_data_read (%d) newlen (%d) \n", *p_data_read,
                            l_seg->newlen);
                *(p_data_read) += l_seg->newlen;

                l_seg->numpasses += l_seg->numnewpasses;
                l_cblk->numnewpasses -= l_seg->numnewpasses;
                if (l_cblk->numnewpasses > 0) {
                    ++l_seg;
                    ++l_cblk->numsegs;
                }
            } while (l_cblk->numnewpasses > 0);

            ++l_cblk;
        }

        ++l_band;
    }

    return OPJ_TRUE;
}