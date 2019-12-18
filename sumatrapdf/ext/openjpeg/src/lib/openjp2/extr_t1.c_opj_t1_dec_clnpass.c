#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int w; int h; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int OPJ_INT32 ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_VSC ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass_64x64_novsc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass_64x64_vsc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass_check_segsym (TYPE_1__*,int) ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass_generic_novsc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass_generic_vsc (TYPE_1__*,int) ; 

__attribute__((used)) static void opj_t1_dec_clnpass(
    opj_t1_t *t1,
    OPJ_INT32 bpno,
    OPJ_INT32 cblksty)
{
    if (t1->w == 64 && t1->h == 64) {
        if (cblksty & J2K_CCP_CBLKSTY_VSC) {
            opj_t1_dec_clnpass_64x64_vsc(t1, bpno);
        } else {
            opj_t1_dec_clnpass_64x64_novsc(t1, bpno);
        }
    } else {
        if (cblksty & J2K_CCP_CBLKSTY_VSC) {
            opj_t1_dec_clnpass_generic_vsc(t1, bpno);
        } else {
            opj_t1_dec_clnpass_generic_novsc(t1, bpno);
        }
    }
    opj_t1_dec_clnpass_check_segsym(t1, cblksty);
}