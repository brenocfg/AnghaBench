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
 int /*<<< orphan*/  R_D_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  R_SYNDROME (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SYN_R_D ; 
 int /*<<< orphan*/  SYN_R_DEFINE () ; 
 int /*<<< orphan*/  SYN_R_X ; 
 int /*<<< orphan*/  SYN_STRIDE ; 
 size_t TARGET_X ; 

__attribute__((used)) static void
raidz_syn_r_abd(void **xc, const void *dc, const size_t tsize,
    const size_t dsize)
{
	v_t *x = (v_t *)xc[TARGET_X];
	const v_t *d = (v_t *)dc;
	const v_t * const dend = d + (dsize / sizeof (v_t));
	const v_t * const xend = x + (tsize / sizeof (v_t));

	SYN_R_DEFINE();

	MUL2_SETUP();

	for (; d < dend; d += SYN_STRIDE, x += SYN_STRIDE) {
		LOAD(d, SYN_R_D);
		R_D_SYNDROME(SYN_R_D, SYN_R_X, x);
	}
	for (; x < xend; x += SYN_STRIDE) {
		R_SYNDROME(SYN_R_X, x);
	}
}