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
 char* malloc (int) ; 
 char* max (char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strdup (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void
split_path(const char *path, char **dirname, char **filename /* OPTIONAL */)
{
    const char *result;

    /* Retrieve the file name */
    char *last_slash_1 = strrchr(path, '/');
    char *last_slash_2 = strrchr(path, '\\');

    if (last_slash_1 || last_slash_2)
        result = max(last_slash_1, last_slash_2) + 1;
    else
        result = path;

    /* Duplicate the file name for the user if needed */
    if (filename)
        *filename = strdup(result);

    /* Remove any trailing directory separators */
    while (result > path && (*(result-1) == '/' || *(result-1) == '\\'))
        result--;

    /* Retrieve and duplicate the directory */
    *dirname = malloc(result - path + 1);
    if (result > path)
        memcpy(*dirname, path, result - path);
    (*dirname)[result - path] = '\0'; // NULL-terminate
}