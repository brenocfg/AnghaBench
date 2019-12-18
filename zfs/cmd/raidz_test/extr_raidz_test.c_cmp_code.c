#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  const* rm_golden; } ;
typedef  TYPE_1__ raidz_test_opts_t ;
typedef  int /*<<< orphan*/  raidz_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_COL (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  D_DEBUG ; 
 int /*<<< orphan*/  LOG_OPT (int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ abd_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmp_code(raidz_test_opts_t *opts, const raidz_map_t *rm, const int parity)
{
	int i, ret = 0;

	VERIFY(parity >= 1 && parity <= 3);

	for (i = 0; i < parity; i++) {
		if (abd_cmp(CODE_COL(rm, i), CODE_COL(opts->rm_golden, i))
		    != 0) {
			ret++;
			LOG_OPT(D_DEBUG, opts,
			    "\nParity block [%d] different!\n", i);
		}
	}
	return (ret);
}