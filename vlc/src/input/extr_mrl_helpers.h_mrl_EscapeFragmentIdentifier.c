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
 char* RFC3986_FRAGMENT ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,char const) ; 

__attribute__((used)) static inline int
mrl_EscapeFragmentIdentifier( char** out, char const* payload )
{
    struct vlc_memstream mstream;

#define RFC3986_SUBDELIMS  "!" "$" "&" "'" "(" ")" \
                           "*" "+" "," ";" "="
#define RFC3986_ALPHA      "abcdefghijklmnopqrstuvwxyz" \
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define RFC3986_DIGIT      "0123456789"
#define RFC3986_UNRESERVED RFC3986_ALPHA RFC3986_DIGIT "-" "." "_" "~"
#define RFC3986_PCHAR      RFC3986_UNRESERVED RFC3986_SUBDELIMS ":" "@"
#define RFC3986_FRAGMENT   RFC3986_PCHAR "/" "?"

    if( vlc_memstream_open( &mstream ) )
        return VLC_EGENERIC;

    for( char const* p = payload; *p; ++p )
    {
        vlc_memstream_printf( &mstream,
            ( strchr( "!?", *p ) == NULL &&
              strchr( RFC3986_FRAGMENT, *p ) ? "%c" : "%%%02hhx"), *p );
    }

#undef RFC3986_FRAGMENT
#undef RFC3986_PCHAR
#undef RFC3986_UNRESERVEd
#undef RFC3986_DIGIT
#undef RFC3986_ALPHA
#undef RFC3986_SUBDELIMS

    if( vlc_memstream_close( &mstream ) )
        return VLC_EGENERIC;

    *out = mstream.ptr;
    return VLC_SUCCESS;
}