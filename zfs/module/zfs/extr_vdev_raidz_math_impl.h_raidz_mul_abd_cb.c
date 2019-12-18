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
typedef  int /*<<< orphan*/  v_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL (unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL_D ; 
 int /*<<< orphan*/  MUL_DEFINE () ; 
 int MUL_STRIDE ; 
 int /*<<< orphan*/  STORE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
raidz_mul_abd_cb(void *dc, size_t size, void *private)
{
	const unsigned mul = *((unsigned *)private);
	v_t *d = (v_t *)dc;
	size_t i;

	MUL_DEFINE();

	for (i = 0; i < size / sizeof (v_t); i += (2 * MUL_STRIDE)) {
		LOAD(d + i, MUL_D);
		MUL(mul, MUL_D);
		STORE(d + i, MUL_D);

		LOAD(d + i + MUL_STRIDE, MUL_D);
		MUL(mul, MUL_D);
		STORE(d + i + MUL_STRIDE, MUL_D);
	}

	return (0);
}