#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  distotile; } ;
typedef  TYPE_1__ opj_tcd_tile_t ;
struct TYPE_26__ {int term; double distortiondec; int rate; int len; } ;
typedef  TYPE_2__ opj_tcd_pass_t ;
struct TYPE_27__ {int x0; int y0; int x1; int y1; int numbps; int totalpasses; int* data; TYPE_2__* passes; } ;
typedef  TYPE_3__ opj_tcd_cblk_enc_t ;
struct TYPE_29__ {scalar_t__ lut_ctxno_zc_orient; } ;
struct TYPE_28__ {int w; int h; int data_stride; int /*<<< orphan*/ * data; TYPE_5__ mqc; } ;
typedef  TYPE_4__ opj_t1_t ;
typedef  TYPE_5__ opj_mqc_t ;
typedef  int OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  double OPJ_FLOAT64 ;
typedef  scalar_t__ OPJ_BYTE ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_LAZY ; 
 int J2K_CCP_CBLKSTY_PTERM ; 
 int J2K_CCP_CBLKSTY_RESET ; 
 int J2K_CCP_CBLKSTY_SEGSYM ; 
 int /*<<< orphan*/  T1_CTXNO_AGG ; 
 int /*<<< orphan*/  T1_CTXNO_UNI ; 
 int /*<<< orphan*/  T1_CTXNO_ZC ; 
 scalar_t__ T1_NMSEDEC_FRACBITS ; 
 scalar_t__ T1_TYPE_MQ ; 
 scalar_t__ T1_TYPE_RAW ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lut_ctxno_zc ; 
 scalar_t__ opj_int_floorlog2 (scalar_t__) ; 
 scalar_t__ opj_int_max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  opj_mqc_bypass_flush_enc (TYPE_5__*,int) ; 
 int opj_mqc_bypass_get_extra_bytes (TYPE_5__*,int) ; 
 int /*<<< orphan*/  opj_mqc_bypass_init_enc (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_erterm_enc (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_flush (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_init_enc (TYPE_5__*,int*) ; 
 int opj_mqc_numbytes (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_reset_enc (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_resetstates (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_restart_init_enc (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_segmark_enc (TYPE_5__*) ; 
 int /*<<< orphan*/  opj_mqc_setstate (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_t1_enc_clnpass (TYPE_4__*,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ opj_t1_enc_is_term_pass (TYPE_3__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  opj_t1_enc_refpass (TYPE_4__*,scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  opj_t1_enc_sigpass (TYPE_4__*,scalar_t__,scalar_t__*,scalar_t__,int) ; 
 double opj_t1_getwmsedec (scalar_t__,int,int,int,scalar_t__,int,double,int,double const*,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void opj_t1_encode_cblk(opj_t1_t *t1,
                               opj_tcd_cblk_enc_t* cblk,
                               OPJ_UINT32 orient,
                               OPJ_UINT32 compno,
                               OPJ_UINT32 level,
                               OPJ_UINT32 qmfbid,
                               OPJ_FLOAT64 stepsize,
                               OPJ_UINT32 cblksty,
                               OPJ_UINT32 numcomps,
                               opj_tcd_tile_t * tile,
                               const OPJ_FLOAT64 * mct_norms,
                               OPJ_UINT32 mct_numcomps)
{
    OPJ_FLOAT64 cumwmsedec = 0.0;

    opj_mqc_t *mqc = &(t1->mqc);   /* MQC component */

    OPJ_UINT32 passno;
    OPJ_INT32 bpno;
    OPJ_UINT32 passtype;
    OPJ_INT32 nmsedec = 0;
    OPJ_INT32 max;
    OPJ_UINT32 i, j;
    OPJ_BYTE type = T1_TYPE_MQ;
    OPJ_FLOAT64 tempwmsedec;

#ifdef EXTRA_DEBUG
    printf("encode_cblk(x=%d,y=%d,x1=%d,y1=%d,orient=%d,compno=%d,level=%d\n",
           cblk->x0, cblk->y0, cblk->x1, cblk->y1, orient, compno, level);
#endif

    mqc->lut_ctxno_zc_orient = lut_ctxno_zc + (orient << 9);

    max = 0;
    for (i = 0; i < t1->w; ++i) {
        for (j = 0; j < t1->h; ++j) {
            OPJ_INT32 tmp = abs(t1->data[i + j * t1->data_stride]);
            max = opj_int_max(max, tmp);
        }
    }

    cblk->numbps = max ? (OPJ_UINT32)((opj_int_floorlog2(max) + 1) -
                                      T1_NMSEDEC_FRACBITS) : 0;
    if (cblk->numbps == 0) {
        cblk->totalpasses = 0;
        return;
    }

    bpno = (OPJ_INT32)(cblk->numbps - 1);
    passtype = 2;

    opj_mqc_resetstates(mqc);
    opj_mqc_setstate(mqc, T1_CTXNO_UNI, 0, 46);
    opj_mqc_setstate(mqc, T1_CTXNO_AGG, 0, 3);
    opj_mqc_setstate(mqc, T1_CTXNO_ZC, 0, 4);
    opj_mqc_init_enc(mqc, cblk->data);

    for (passno = 0; bpno >= 0; ++passno) {
        opj_tcd_pass_t *pass = &cblk->passes[passno];
        type = ((bpno < ((OPJ_INT32)(cblk->numbps) - 4)) && (passtype < 2) &&
                (cblksty & J2K_CCP_CBLKSTY_LAZY)) ? T1_TYPE_RAW : T1_TYPE_MQ;

        /* If the previous pass was terminating, we need to reset the encoder */
        if (passno > 0 && cblk->passes[passno - 1].term) {
            if (type == T1_TYPE_RAW) {
                opj_mqc_bypass_init_enc(mqc);
            } else {
                opj_mqc_restart_init_enc(mqc);
            }
        }

        switch (passtype) {
        case 0:
            opj_t1_enc_sigpass(t1, bpno, &nmsedec, type, cblksty);
            break;
        case 1:
            opj_t1_enc_refpass(t1, bpno, &nmsedec, type);
            break;
        case 2:
            opj_t1_enc_clnpass(t1, bpno, &nmsedec, cblksty);
            /* code switch SEGMARK (i.e. SEGSYM) */
            if (cblksty & J2K_CCP_CBLKSTY_SEGSYM) {
                opj_mqc_segmark_enc(mqc);
            }
            break;
        }

        /* fixed_quality */
        tempwmsedec = opj_t1_getwmsedec(nmsedec, compno, level, orient, bpno, qmfbid,
                                        stepsize, numcomps, mct_norms, mct_numcomps) ;
        cumwmsedec += tempwmsedec;
        tile->distotile += tempwmsedec;
        pass->distortiondec = cumwmsedec;

        if (opj_t1_enc_is_term_pass(cblk, cblksty, bpno, passtype)) {
            /* If it is a terminated pass, terminate it */
            if (type == T1_TYPE_RAW) {
                opj_mqc_bypass_flush_enc(mqc, cblksty & J2K_CCP_CBLKSTY_PTERM);
            } else {
                if (cblksty & J2K_CCP_CBLKSTY_PTERM) {
                    opj_mqc_erterm_enc(mqc);
                } else {
                    opj_mqc_flush(mqc);
                }
            }
            pass->term = 1;
            pass->rate = opj_mqc_numbytes(mqc);
        } else {
            /* Non terminated pass */
            OPJ_UINT32 rate_extra_bytes;
            if (type == T1_TYPE_RAW) {
                rate_extra_bytes = opj_mqc_bypass_get_extra_bytes(
                                       mqc, (cblksty & J2K_CCP_CBLKSTY_PTERM));
            } else {
                rate_extra_bytes = 3;
            }
            pass->term = 0;
            pass->rate = opj_mqc_numbytes(mqc) + rate_extra_bytes;
        }

        if (++passtype == 3) {
            passtype = 0;
            bpno--;
        }

        /* Code-switch "RESET" */
        if (cblksty & J2K_CCP_CBLKSTY_RESET) {
            opj_mqc_reset_enc(mqc);
        }
    }

    cblk->totalpasses = passno;

    if (cblk->totalpasses) {
        /* Make sure that pass rates are increasing */
        OPJ_UINT32 last_pass_rate = opj_mqc_numbytes(mqc);
        for (passno = cblk->totalpasses; passno > 0;) {
            opj_tcd_pass_t *pass = &cblk->passes[--passno];
            if (pass->rate > last_pass_rate) {
                pass->rate = last_pass_rate;
            } else {
                last_pass_rate = pass->rate;
            }
        }
    }

    for (passno = 0; passno < cblk->totalpasses; passno++) {
        opj_tcd_pass_t *pass = &cblk->passes[passno];

        /* Prevent generation of FF as last data byte of a pass*/
        /* For terminating passes, the flushing procedure ensured this already */
        assert(pass->rate > 0);
        if (cblk->data[pass->rate - 1] == 0xFF) {
            pass->rate--;
        }
        pass->len = pass->rate - (passno == 0 ? 0 : cblk->passes[passno - 1].rate);
    }

#ifdef EXTRA_DEBUG
    printf(" len=%d\n", (cblk->totalpasses) ? opj_mqc_numbytes(mqc) : 0);

    /* Check that there not 0xff >=0x90 sequences */
    if (cblk->totalpasses) {
        OPJ_UINT32 i;
        OPJ_UINT32 len = opj_mqc_numbytes(mqc);
        for (i = 1; i < len; ++i) {
            if (cblk->data[i - 1] == 0xff && cblk->data[i] >= 0x90) {
                printf("0xff %02x at offset %d\n", cblk->data[i], i - 1);
                abort();
            }
        }
    }
#endif
}