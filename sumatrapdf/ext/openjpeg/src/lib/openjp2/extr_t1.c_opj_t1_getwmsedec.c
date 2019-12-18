#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t OPJ_UINT32 ;
typedef  int OPJ_INT32 ;
typedef  int OPJ_FLOAT64 ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_ARG_NOT_USED (size_t) ; 
 int opj_dwt_getnorm (size_t,size_t) ; 
 int opj_dwt_getnorm_real (size_t,size_t) ; 

__attribute__((used)) static OPJ_FLOAT64 opj_t1_getwmsedec(
    OPJ_INT32 nmsedec,
    OPJ_UINT32 compno,
    OPJ_UINT32 level,
    OPJ_UINT32 orient,
    OPJ_INT32 bpno,
    OPJ_UINT32 qmfbid,
    OPJ_FLOAT64 stepsize,
    OPJ_UINT32 numcomps,
    const OPJ_FLOAT64 * mct_norms,
    OPJ_UINT32 mct_numcomps)
{
    OPJ_FLOAT64 w1 = 1, w2, wmsedec;
    OPJ_ARG_NOT_USED(numcomps);

    if (mct_norms && (compno < mct_numcomps)) {
        w1 = mct_norms[compno];
    }

    if (qmfbid == 1) {
        w2 = opj_dwt_getnorm(level, orient);
    } else {    /* if (qmfbid == 0) */
        w2 = opj_dwt_getnorm_real(level, orient);
    }

    wmsedec = w1 * w2 * stepsize * (1 << bpno);
    wmsedec *= wmsedec * nmsedec / 8192.0;

    return wmsedec;
}