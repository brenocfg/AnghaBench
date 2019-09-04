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

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getchar () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strchr (char const*,int) ; 

char get_key(const char *valid, const char *prompt)
{
#ifndef __REACTOS__
    int ch, okay;

    while (1) {
	if (prompt)
	    printf("%s ", prompt);
	fflush(stdout);
	while (ch = getchar(), ch == ' ' || ch == '\t') ;
	if (ch == EOF)
	    exit(1);
	if (!strchr(valid, okay = ch))
	    okay = 0;
	while (ch = getchar(), ch != '\n' && ch != EOF) ;
	if (ch == EOF)
	    exit(1);
	if (okay)
	    return okay;
	printf("Invalid input.\n");
    }
#else
    return 0;
#endif
}