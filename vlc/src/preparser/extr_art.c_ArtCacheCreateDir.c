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
 char DIR_SEP_CHAR ; 
 int /*<<< orphan*/  EMPTY_STR (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vlc_mkdir (char const*,int) ; 

__attribute__((used)) static void ArtCacheCreateDir( const char *psz_dir )
{
    char newdir[strlen( psz_dir ) + 1];
    strcpy( newdir, psz_dir );
    char * psz_newdir = newdir;
    char * psz = psz_newdir;

    while( *psz )
    {
        while( *psz && *psz != DIR_SEP_CHAR) psz++;
        if( !*psz ) break;
        *psz = 0;
        if( !EMPTY_STR( psz_newdir ) )
            vlc_mkdir( psz_newdir, 0700 );
        *psz = DIR_SEP_CHAR;
        psz++;
    }
    vlc_mkdir( psz_dir, 0700 );
}