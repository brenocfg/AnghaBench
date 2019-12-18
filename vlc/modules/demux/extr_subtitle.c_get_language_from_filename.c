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
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char * get_language_from_filename( const char * psz_sub_file )
{
    char *psz_ret = NULL;
    char *psz_tmp, *psz_language_begin;

    if( !psz_sub_file ) return NULL;
    char *psz_work = strdup( psz_sub_file );

    /* Removing extension, but leaving the dot */
    psz_tmp = strrchr( psz_work, '.' );
    if( psz_tmp )
    {
        psz_tmp[0] = '\0';
        psz_language_begin = strrchr( psz_work, '.' );
        if( psz_language_begin )
            psz_ret = strdup(++psz_language_begin);
        psz_tmp[0] = '.';
    }

    free( psz_work );
    return psz_ret;
}