#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int len; int real_num_passes; } ;
typedef  TYPE_2__ opj_tcd_seg_t ;
struct TYPE_21__ {int numbps; int numchunks; int* decoded_data; int real_num_segs; TYPE_2__* segs; TYPE_1__* chunks; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_3__ opj_tcd_cblk_dec_t ;
struct TYPE_23__ {scalar_t__ bp; scalar_t__ end; scalar_t__ start; int end_of_byte_stream_counter; scalar_t__ lut_ctxno_zc_orient; } ;
struct TYPE_22__ {int cblkdatabuffersize; scalar_t__* cblkdatabuffer; int* data; scalar_t__ mustuse_cblkdatabuffer; TYPE_5__ mqc; } ;
typedef  TYPE_4__ opj_t1_t ;
typedef  int /*<<< orphan*/  opj_mutex_t ;
typedef  TYPE_5__ opj_mqc_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_19__ {int len; scalar_t__* data; } ;
typedef  int OPJ_UINT32 ;
typedef  int OPJ_INT32 ;
typedef  scalar_t__ OPJ_BYTE ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_WARNING ; 
 int J2K_CCP_CBLKSTY_LAZY ; 
 int J2K_CCP_CBLKSTY_RESET ; 
 int OPJ_COMMON_CBLK_DATA_EXTRA ; 
 scalar_t__ OPJ_FALSE ; 
 scalar_t__ OPJ_TRUE ; 
 int /*<<< orphan*/  T1_CTXNO_AGG ; 
 int /*<<< orphan*/  T1_CTXNO_UNI ; 
 int /*<<< orphan*/  T1_CTXNO_ZC ; 
 scalar_t__ T1_TYPE_MQ ; 
 scalar_t__ T1_TYPE_RAW ; 
 scalar_t__ lut_ctxno_zc ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  opj_mqc_init_dec (TYPE_5__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  opj_mqc_raw_init_dec (TYPE_5__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  opj_mqc_resetstates (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_setstate (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ opj_realloc (scalar_t__*,int) ; 
 int /*<<< orphan*/  opj_t1_allocate_buffers (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  opj_t1_dec_refpass_mqc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  opj_t1_dec_refpass_raw (TYPE_4__*,int) ; 
 int /*<<< orphan*/  opj_t1_dec_sigpass_mqc (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  opj_t1_dec_sigpass_raw (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  opq_mqc_finish_dec (TYPE_5__*) ; 

__attribute__((used)) static OPJ_BOOL opj_t1_decode_cblk(opj_t1_t *t1,
                                   opj_tcd_cblk_dec_t* cblk,
                                   OPJ_UINT32 orient,
                                   OPJ_UINT32 roishift,
                                   OPJ_UINT32 cblksty,
                                   opj_event_mgr_t *p_manager,
                                   opj_mutex_t* p_manager_mutex,
                                   OPJ_BOOL check_pterm)
{
    opj_mqc_t *mqc = &(t1->mqc);   /* MQC component */

    OPJ_INT32 bpno_plus_one;
    OPJ_UINT32 passtype;
    OPJ_UINT32 segno, passno;
    OPJ_BYTE* cblkdata = NULL;
    OPJ_UINT32 cblkdataindex = 0;
    OPJ_BYTE type = T1_TYPE_MQ; /* BYPASS mode */
    OPJ_INT32* original_t1_data = NULL;

    mqc->lut_ctxno_zc_orient = lut_ctxno_zc + (orient << 9);

    if (!opj_t1_allocate_buffers(
                t1,
                (OPJ_UINT32)(cblk->x1 - cblk->x0),
                (OPJ_UINT32)(cblk->y1 - cblk->y0))) {
        return OPJ_FALSE;
    }

    bpno_plus_one = (OPJ_INT32)(roishift + cblk->numbps);
    if (bpno_plus_one >= 31) {
        if (p_manager_mutex) {
            opj_mutex_lock(p_manager_mutex);
        }
        opj_event_msg(p_manager, EVT_WARNING,
                      "opj_t1_decode_cblk(): unsupported bpno_plus_one = %d >= 31\n",
                      bpno_plus_one);
        if (p_manager_mutex) {
            opj_mutex_unlock(p_manager_mutex);
        }
        return OPJ_FALSE;
    }
    passtype = 2;

    opj_mqc_resetstates(mqc);
    opj_mqc_setstate(mqc, T1_CTXNO_UNI, 0, 46);
    opj_mqc_setstate(mqc, T1_CTXNO_AGG, 0, 3);
    opj_mqc_setstate(mqc, T1_CTXNO_ZC, 0, 4);

    /* Even if we have a single chunk, in multi-threaded decoding */
    /* the insertion of our synthetic marker might potentially override */
    /* valid codestream of other codeblocks decoded in parallel. */
    if (cblk->numchunks > 1 || t1->mustuse_cblkdatabuffer) {
        OPJ_UINT32 i;
        OPJ_UINT32 cblk_len;

        /* Compute whole codeblock length from chunk lengths */
        cblk_len = 0;
        for (i = 0; i < cblk->numchunks; i++) {
            cblk_len += cblk->chunks[i].len;
        }

        /* Allocate temporary memory if needed */
        if (cblk_len + OPJ_COMMON_CBLK_DATA_EXTRA > t1->cblkdatabuffersize) {
            cblkdata = (OPJ_BYTE*)opj_realloc(t1->cblkdatabuffer,
                                              cblk_len + OPJ_COMMON_CBLK_DATA_EXTRA);
            if (cblkdata == NULL) {
                return OPJ_FALSE;
            }
            t1->cblkdatabuffer = cblkdata;
            memset(t1->cblkdatabuffer + cblk_len, 0, OPJ_COMMON_CBLK_DATA_EXTRA);
            t1->cblkdatabuffersize = cblk_len + OPJ_COMMON_CBLK_DATA_EXTRA;
        }

        /* Concatenate all chunks */
        cblkdata = t1->cblkdatabuffer;
        cblk_len = 0;
        for (i = 0; i < cblk->numchunks; i++) {
            memcpy(cblkdata + cblk_len, cblk->chunks[i].data, cblk->chunks[i].len);
            cblk_len += cblk->chunks[i].len;
        }
    } else if (cblk->numchunks == 1) {
        cblkdata = cblk->chunks[0].data;
    } else {
        /* Not sure if that can happen in practice, but avoid Coverity to */
        /* think we will dereference a null cblkdta pointer */
        return OPJ_TRUE;
    }

    /* For subtile decoding, directly decode in the decoded_data buffer of */
    /* the code-block. Hack t1->data to point to it, and restore it later */
    if (cblk->decoded_data) {
        original_t1_data = t1->data;
        t1->data = cblk->decoded_data;
    }

    for (segno = 0; segno < cblk->real_num_segs; ++segno) {
        opj_tcd_seg_t *seg = &cblk->segs[segno];

        /* BYPASS mode */
        type = ((bpno_plus_one <= ((OPJ_INT32)(cblk->numbps)) - 4) && (passtype < 2) &&
                (cblksty & J2K_CCP_CBLKSTY_LAZY)) ? T1_TYPE_RAW : T1_TYPE_MQ;

        if (type == T1_TYPE_RAW) {
            opj_mqc_raw_init_dec(mqc, cblkdata + cblkdataindex, seg->len,
                                 OPJ_COMMON_CBLK_DATA_EXTRA);
        } else {
            opj_mqc_init_dec(mqc, cblkdata + cblkdataindex, seg->len,
                             OPJ_COMMON_CBLK_DATA_EXTRA);
        }
        cblkdataindex += seg->len;

        for (passno = 0; (passno < seg->real_num_passes) &&
                (bpno_plus_one >= 1); ++passno) {
            switch (passtype) {
            case 0:
                if (type == T1_TYPE_RAW) {
                    opj_t1_dec_sigpass_raw(t1, bpno_plus_one, (OPJ_INT32)cblksty);
                } else {
                    opj_t1_dec_sigpass_mqc(t1, bpno_plus_one, (OPJ_INT32)cblksty);
                }
                break;
            case 1:
                if (type == T1_TYPE_RAW) {
                    opj_t1_dec_refpass_raw(t1, bpno_plus_one);
                } else {
                    opj_t1_dec_refpass_mqc(t1, bpno_plus_one);
                }
                break;
            case 2:
                opj_t1_dec_clnpass(t1, bpno_plus_one, (OPJ_INT32)cblksty);
                break;
            }

            if ((cblksty & J2K_CCP_CBLKSTY_RESET) && type == T1_TYPE_MQ) {
                opj_mqc_resetstates(mqc);
                opj_mqc_setstate(mqc, T1_CTXNO_UNI, 0, 46);
                opj_mqc_setstate(mqc, T1_CTXNO_AGG, 0, 3);
                opj_mqc_setstate(mqc, T1_CTXNO_ZC, 0, 4);
            }
            if (++passtype == 3) {
                passtype = 0;
                bpno_plus_one--;
            }
        }

        opq_mqc_finish_dec(mqc);
    }

    if (check_pterm) {
        if (mqc->bp + 2 < mqc->end) {
            if (p_manager_mutex) {
                opj_mutex_lock(p_manager_mutex);
            }
            opj_event_msg(p_manager, EVT_WARNING,
                          "PTERM check failure: %d remaining bytes in code block (%d used / %d)\n",
                          (int)(mqc->end - mqc->bp) - 2,
                          (int)(mqc->bp - mqc->start),
                          (int)(mqc->end - mqc->start));
            if (p_manager_mutex) {
                opj_mutex_unlock(p_manager_mutex);
            }
        } else if (mqc->end_of_byte_stream_counter > 2) {
            if (p_manager_mutex) {
                opj_mutex_lock(p_manager_mutex);
            }
            opj_event_msg(p_manager, EVT_WARNING,
                          "PTERM check failure: %d synthetized 0xFF markers read\n",
                          mqc->end_of_byte_stream_counter);
            if (p_manager_mutex) {
                opj_mutex_unlock(p_manager_mutex);
            }
        }
    }

    /* Restore original t1->data is needed */
    if (cblk->decoded_data) {
        t1->data = original_t1_data;
    }

    return OPJ_TRUE;
}