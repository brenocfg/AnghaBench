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
typedef  int /*<<< orphan*/  const v_t ;

/* Variables and functions */
 size_t CODE_P ; 
 size_t CODE_Q ; 
 int /*<<< orphan*/  COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL (unsigned int const,int /*<<< orphan*/ ) ; 
 size_t MUL_PQ_X ; 
 size_t MUL_PQ_Y ; 
 int /*<<< orphan*/  REC_PQ_DEFINE () ; 
 int /*<<< orphan*/  REC_PQ_STRIDE ; 
 int /*<<< orphan*/  REC_PQ_T ; 
 int /*<<< orphan*/  REC_PQ_X ; 
 int /*<<< orphan*/  REC_PQ_Y ; 
 int /*<<< orphan*/  STORE (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 size_t TARGET_X ; 
 size_t TARGET_Y ; 
 int /*<<< orphan*/  XOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOR_ACC (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
raidz_rec_pq_abd(void **tc, const size_t tsize, void **c,
    const unsigned *mul)
{
	v_t *x = (v_t *)tc[TARGET_X];
	v_t *y = (v_t *)tc[TARGET_Y];
	const v_t * const xend = x + (tsize / sizeof (v_t));
	const v_t *p = (v_t *)c[CODE_P];
	const v_t *q = (v_t *)c[CODE_Q];

	REC_PQ_DEFINE();

	for (; x < xend; x += REC_PQ_STRIDE, y += REC_PQ_STRIDE,
	    p += REC_PQ_STRIDE, q += REC_PQ_STRIDE) {
		LOAD(x, REC_PQ_X);
		LOAD(y, REC_PQ_Y);

		XOR_ACC(p, REC_PQ_X);
		XOR_ACC(q, REC_PQ_Y);

		/* Save Pxy */
		COPY(REC_PQ_X,  REC_PQ_T);

		/* Calc X */
		MUL(mul[MUL_PQ_X], REC_PQ_X);
		MUL(mul[MUL_PQ_Y], REC_PQ_Y);
		XOR(REC_PQ_Y,  REC_PQ_X);
		STORE(x, REC_PQ_X);

		/* Calc Y */
		XOR(REC_PQ_T,  REC_PQ_X);
		STORE(y, REC_PQ_X);
	}
}