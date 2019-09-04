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
typedef  int /*<<< orphan*/  u_char ;
struct format_tree {int dummy; } ;
struct cmd_find_state {int /*<<< orphan*/ * wp; int /*<<< orphan*/ * wl; int /*<<< orphan*/ * s; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORMAT_NOJOBS ; 
 int /*<<< orphan*/  FORMAT_NONE ; 
 int /*<<< orphan*/  cfg_add_cause (char*,char const*,size_t) ; 
 struct format_tree* format_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* format_expand (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int format_true (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfg_check_cond(const char *path, size_t line, const char *p, int *skip,
    struct client *c, struct cmd_find_state *fs)
{
	struct format_tree	*ft;
	char			*s;
	int			 result;

	while (isspace((u_char)*p))
		p++;
	if (p[0] == '\0') {
		cfg_add_cause("%s:%zu: invalid condition", path, line);
		*skip = 1;
		return (0);
	}

	ft = format_create(NULL, NULL, FORMAT_NONE, FORMAT_NOJOBS);
	if (fs != NULL)
		format_defaults(ft, c, fs->s, fs->wl, fs->wp);
	else
		format_defaults(ft, c, NULL, NULL, NULL);
	s = format_expand(ft, p);
	result = format_true(s);
	free(s);
	format_free(ft);

	*skip = result;
	return (result);
}