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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* pp_xmalloc (scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static char *wpp_default_lookup(const char *name, int type, const char *parent_name,
                                char **include_path, int include_path_count)
{
    char *cpy;
    char *cptr;
    char *path;
    const char *ccptr;
    int i, fd;

    cpy = pp_xmalloc(strlen(name)+1);
    if(!cpy)
        return NULL;
    cptr = cpy;

    for(ccptr = name; *ccptr; ccptr++)
    {
        /* Convert to forward slash */
        if(*ccptr == '\\') {
            /* kill double backslash */
            if(ccptr[1] == '\\')
                ccptr++;
            *cptr = '/';
        }else {
            *cptr = *ccptr;
        }
        cptr++;
    }
    *cptr = '\0';

    if(type && parent_name)
    {
        /* Search directory of parent include and then -I path */
        const char *p;

        if ((p = strrchr( parent_name, '/' ))) p++;
        else p = parent_name;
        path = pp_xmalloc( (p - parent_name) + strlen(cpy) + 1 );
        if(!path)
        {
            free(cpy);
            return NULL;
        }
        memcpy( path, parent_name, p - parent_name );
        strcpy( path + (p - parent_name), cpy );
        fd = open( path, O_RDONLY );
        if (fd != -1)
        {
            close( fd );
            free( cpy );
            return path;
        }
        free( path );
    }
    /* Search -I path */
    for(i = 0; i < include_path_count; i++)
    {
        path = pp_xmalloc(strlen(include_path[i]) + strlen(cpy) + 2);
        if(!path)
        {
            free(cpy);
            return NULL;
        }
        strcpy(path, include_path[i]);
        strcat(path, "/");
        strcat(path, cpy);
        fd = open( path, O_RDONLY );
        if (fd != -1)
        {
            close( fd );
            free( cpy );
            return path;
        }
        free( path );
    }
    free( cpy );
    return NULL;
}