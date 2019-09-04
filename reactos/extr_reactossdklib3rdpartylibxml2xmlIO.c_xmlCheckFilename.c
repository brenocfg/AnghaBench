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

int
xmlCheckFilename (const char *path)
{
#ifdef HAVE_STAT
#if defined(_WIN32) || defined (__DJGPP__) && !defined (__CYGWIN__)
    struct _stat stat_buffer;
#else
    struct stat stat_buffer;
#endif
#endif
    if (path == NULL)
	return(0);

#ifdef HAVE_STAT
#if defined(_WIN32) || defined (__DJGPP__) && !defined (__CYGWIN__)
    /*
     * On Windows stat and wstat do not work with long pathname,
     * which start with '\\?\'
     */
    if ((path[0] == '\\') && (path[1] == '\\') && (path[2] == '?') &&
	(path[3] == '\\') )
	    return 1;

    if (xmlWrapStatUtf8(path, &stat_buffer) == -1)
        return 0;
#else
    if (stat(path, &stat_buffer) == -1)
        return 0;
#endif
#ifdef S_ISDIR
    if (S_ISDIR(stat_buffer.st_mode))
        return 2;
#endif
#endif /* HAVE_STAT */
    return 1;
}