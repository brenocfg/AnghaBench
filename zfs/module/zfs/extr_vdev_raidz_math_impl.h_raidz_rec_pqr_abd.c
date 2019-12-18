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
 size_t CODE_R ; 
 int /*<<< orphan*/  COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL (unsigned int const,int /*<<< orphan*/ ) ; 
 size_t MUL_PQR_XP ; 
 size_t MUL_PQR_XQ ; 
 size_t MUL_PQR_XR ; 
 size_t MUL_PQR_YP ; 
 size_t MUL_PQR_YQ ; 
 size_t MUL_PQR_YU ; 
 int /*<<< orphan*/  REC_PQR_DEFINE () ; 
 int /*<<< orphan*/  REC_PQR_STRIDE ; 
 int /*<<< orphan*/  REC_PQR_X ; 
 int /*<<< orphan*/  REC_PQR_XS ; 
 int /*<<< orphan*/  REC_PQR_Y ; 
 int /*<<< orphan*/  REC_PQR_YS ; 
 int /*<<< orphan*/  REC_PQR_Z ; 
 int /*<<< orphan*/  STORE (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 size_t TARGET_X ; 
 size_t TARGET_Y ; 
 size_t TARGET_Z ; 
 int /*<<< orphan*/  XOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOR_ACC (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
raidz_rec_pqr_abd(void **t, const size_t tsize, void **c,
    const unsigned * const mul)
{
	v_t *x = (v_t *)t[TARGET_X];
	v_t *y = (v_t *)t[TARGET_Y];
	v_t *z = (v_t *)t[TARGET_Z];
	const v_t * const xend = x + (tsize / sizeof (v_t));
	const v_t *p = (v_t *)c[CODE_P];
	const v_t *q = (v_t *)c[CODE_Q];
	const v_t *r = (v_t *)c[CODE_R];

	REC_PQR_DEFINE();

	for (; x < xend; x += REC_PQR_STRIDE, y += REC_PQR_STRIDE,
	    z += REC_PQR_STRIDE, p += REC_PQR_STRIDE, q += REC_PQR_STRIDE,
	    r += REC_PQR_STRIDE) {
		LOAD(x, REC_PQR_X);
		LOAD(y, REC_PQR_Y);
		LOAD(z, REC_PQR_Z);

		XOR_ACC(p, REC_PQR_X);
		XOR_ACC(q, REC_PQR_Y);
		XOR_ACC(r, REC_PQR_Z);

		/* Save Pxyz and Qxyz */
		COPY(REC_PQR_X, REC_PQR_XS);
		COPY(REC_PQR_Y, REC_PQR_YS);

		/* Calc X */
		MUL(mul[MUL_PQR_XP], REC_PQR_X);	/* Xp = Pxyz * xp   */
		MUL(mul[MUL_PQR_XQ], REC_PQR_Y);	/* Xq = Qxyz * xq   */
		XOR(REC_PQR_Y, REC_PQR_X);
		MUL(mul[MUL_PQR_XR], REC_PQR_Z);	/* Xr = Rxyz * xr   */
		XOR(REC_PQR_Z, REC_PQR_X);		/* X = Xp + Xq + Xr */
		STORE(x, REC_PQR_X);

		/* Calc Y */
		XOR(REC_PQR_X, REC_PQR_XS); 		/* Pyz = Pxyz + X */
		MUL(mul[MUL_PQR_YU], REC_PQR_X);  	/* Xq = X * upd_q */
		XOR(REC_PQR_X, REC_PQR_YS); 		/* Qyz = Qxyz + Xq */
		COPY(REC_PQR_XS, REC_PQR_X);		/* restore Pyz */
		MUL(mul[MUL_PQR_YP], REC_PQR_X);	/* Yp = Pyz * yp */
		MUL(mul[MUL_PQR_YQ], REC_PQR_YS);	/* Yq = Qyz * yq */
		XOR(REC_PQR_X, REC_PQR_YS); 		/* Y = Yp + Yq */
		STORE(y, REC_PQR_YS);

		/* Calc Z */
		XOR(REC_PQR_XS, REC_PQR_YS);		/* Z = Pz = Pyz + Y */
		STORE(z, REC_PQR_YS);
	}
}