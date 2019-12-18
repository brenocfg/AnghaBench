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
typedef  int OPJ_UINT32 ;

/* Variables and functions */
 int T1_LUT_SGN_E ; 
 int T1_LUT_SGN_N ; 
 int T1_LUT_SGN_S ; 
 int T1_LUT_SGN_W ; 
 int T1_LUT_SIG_E ; 
 int T1_LUT_SIG_N ; 
 int T1_LUT_SIG_S ; 
 int T1_LUT_SIG_W ; 
 int opj_int_min (int,int) ; 

__attribute__((used)) static int t1_init_spb(OPJ_UINT32 f)
{
    int hc, vc, n;

    hc = opj_int_min(((f & (T1_LUT_SIG_E | T1_LUT_SGN_E)) ==
                      T1_LUT_SIG_E) + ((f & (T1_LUT_SIG_W | T1_LUT_SGN_W)) == T1_LUT_SIG_W),
                     1) - opj_int_min(((f & (T1_LUT_SIG_E | T1_LUT_SGN_E)) ==
                                       (T1_LUT_SIG_E | T1_LUT_SGN_E)) +
                                      ((f & (T1_LUT_SIG_W | T1_LUT_SGN_W)) ==
                                       (T1_LUT_SIG_W | T1_LUT_SGN_W)), 1);

    vc = opj_int_min(((f & (T1_LUT_SIG_N | T1_LUT_SGN_N)) ==
                      T1_LUT_SIG_N) + ((f & (T1_LUT_SIG_S | T1_LUT_SGN_S)) == T1_LUT_SIG_S),
                     1) - opj_int_min(((f & (T1_LUT_SIG_N | T1_LUT_SGN_N)) ==
                                       (T1_LUT_SIG_N | T1_LUT_SGN_N)) +
                                      ((f & (T1_LUT_SIG_S | T1_LUT_SGN_S)) ==
                                       (T1_LUT_SIG_S | T1_LUT_SGN_S)), 1);

    if (!hc && !vc) {
        n = 0;
    } else {
        n = (!(hc > 0 || (!hc && vc > 0)));
    }

    return n;
}