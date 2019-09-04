#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum status_code { ____Placeholder_status_code } status_code ;
struct TYPE_2__ {int /*<<< orphan*/  head_id; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 char* REPO_INFO_RESOLVED_HEAD ; 
 char* REPO_INFO_SYMBOLIC_HEAD ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int reload_repo_info (char const**) ; 
 TYPE_1__ repo ; 

enum status_code
load_repo_head(void)
{
	const char *rev_parse_argv[] = {
		"git", "rev-parse", REPO_INFO_RESOLVED_HEAD,
			REPO_INFO_SYMBOLIC_HEAD, "HEAD", NULL
	};

	memset(repo.head, 0, sizeof(repo.head));
	memset(repo.head_id, 0, sizeof(repo.head_id));
	return reload_repo_info(rev_parse_argv);
}