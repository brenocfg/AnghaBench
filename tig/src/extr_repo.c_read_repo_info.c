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
struct repo_info_state {scalar_t__* argv; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
struct TYPE_2__ {int is_inside_work_tree; int /*<<< orphan*/ * head; int /*<<< orphan*/  remote; int /*<<< orphan*/ * head_id; int /*<<< orphan*/ * prefix; int /*<<< orphan*/ * cdup; int /*<<< orphan*/ * exec_dir; int /*<<< orphan*/ * git_dir; } ;

/* Variables and functions */
 char* REPO_INFO_GIT_DIR ; 
 char* REPO_INFO_RESOLVED_HEAD ; 
 char* REPO_INFO_SHOW_CDUP ; 
 char* REPO_INFO_SHOW_PREFIX ; 
 char* REPO_INFO_SYMBOLIC_HEAD ; 
 char* REPO_INFO_WORK_TREE ; 
 int STRING_SIZE (char*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  add_ref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iscommit (char*) ; 
 int /*<<< orphan*/  prefixcmp (char*,char*) ; 
 TYPE_1__ repo ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static enum status_code
read_repo_info(char *name, size_t namelen, char *value, size_t valuelen, void *data)
{
	struct repo_info_state *state = data;
	const char *arg = *state->argv ? *state->argv++ : "";

	if (!strcmp(arg, REPO_INFO_GIT_DIR)) {
		string_ncopy(repo.git_dir, name, namelen);

	} else if (!strcmp(arg, REPO_INFO_WORK_TREE)) {
		/* This can be 3 different values depending on the
		 * version of git being used. If git-rev-parse does not
		 * understand --is-inside-work-tree it will simply echo
		 * the option else either "true" or "false" is printed.
		 * Default to true for the unknown case. */
		repo.is_inside_work_tree = strcmp(name, "false") ? true : false;

	} else if (!strcmp(arg, REPO_INFO_SHOW_CDUP)) {
		string_ncopy(repo.cdup, name, namelen);
		if (repo.is_inside_work_tree)
			string_ncopy(repo.exec_dir, name, namelen);

	} else if (!strcmp(arg, REPO_INFO_SHOW_PREFIX)) {
		/* Some versions of Git does not emit anything for --show-prefix
		 * when the user is in the repository root directory. Try to detect
		 * this special case by looking at the emitted value. If it looks
		 * like a commit ID and there's no cdup path assume that no value
		 * was emitted. */
		if (!*repo.cdup && namelen == 40 && iscommit(name))
			return read_repo_info(name, namelen, value, valuelen, data);

		string_ncopy(repo.prefix, name, namelen);

	} else if (!strcmp(arg, REPO_INFO_RESOLVED_HEAD)) {
		string_ncopy(repo.head_id, name, namelen);

	} else if (!strcmp(arg, REPO_INFO_SYMBOLIC_HEAD)) {
		if (!prefixcmp(name, "refs/heads/")) {
			const char *head = name + STRING_SIZE("refs/heads/");

			string_ncopy(repo.head, head, strlen(head) + 1);
			add_ref(repo.head_id, name, repo.remote, repo.head);
		}
		state->argv++;
	}

	return SUCCESS;
}