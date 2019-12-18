#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ct; int* bp; scalar_t__ c; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  unsigned int OPJ_BYTE ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void opj_mqc_bypass_flush_enc(opj_mqc_t *mqc, OPJ_BOOL erterm)
{
    /* Is there any bit remaining to be flushed ? */
    /* If the last output byte is 0xff, we can discard it, unless */
    /* erterm is required (I'm not completely sure why in erterm */
    /* we must output 0xff 0x2a if the last byte was 0xff instead of */
    /* discarding it, but Kakadu requires it when decoding */
    /* in -fussy mode) */
    if (mqc->ct < 7 || (mqc->ct == 7 && (erterm || mqc->bp[-1] != 0xff))) {
        OPJ_BYTE bit_value = 0;
        /* If so, fill the remaining lsbs with an alternating sequence of */
        /* 0,1,... */
        /* Note: it seems the standard only requires that for a ERTERM flush */
        /* and doesn't specify what to do for a regular BYPASS flush */
        while (mqc->ct > 0) {
            mqc->ct--;
            mqc->c += (OPJ_UINT32)(bit_value << mqc->ct);
            bit_value = (OPJ_BYTE)(1U - bit_value);
        }
        *mqc->bp = (OPJ_BYTE)mqc->c;
        /* Advance pointer so that opj_mqc_numbytes() returns a valid value */
        mqc->bp++;
    } else if (mqc->ct == 7 && mqc->bp[-1] == 0xff) {
        /* Discard last 0xff */
        assert(!erterm);
        mqc->bp --;
    } else if (mqc->ct == 8 && !erterm &&
               mqc->bp[-1] == 0x7f && mqc->bp[-2] == 0xff) {
        /* Tiny optimization: discard terminating 0xff 0x7f since it is */
        /* interpreted as 0xff 0x7f [0xff 0xff] by the decoder, and given */
        /* the bit stuffing, in fact as 0xff 0xff [0xff ..] */
        /* Happens once on opj_compress -i ../MAPA.tif -o MAPA.j2k  -M 1 */
        mqc->bp -= 2;
    }

    assert(mqc->bp[-1] != 0xff);
}