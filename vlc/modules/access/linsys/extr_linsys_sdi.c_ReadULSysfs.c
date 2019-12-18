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
 unsigned int INT_MAX ; 
 int MAXLEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fscanf (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,unsigned int) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 

__attribute__((used)) static int ReadULSysfs( const char *psz_fmt, unsigned int i_link )
{
    char psz_file[MAXLEN];
    unsigned int i_data;

    snprintf( psz_file, sizeof(psz_file), psz_fmt, i_link );

    FILE *stream = vlc_fopen( psz_file, "rt" );
    if( stream == NULL )
        return -1;

    int ret = fscanf( stream, "%u", &i_data );
    fclose( stream );

    return (ret == 1 && i_data <= INT_MAX) ? (int)i_data : -1;
}