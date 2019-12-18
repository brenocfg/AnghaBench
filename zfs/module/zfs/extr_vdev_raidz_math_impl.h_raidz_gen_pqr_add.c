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
 size_t CODE_R ; 
 int /*<<< orphan*/  GEN_PQR_C ; 
 int /*<<< orphan*/  GEN_PQR_D ; 
 int /*<<< orphan*/  GEN_PQR_DEFINE () ; 
 int /*<<< orphan*/  GEN_PQR_STRIDE ; 
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL2_SETUP () ; 
 int /*<<< orphan*/  P_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Q_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Q_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  R_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  R_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
raidz_gen_pqr_add(void **c, const void *dc, const size_t csize,
    const size_t dsize)
{
	v_t *p = (v_t *)c[0];
	v_t *q = (v_t *)c[1];
	v_t *r = (v_t *)c[CODE_R];
	const v_t *d = (v_t *)dc;
	const v_t * const dend = d + (dsize / sizeof (v_t));
	const v_t * const qend = q + (csize / sizeof (v_t));

	GEN_PQR_DEFINE();

	MUL2_SETUP();

	for (; d < dend; d += GEN_PQR_STRIDE, p += GEN_PQR_STRIDE,
	    q += GEN_PQR_STRIDE, r += GEN_PQR_STRIDE) {
		LOAD(d, GEN_PQR_D);
		P_D_SYNDROME(GEN_PQR_D, GEN_PQR_C, p);
		Q_D_SYNDROME(GEN_PQR_D, GEN_PQR_C, q);
		R_D_SYNDROME(GEN_PQR_D, GEN_PQR_C, r);
	}
	for (; q < qend; q += GEN_PQR_STRIDE, r += GEN_PQR_STRIDE) {
		Q_SYNDROME(GEN_PQR_C, q);
		R_SYNDROME(GEN_PQR_C, r);
	}
}