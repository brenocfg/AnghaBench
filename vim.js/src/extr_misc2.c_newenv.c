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
typedef  int /*<<< orphan*/  elem ;

/* Variables and functions */
 int EXTRASIZE ; 
 scalar_t__ alloc (unsigned int) ; 
 char** environ ; 
 int envsize ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
newenv()
{
    char    **env, *elem;
    int	    i, esize;

#ifdef MACOS
    /* for Mac a new, empty environment is created */
    i = 0;
#else
    for (i = 0; environ[i]; i++)
	;
#endif
    esize = i + EXTRASIZE + 1;
    env = (char **)alloc((unsigned)(esize * sizeof (elem)));
    if (env == NULL)
	return -1;

#ifndef MACOS
    for (i = 0; environ[i]; i++)
    {
	elem = (char *)alloc((unsigned)(strlen(environ[i]) + 1));
	if (elem == NULL)
	    return -1;
	env[i] = elem;
	strcpy(elem, environ[i]);
    }
#endif

    env[i] = 0;
    environ = env;
    envsize = esize;
    return 0;
}