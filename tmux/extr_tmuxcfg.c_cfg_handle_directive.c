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
struct cmd_find_state {int dummy; } ;
struct client {int dummy; } ;
struct cfg_conds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg_add_cause (char*,char const*,size_t,char const*) ; 
 int /*<<< orphan*/  cfg_handle_elif (char const*,size_t,struct cfg_conds*,char const*,struct client*,struct cmd_find_state*) ; 
 int /*<<< orphan*/  cfg_handle_else (char const*,size_t,struct cfg_conds*) ; 
 int /*<<< orphan*/  cfg_handle_endif (char const*,size_t,struct cfg_conds*) ; 
 int /*<<< orphan*/  cfg_handle_if (char const*,size_t,struct cfg_conds*,char const*,struct client*,struct cmd_find_state*) ; 
 int /*<<< orphan*/  isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void
cfg_handle_directive(const char *p, const char *path, size_t line,
    struct cfg_conds *conds, struct client *c, struct cmd_find_state *fs)
{
	int	n = 0;

	while (p[n] != '\0' && !isspace((u_char)p[n]))
		n++;
	if (strncmp(p, "%if", n) == 0)
		cfg_handle_if(path, line, conds, p + n, c, fs);
	else if (strncmp(p, "%elif", n) == 0)
		cfg_handle_elif(path, line, conds, p + n, c, fs);
	else if (strcmp(p, "%else") == 0)
		cfg_handle_else(path, line, conds);
	else if (strcmp(p, "%endif") == 0)
		cfg_handle_endif(path, line, conds);
	else
		cfg_add_cause("%s:%zu: invalid directive: %s", path, line, p);
}