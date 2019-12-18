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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ReadLine( char **ppsz_line, size_t *pi_size, FILE *p_file )
{
    ssize_t read = getline( ppsz_line, pi_size, p_file );

    if( read == -1 )
    {
        /* automatically free buffer on eof */
        free( *ppsz_line );
        *ppsz_line = NULL;
        return false;
    }

    if( read > 0 && (*ppsz_line)[ read - 1 ] == '\n' )
        (*ppsz_line)[ read - 1 ] = '\0';
    EnsureUTF8( *ppsz_line );

    return true;
}