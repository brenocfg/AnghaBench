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
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * IAx; } ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2ArithState ;
typedef  TYPE_1__ Jbig2ArithIntCtx ;
typedef  int /*<<< orphan*/  Jbig2ArithCx ;

/* Variables and functions */
 int INT32_MAX ; 
 int INT32_MIN ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int jbig2_arith_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,...) ; 

int
jbig2_arith_int_decode(Jbig2Ctx *ctx, Jbig2ArithIntCtx *actx, Jbig2ArithState *as, int32_t *p_result)
{
    Jbig2ArithCx *IAx = actx->IAx;
    int PREV = 1;
    int S;
    int32_t V;
    int bit;
    int n_tail, offset;
    int i;
    int code = 0;

    S = jbig2_arith_decode(as, &IAx[PREV], &code);
    if (code)
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAx S");
    PREV = (PREV << 1) | S;

    bit = jbig2_arith_decode(as, &IAx[PREV], &code);
    if (code)
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAx decision bit 0");
    PREV = (PREV << 1) | bit;
    if (bit) {
        bit = jbig2_arith_decode(as, &IAx[PREV], &code);
        if (code)
            return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAx decision bit 1");
        PREV = (PREV << 1) | bit;

        if (bit) {
            bit = jbig2_arith_decode(as, &IAx[PREV], &code);
            if (code)
                return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAx decision bit 2");
            PREV = (PREV << 1) | bit;

            if (bit) {
                bit = jbig2_arith_decode(as, &IAx[PREV], &code);
                if (code)
                    return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAx decision bit 3");
                PREV = (PREV << 1) | bit;

                if (bit) {
                    bit = jbig2_arith_decode(as, &IAx[PREV], &code);
                    if (code)
                        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAx decision bit 4");
                    PREV = (PREV << 1) | bit;

                    if (bit) {
                        n_tail = 32;
                        offset = 4436;
                    } else {
                        n_tail = 12;
                        offset = 340;
                    }
                } else {
                    n_tail = 8;
                    offset = 84;
                }
            } else {
                n_tail = 6;
                offset = 20;
            }
        } else {
            n_tail = 4;
            offset = 4;
        }
    } else {
        n_tail = 2;
        offset = 0;
    }

    V = 0;
    for (i = 0; i < n_tail; i++) {
        bit = jbig2_arith_decode(as, &IAx[PREV], &code);
        if (code)
            return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAx V bit %d", i);
        PREV = ((PREV << 1) & 511) | (PREV & 256) | bit;
        V = (V << 1) | bit;
    }

    /* make sure not to underflow/overflow 32 bit value */
    if (V < INT32_MAX - 4436 || V > INT32_MIN + 4436)
        V += offset;
    V = S ? -V : V;
    *p_result = V;
    return S && V == 0 ? 1 : 0;
}