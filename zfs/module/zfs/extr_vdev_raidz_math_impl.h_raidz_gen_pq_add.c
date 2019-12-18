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
 int /*<<< orphan*/  GEN_PQ_C ; 
 int /*<<< orphan*/  GEN_PQ_D ; 
 int /*<<< orphan*/  GEN_PQ_DEFINE () ; 
 int /*<<< orphan*/  GEN_PQ_STRIDE ; 
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL2_SETUP () ; 
 int /*<<< orphan*/  P_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Q_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Q_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
raidz_gen_pq_add(void **c, const void *dc, const size_t csize,
    const size_t dsize)
{
	v_t *p = (v_t *)c[0];
	v_t *q = (v_t *)c[1];
	const v_t *d = (v_t *)dc;
	const v_t * const dend = d + (dsize / sizeof (v_t));
	const v_t * const qend = q + (csize / sizeof (v_t));

	GEN_PQ_DEFINE();

	MUL2_SETUP();

	for (; d < dend; d += GEN_PQ_STRIDE, p += GEN_PQ_STRIDE,
	    q += GEN_PQ_STRIDE) {
		LOAD(d, GEN_PQ_D);
		P_D_SYNDROME(GEN_PQ_D, GEN_PQ_C, p);
		Q_D_SYNDROME(GEN_PQ_D, GEN_PQ_C, q);
	}
	for (; q < qend; q += GEN_PQ_STRIDE) {
		Q_SYNDROME(GEN_PQ_C, q);
	}
}