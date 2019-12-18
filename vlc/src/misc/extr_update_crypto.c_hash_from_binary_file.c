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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  gcry_md_hd_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcry_md_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * vlc_fopen (char const*,char*) ; 

__attribute__((used)) static int hash_from_binary_file( const char *psz_file, gcry_md_hd_t hd )
{
    uint8_t buffer[4096];
    size_t i_read;

    FILE *f = vlc_fopen( psz_file, "r" );
    if( !f )
        return -1;

    while( ( i_read = fread( buffer, 1, sizeof(buffer), f ) ) > 0 )
        gcry_md_write( hd, buffer, i_read );

    fclose( f );

    return 0;
}