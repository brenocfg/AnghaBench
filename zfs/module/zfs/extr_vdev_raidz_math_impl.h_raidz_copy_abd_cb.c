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
 int /*<<< orphan*/  COPY_D ; 
 int /*<<< orphan*/  COPY_DEFINE () ; 
 int COPY_STRIDE ; 
 int /*<<< orphan*/  LOAD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
raidz_copy_abd_cb(void *dc, void *sc, size_t size, void *private)
{
	v_t *dst = (v_t *)dc;
	const v_t *src = (v_t *)sc;
	size_t i;

	COPY_DEFINE();

	(void) private; /* unused */

	for (i = 0; i < size / sizeof (v_t); i += (2 * COPY_STRIDE)) {
		LOAD(src + i, COPY_D);
		STORE(dst + i, COPY_D);

		LOAD(src + i + COPY_STRIDE, COPY_D);
		STORE(dst + i + COPY_STRIDE, COPY_D);
	}

	return (0);
}