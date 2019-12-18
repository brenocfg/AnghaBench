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
 int /*<<< orphan*/  ADD_D ; 
 int /*<<< orphan*/  ADD_DEFINE () ; 
 int ADD_STRIDE ; 
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOR_ACC (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
raidz_add_abd_cb(void *dc, void *sc, size_t size, void *private)
{
	v_t *dst = (v_t *)dc;
	const v_t *src = (v_t *)sc;
	size_t i;

	ADD_DEFINE();

	(void) private; /* unused */

	for (i = 0; i < size / sizeof (v_t); i += (2 * ADD_STRIDE)) {
		LOAD(dst + i, ADD_D);
		XOR_ACC(src + i, ADD_D);
		STORE(dst + i, ADD_D);

		LOAD(dst + i + ADD_STRIDE, ADD_D);
		XOR_ACC(src + i + ADD_STRIDE, ADD_D);
		STORE(dst + i + ADD_STRIDE, ADD_D);
	}

	return (0);
}