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
 int T1_CTXNO_ZC ; 
 int T1_SIGMA_0 ; 
 int T1_SIGMA_1 ; 
 int T1_SIGMA_2 ; 
 int T1_SIGMA_3 ; 
 int T1_SIGMA_5 ; 
 int T1_SIGMA_6 ; 
 int T1_SIGMA_7 ; 
 int T1_SIGMA_8 ; 

__attribute__((used)) static int t1_init_ctxno_zc(OPJ_UINT32 f, OPJ_UINT32 orient)
{
    int h, v, d, n, t, hv;
    n = 0;
    h = ((f & T1_SIGMA_3) != 0) + ((f & T1_SIGMA_5) != 0);
    v = ((f & T1_SIGMA_1) != 0) + ((f & T1_SIGMA_7) != 0);
    d = ((f & T1_SIGMA_0) != 0) + ((f & T1_SIGMA_2) != 0) + ((
                f & T1_SIGMA_8) != 0) + ((f & T1_SIGMA_6) != 0);

    switch (orient) {
    case 2:
        t = h;
        h = v;
        v = t;
    case 0:
    case 1:
        if (!h) {
            if (!v) {
                if (!d) {
                    n = 0;
                } else if (d == 1) {
                    n = 1;
                } else {
                    n = 2;
                }
            } else if (v == 1) {
                n = 3;
            } else {
                n = 4;
            }
        } else if (h == 1) {
            if (!v) {
                if (!d) {
                    n = 5;
                } else {
                    n = 6;
                }
            } else {
                n = 7;
            }
        } else {
            n = 8;
        }
        break;
    case 3:
        hv = h + v;
        if (!d) {
            if (!hv) {
                n = 0;
            } else if (hv == 1) {
                n = 1;
            } else {
                n = 2;
            }
        } else if (d == 1) {
            if (!hv) {
                n = 3;
            } else if (hv == 1) {
                n = 4;
            } else {
                n = 5;
            }
        } else if (d == 2) {
            if (!hv) {
                n = 6;
            } else {
                n = 7;
            }
        } else {
            n = 8;
        }
        break;
    }

    return (T1_CTXNO_ZC + n);
}