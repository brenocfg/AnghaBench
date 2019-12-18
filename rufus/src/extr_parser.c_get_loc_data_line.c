#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ command; } ;
typedef  TYPE_1__ loc_cmd ;

/* Variables and functions */
 scalar_t__ LC_LOCALE ; 
 int /*<<< orphan*/  dispatch_loc_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  free_loc_cmd (TYPE_1__*) ; 
 TYPE_1__* get_loc_cmd (char,char*) ; 
 int /*<<< orphan*/  luprintf (char*,char*) ; 
 char* space ; 
 size_t strspn (char*,char*) ; 

__attribute__((used)) static void get_loc_data_line(char* line)
{
	size_t i;
	loc_cmd* lcmd = NULL;
	char t;

	if ((line == NULL) || (line[0] == 0))
		return;

	// Skip leading spaces
	i = strspn(line, space);

	// Read token (NUL character will be read if EOL)
	t = line[i++];
	if (t == '#')	// Comment
		return;
	if ((t == 0) || ((line[i] != space[0]) && (line[i] != space[1]))) {
		luprintf("syntax error: '%s'", line);
		return;
	}

	lcmd = get_loc_cmd(t, &line[i]);

	if ((lcmd != NULL) && (lcmd->command != LC_LOCALE))
		// TODO: check return value?
		dispatch_loc_cmd(lcmd);
	else
		free_loc_cmd(lcmd);
}