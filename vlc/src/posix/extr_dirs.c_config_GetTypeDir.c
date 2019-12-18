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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t const) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 

__attribute__((used)) static char *config_GetTypeDir (const char *xdg_name)
{
    const size_t namelen = strlen (xdg_name);
    const char *home = getenv ("HOME");
    const char *dir = getenv ("XDG_CONFIG_HOME");
    const char *file = "user-dirs.dirs";

    if (home == NULL)
        return NULL;
    if (dir == NULL)
    {
        dir = home;
        file = ".config/user-dirs.dirs";
    }

    char *path;
    if (asprintf (&path, "%s/%s", dir, file) == -1)
        return NULL;

    FILE *stream = fopen (path, "rte");
    free (path);
    path = NULL;
    if (stream != NULL)
    {
        char *linebuf = NULL;
        size_t linelen = 0;

        while (getline (&linebuf, &linelen, stream) != -1)
        {
            char *ptr = linebuf;
            ptr += strspn (ptr, " \t"); /* Skip whites */
            if (strncmp (ptr, "XDG_", 4))
                continue;
            ptr += 4; /* Skip XDG_ */
            if (strncmp (ptr, xdg_name, namelen))
                continue;
            ptr += namelen; /* Skip XDG type name */
            if (strncmp (ptr, "_DIR", 4))
                continue;
            ptr += 4; /* Skip _DIR */
            ptr += strspn (ptr, " \t"); /* Skip whites */
            if (*ptr != '=')
                continue;
            ptr++; /* Skip equality sign */
            ptr += strspn (ptr, " \t"); /* Skip whites */
            if (*ptr != '"')
                continue;
            ptr++; /* Skip quote */
            linelen -= ptr - linebuf;

            char *out;
            if (strncmp (ptr, "$HOME", 5))
            {
                path = malloc (linelen);
                if (path == NULL)
                    continue;
                out = path;
            }
            else
            {   /* Prefix with $HOME */
                const size_t homelen = strlen (home);
                ptr += 5;
                path = malloc (homelen + linelen - 5);
                if (path == NULL)
                    continue;
                memcpy (path, home, homelen);
                out = path + homelen;
            }

            while (*ptr != '"')
            {
                if (*ptr == '\\')
                    ptr++;
                if (*ptr == '\0')
                {
                    free (path);
                    path = NULL;
                    break;
                }
                *(out++) = *(ptr++);
            }
            if (path != NULL)
                *out = '\0';
            break;
        }
        free (linebuf);
        fclose (stream);
    }

    /* Default! */
    if (path == NULL)
    {
        if (strcmp (xdg_name, "DESKTOP") == 0)
        {
            if (asprintf (&path, "%s/Desktop", home) == -1)
                return NULL;
        }
        else
            path = strdup (home);
    }

    return path;
}