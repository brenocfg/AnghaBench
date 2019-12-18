#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* comps; } ;
typedef  TYPE_3__ opj_tcd_tile_t ;
struct TYPE_18__ {scalar_t__ numpasses; scalar_t__ maxpasses; int newlen; int len; scalar_t__ numnewpasses; scalar_t__ real_num_passes; } ;
typedef  TYPE_4__ opj_tcd_seg_t ;
struct TYPE_19__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_5__ opj_tcd_seg_data_chunk_t ;
struct TYPE_20__ {scalar_t__ numbands; TYPE_9__* bands; } ;
typedef  TYPE_6__ opj_tcd_resolution_t ;
struct TYPE_16__ {TYPE_8__* dec; } ;
struct TYPE_21__ {scalar_t__ cw; scalar_t__ ch; TYPE_2__ cblks; } ;
typedef  TYPE_7__ opj_tcd_precinct_t ;
struct TYPE_22__ {scalar_t__ numnewpasses; int numsegs; int len; size_t numchunks; size_t numchunksalloc; int real_num_segs; TYPE_5__* chunks; TYPE_4__* segs; } ;
typedef  TYPE_8__ opj_tcd_cblk_dec_t ;
struct TYPE_23__ {scalar_t__ x1; scalar_t__ x0; scalar_t__ y1; scalar_t__ y0; TYPE_7__* precincts; } ;
typedef  TYPE_9__ opj_tcd_band_t ;
typedef  int /*<<< orphan*/  opj_t2_t ;
struct TYPE_14__ {size_t compno; size_t resno; size_t precno; } ;
typedef  TYPE_10__ opj_pi_iterator_t ;
typedef  int /*<<< orphan*/  opj_packet_info_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_15__ {TYPE_6__* resolutions; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 int /*<<< orphan*/  JPWL_ASSUME ; 
 int /*<<< orphan*/  OPJ_ARG_NOT_USED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ opj_realloc (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static OPJ_BOOL opj_t2_read_packet_data(opj_t2_t* p_t2,
                                        opj_tcd_tile_t *p_tile,
                                        opj_pi_iterator_t *p_pi,
                                        OPJ_BYTE *p_src_data,
                                        OPJ_UINT32 * p_data_read,
                                        OPJ_UINT32 p_max_length,
                                        opj_packet_info_t *pack_info,
                                        opj_event_mgr_t* p_manager)
{
    OPJ_UINT32 bandno, cblkno;
    OPJ_UINT32 l_nb_code_blocks;
    OPJ_BYTE *l_current_data = p_src_data;
    opj_tcd_band_t *l_band = 00;
    opj_tcd_cblk_dec_t* l_cblk = 00;
    opj_tcd_resolution_t* l_res =
        &p_tile->comps[p_pi->compno].resolutions[p_pi->resno];

    OPJ_ARG_NOT_USED(p_t2);
    OPJ_ARG_NOT_USED(pack_info);

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
                /* Check possible overflow (on l_current_data only, assumes input args already checked) then size */
                if ((((OPJ_SIZE_T)l_current_data + (OPJ_SIZE_T)l_seg->newlen) <
                        (OPJ_SIZE_T)l_current_data) ||
                        (l_current_data + l_seg->newlen > p_src_data + p_max_length)) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "read: segment too long (%d) with max (%d) for codeblock %d (p=%d, b=%d, r=%d, c=%d)\n",
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
                        return OPJ_FALSE;
                    }
                    l_seg->newlen = 8192 - l_cblk->len;
                    opj_event_msg(p_manager, EVT_WARNING, "      - truncating segment to %d\n",
                                  l_seg->newlen);
                    break;
                };

#endif /* USE_JPWL */

                if (l_cblk->numchunks == l_cblk->numchunksalloc) {
                    OPJ_UINT32 l_numchunksalloc = l_cblk->numchunksalloc * 2 + 1;
                    opj_tcd_seg_data_chunk_t* l_chunks =
                        (opj_tcd_seg_data_chunk_t*)opj_realloc(l_cblk->chunks,
                                l_numchunksalloc * sizeof(opj_tcd_seg_data_chunk_t));
                    if (l_chunks == NULL) {
                        opj_event_msg(p_manager, EVT_ERROR,
                                      "cannot allocate opj_tcd_seg_data_chunk_t* array");
                        return OPJ_FALSE;
                    }
                    l_cblk->chunks = l_chunks;
                    l_cblk->numchunksalloc = l_numchunksalloc;
                }

                l_cblk->chunks[l_cblk->numchunks].data = l_current_data;
                l_cblk->chunks[l_cblk->numchunks].len = l_seg->newlen;
                l_cblk->numchunks ++;

                l_current_data += l_seg->newlen;
                l_seg->len += l_seg->newlen;
                l_seg->numpasses += l_seg->numnewpasses;
                l_cblk->numnewpasses -= l_seg->numnewpasses;

                l_seg->real_num_passes = l_seg->numpasses;

                if (l_cblk->numnewpasses > 0) {
                    ++l_seg;
                    ++l_cblk->numsegs;
                }
            } while (l_cblk->numnewpasses > 0);

            l_cblk->real_num_segs = l_cblk->numsegs;
            ++l_cblk;
        } /* next code_block */

        ++l_band;
    }

    *(p_data_read) = (OPJ_UINT32)(l_current_data - p_src_data);


    return OPJ_TRUE;
}