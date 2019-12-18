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
typedef  int /*<<< orphan*/  WINDOW ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ERR ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int mvwinnstr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,size_t) ; 
 char* string_trim_end (char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static bool
save_window_line(FILE *file, WINDOW *win, int y, char *buf, size_t bufsize)
{
	int read = mvwinnstr(win, y, 0, buf, bufsize);
	const char *out = read == ERR ? "" : string_trim_end(buf);

	return read == ERR ? false : fprintf(file, "%s\n", out) == strlen(out) + 1;
}