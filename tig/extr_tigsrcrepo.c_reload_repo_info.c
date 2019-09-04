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
struct repo_info_state {char const** member_0; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int io_run_load (char const**,char*,int /*<<< orphan*/ ,struct repo_info_state*) ; 
 int /*<<< orphan*/  read_repo_info ; 

__attribute__((used)) static enum status_code
reload_repo_info(const char **rev_parse_argv)
{
	struct repo_info_state state = { rev_parse_argv + 2 };

	return io_run_load(rev_parse_argv, "\n", read_repo_info, &state);
}