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
 size_t MUL_QR_X ; 
 size_t MUL_QR_XQ ; 
 size_t MUL_QR_Y ; 
 size_t MUL_QR_YQ ; 
 int /*<<< orphan*/  REC_QR_DEFINE () ; 
 int /*<<< orphan*/  REC_QR_STRIDE ; 
 int /*<<< orphan*/  REC_QR_T ; 
 int /*<<< orphan*/  REC_QR_X ; 
 int /*<<< orphan*/  REC_QR_Y ; 
 int /*<<< orphan*/  STORE (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 size_t TARGET_X ; 
 size_t TARGET_Y ; 
 int /*<<< orphan*/  XOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOR_ACC (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
raidz_rec_qr_abd(void **t, const size_t tsize, void **c,
    const unsigned *mul)
{
	v_t *x = (v_t *)t[TARGET_X];
	v_t *y = (v_t *)t[TARGET_Y];
	const v_t * const xend = x + (tsize / sizeof (v_t));
	const v_t *p = (v_t *)c[CODE_P];
	const v_t *q = (v_t *)c[CODE_Q];

	REC_QR_DEFINE();

	for (; x < xend; x += REC_QR_STRIDE, y += REC_QR_STRIDE,
	    p += REC_QR_STRIDE, q += REC_QR_STRIDE) {
		LOAD(x, REC_QR_X);
		LOAD(y, REC_QR_Y);

		XOR_ACC(p, REC_QR_X);
		XOR_ACC(q, REC_QR_Y);

		/* Save Pxy */
		COPY(REC_QR_X,  REC_QR_T);

		/* Calc X */
		MUL(mul[MUL_QR_XQ], REC_QR_X);	/* X = Q * xqm */
		XOR(REC_QR_Y, REC_QR_X);	/* X = R ^ X   */
		MUL(mul[MUL_QR_X], REC_QR_X);	/* X = X * xm  */
		STORE(x, REC_QR_X);

		/* Calc Y */
		MUL(mul[MUL_QR_YQ], REC_QR_T);	/* X = Q * xqm */
		XOR(REC_QR_Y, REC_QR_T);	/* X = R ^ X   */
		MUL(mul[MUL_QR_Y], REC_QR_T);	/* X = X * xm  */
		STORE(y, REC_QR_T);
	}
}