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
 int asprintf (char**,char*,char const*,char*) ; 
 char** calloc (unsigned int,int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char **paths_to_list( const char *psz_dir, char *psz_path )
{
    unsigned int i, k, i_nb_subdirs;
    char **subdirs; /* list of subdirectories to look in */
    char *psz_parser = psz_path;

    if( !psz_dir || !psz_path )
        return NULL;

    for( k = 0, i_nb_subdirs = 1; psz_path[k] != '\0'; k++ )
    {
        if( psz_path[k] == ',' )
            i_nb_subdirs++;
    }

    subdirs = calloc( i_nb_subdirs + 1, sizeof(char*) );
    if( !subdirs )
        return NULL;

    for( i = 0; psz_parser && *psz_parser != '\0' ; )
    {
        char *psz_subdir = psz_parser;
        psz_parser = strchr( psz_subdir, ',' );
        if( psz_parser )
        {
            *psz_parser++ = '\0';
            while( *psz_parser == ' ' )
                psz_parser++;
        }
        if( *psz_subdir == '\0' )
            continue;

        if( asprintf( &subdirs[i++], "%s%s",
                  psz_subdir[0] == '.' ? psz_dir : "",
                  psz_subdir ) == -1 )
            break;
    }
    subdirs[i] = NULL;

    return subdirs;
}