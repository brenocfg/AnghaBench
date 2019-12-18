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
struct cmd_results {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  L_HORIZ ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cmd_results* do_split (int /*<<< orphan*/ ) ; 

struct cmd_results *cmd_splith(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "splitv", EXPECTED_EQUAL_TO, 0))) {
		return error;
	}
	return do_split(L_HORIZ);
}