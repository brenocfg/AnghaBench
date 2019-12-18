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
 int asprintf (char**,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* memchr (char const*,char,int) ; 
 char* memmove (char*,char*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 int strcspn (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 char* strndup (char*,int) ; 
 char* strstr (char const*,char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_uri_decode (char*) ; 

char *vlc_uri2path (const char *url)
{
    char *ret = NULL;
    char *end;

    char *path = strstr (url, "://");
    if (path == NULL)
        return NULL; /* unsupported scheme or invalid syntax */

    end = memchr (url, '/', path - url);
    size_t schemelen = ((end != NULL) ? end : path) - url;
    path += 3; /* skip "://" */

    /* Remove request parameters and/or HTML anchor if present */
    end = path + strcspn (path, "?#");
    path = strndup (path, end - path);
    if (unlikely(path == NULL))
        return NULL; /* boom! */

    /* Decode path */
    vlc_uri_decode (path);

    if (schemelen == 4 && !strncasecmp (url, "file", 4))
    {
#if !defined (_WIN32) && !defined (__OS2__)
        /* Leading slash => local path */
        if (*path == '/')
            return path;
        /* Local path disguised as a remote one */
        if (!strncasecmp (path, "localhost/", 10))
            return memmove (path, path + 9, strlen (path + 9) + 1);
#else
        /* cannot start with a space */
        if (*path == ' ')
            goto out;
        for (char *p = strchr (path, '/'); p; p = strchr (p + 1, '/'))
            *p = '\\';

        /* Leading backslash => local path */
        if (*path == '\\')
            return memmove (path, path + 1, strlen (path + 1) + 1);
        /* Local path disguised as a remote one */
        if (!strncasecmp (path, "localhost\\", 10))
            return memmove (path, path + 10, strlen (path + 10) + 1);
        /* UNC path */
        if (*path && asprintf (&ret, "\\\\%s", path) == -1)
            ret = NULL;
#endif
        /* non-local path :-( */
    }
    else
    if (schemelen == 2 && !strncasecmp (url, "fd", 2))
    {
        int fd = strtol (path, &end, 0);

        if (*end)
            goto out;

#if !defined( _WIN32 ) && !defined( __OS2__ )
        switch (fd)
        {
            case 0:
                ret = strdup ("/dev/stdin");
                break;
            case 1:
                ret = strdup ("/dev/stdout");
                break;
            case 2:
                ret = strdup ("/dev/stderr");
                break;
            default:
                if (asprintf (&ret, "/dev/fd/%d", fd) == -1)
                    ret = NULL;
        }
#else
        /* XXX: Does this work on WinCE? */
        if (fd < 2)
            ret = strdup ("CON");
#endif
    }

out:
    free (path);
    return ret; /* unknown scheme */
}