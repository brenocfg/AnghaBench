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
struct vlc_memstream {char* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mrl_EscapeFragmentIdentifier (char**,char const*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,char*) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,char) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char const*) ; 

__attribute__((used)) static char*
StreamExtractorCreateMRL( char const* base, char const* subentry )
{
    struct vlc_memstream buffer;
    char* escaped;

    if( mrl_EscapeFragmentIdentifier( &escaped, subentry ) )
        return NULL;

    if( vlc_memstream_open( &buffer ) )
    {
        free( escaped );
        return NULL;
    }

    vlc_memstream_puts( &buffer, base );

    if( !strstr( base, "#" ) )
        vlc_memstream_putc( &buffer, '#' );

    vlc_memstream_printf( &buffer, "!/%s", escaped );

    free( escaped );
    return vlc_memstream_close( &buffer ) ? NULL : buffer.ptr;
}