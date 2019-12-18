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
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL2_SETUP () ; 
 int /*<<< orphan*/  P_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Q_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Q_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SYN_PQ_D ; 
 int /*<<< orphan*/  SYN_PQ_DEFINE () ; 
 int /*<<< orphan*/  SYN_PQ_X ; 
 int /*<<< orphan*/  SYN_STRIDE ; 
 size_t TARGET_X ; 
 size_t TARGET_Y ; 

__attribute__((used)) static void
raidz_syn_pq_abd(void **tc, const void *dc, const size_t tsize,
    const size_t dsize)
{
	v_t *x = (v_t *)tc[TARGET_X];
	v_t *y = (v_t *)tc[TARGET_Y];
	const v_t *d = (v_t *)dc;
	const v_t * const dend = d + (dsize / sizeof (v_t));
	const v_t * const yend = y + (tsize / sizeof (v_t));

	SYN_PQ_DEFINE();

	MUL2_SETUP();

	for (; d < dend; d += SYN_STRIDE, x += SYN_STRIDE, y += SYN_STRIDE) {
		LOAD(d, SYN_PQ_D);
		P_D_SYNDROME(SYN_PQ_D, SYN_PQ_X, x);
		Q_D_SYNDROME(SYN_PQ_D, SYN_PQ_X, y);
	}
	for (; y < yend; y += SYN_STRIDE) {
		Q_SYNDROME(SYN_PQ_X, y);
	}
}