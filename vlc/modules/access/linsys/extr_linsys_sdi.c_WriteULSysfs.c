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
typedef  int /*<<< orphan*/  psz_file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXLEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fprintf (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,unsigned int) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 

__attribute__((used)) static int WriteULSysfs( const char *psz_fmt, unsigned int i_link,
                         unsigned int i_buf )
{
    char psz_file[MAXLEN];

    snprintf( psz_file, sizeof(psz_file), psz_fmt, i_link );

    FILE *stream = vlc_fopen( psz_file, "wt" );
    if( stream == NULL )
        return -1;

    int ret = fprintf( stream, "%u\n", i_buf );
    fclose( stream );
    return ret;
}