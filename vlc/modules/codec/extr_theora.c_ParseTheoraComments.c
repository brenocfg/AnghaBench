#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ p_description; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_5__ {int comments; int* comment_lengths; scalar_t__* user_comments; } ;
struct TYPE_7__ {TYPE_1__ tc; } ;
typedef  TYPE_3__ decoder_sys_t ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  vlc_meta_AddExtra (scalar_t__,char*,char*) ; 
 scalar_t__ vlc_meta_New () ; 

__attribute__((used)) static void ParseTheoraComments( decoder_t *p_dec )
{
    char *psz_name, *psz_value, *psz_comment;
    int i = 0;

    decoder_sys_t *p_sys = p_dec->p_sys;

    /* Regarding the th_comment structure: */

    /* The metadata is stored as a series of (tag, value) pairs, in
       length-encoded string vectors. The first occurrence of the '='
       character delimits the tag and value. A particular tag may
       occur more than once, and order is significant. The character
       set encoding for the strings is always UTF-8, but the tag names
       are limited to ASCII, and treated as case-insensitive. See the
       Theora specification, Section 6.3.3 for details. */

    /* In filling in this structure, th_decode_headerin() will
       null-terminate the user_comment strings for safety. However,
       the bitstream format itself treats them as 8-bit clean vectors,
       possibly containing null characters, and so the length array
       should be treated as their authoritative length. */
    while ( i < p_sys->tc.comments )
    {
        int clen = p_sys->tc.comment_lengths[i];
        if ( clen <= 0 || clen >= INT_MAX ) { i++; continue; }
        psz_comment = (char *)malloc( clen + 1 );
        if( !psz_comment )
            break;
        memcpy( (void*)psz_comment, (void*)p_sys->tc.user_comments[i], clen + 1 );
        psz_name = psz_comment;
        psz_value = strchr( psz_comment, '=' );
        if( psz_value )
        {
            *psz_value = '\0';
            psz_value++;

            if( !p_dec->p_description )
                p_dec->p_description = vlc_meta_New();
            /* TODO:  Since psz_value can contain NULLs see if there is an
             * instance where we need to preserve the full length of this string */
            if( p_dec->p_description )
                vlc_meta_AddExtra( p_dec->p_description, psz_name, psz_value );
        }
        free( psz_comment );
        i++;
    }
}