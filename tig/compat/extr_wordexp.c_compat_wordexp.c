#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;

/* Variables and functions */
 char** calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 

int
compat_wordexp (const char *words, wordexp_t *pwordexp, int flags)
{
	char *expanded = NULL;
	const char *home = getenv("HOME");

	if (home && words[0] == '~' && (words[1] == '/' || words[1] == 0)) {
		size_t len = strlen(home) + strlen(words + 1) + 1;
		if ((expanded = malloc(len)) && !snprintf(expanded, len, "%s%s", home, words + 1)) {
			free(expanded);
			return -1;
		}
	} else {
		expanded = strdup(words);
	}

	if (!expanded)
		return -1;

	pwordexp->we_wordv = calloc(2, sizeof(*pwordexp->we_wordv));
	if (!pwordexp->we_wordv) {
		free(expanded);
		return -1;
	}
	pwordexp->we_wordv[0] = expanded;

	return 0;
}