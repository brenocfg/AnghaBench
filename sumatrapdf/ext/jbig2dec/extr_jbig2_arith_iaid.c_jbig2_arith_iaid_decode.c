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
struct TYPE_3__ {int SBSYMCODELEN; int /*<<< orphan*/ * IAIDx; } ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2ArithState ;
typedef  TYPE_1__ Jbig2ArithIaidCtx ;
typedef  int /*<<< orphan*/  Jbig2ArithCx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int jbig2_arith_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stderr ; 

int
jbig2_arith_iaid_decode(Jbig2Ctx *ctx, Jbig2ArithIaidCtx *actx, Jbig2ArithState *as, int32_t *p_result)
{
    Jbig2ArithCx *IAIDx = actx->IAIDx;
    int SBSYMCODELEN = actx->SBSYMCODELEN;
    int PREV = 1;
    int D;
    int i;
    int code = 0;

    /* A.3 (2) */
    for (i = 0; i < SBSYMCODELEN; i++) {
        D = jbig2_arith_decode(as, &IAIDx[PREV], &code);
        if (code)
            return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to decode IAIDx code");
#ifdef VERBOSE
        fprintf(stderr, "IAID%x: D = %d\n", PREV, D);
#endif
        PREV = (PREV << 1) | D;
    }
    /* A.3 (3) */
    PREV -= 1 << SBSYMCODELEN;
#ifdef VERBOSE
    fprintf(stderr, "IAID result: %d\n", PREV);
#endif
    *p_result = PREV;
    return 0;
}