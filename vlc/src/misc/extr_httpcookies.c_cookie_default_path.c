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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 
 char* strndup (char const*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *cookie_default_path( const char *request_path )
{
    if ( request_path == NULL || request_path[0] != '/' )
        return strdup("/");

    char *path;
    const char *query_start = strchr( request_path, '?' );
    if ( query_start != NULL )
        path = strndup( request_path, query_start - request_path );
    else
        path = strdup( request_path );

    if ( path == NULL )
        return NULL;

    char *last_slash = strrchr(path, '/');
    assert(last_slash != NULL);
    if ( last_slash == path )
        path[1] = '\0';
    else
        *last_slash = '\0';

    return path;
}