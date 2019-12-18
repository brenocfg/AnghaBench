#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ iconv_u16be; } ;
typedef  TYPE_1__ atsc_a65_handle_t ;

/* Variables and functions */
 scalar_t__ VLC_ICONV_ERR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t const) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_iconv (scalar_t__,char const**,size_t*,char**,size_t*) ; 
 scalar_t__ vlc_iconv_open (char*,char*) ; 

char * atsc_a65_Decode_simple_UTF16_string( atsc_a65_handle_t *p_handle, const uint8_t *p_buffer, size_t i_buffer )
{
    if( i_buffer < 1 )
        return NULL;

    if( !p_handle->iconv_u16be )
    {
        if ( !(p_handle->iconv_u16be = vlc_iconv_open("UTF-8", "UTF-16BE")) )
            return NULL;
    }
    else if ( VLC_ICONV_ERR == vlc_iconv( p_handle->iconv_u16be, NULL, NULL, NULL, NULL ) ) /* reset */
    {
        return NULL;
    }

    const size_t i_target_buffer = i_buffer * 3 / 2;
    size_t i_target_remaining = i_target_buffer;
    const char *psz_toconvert = (const char *) p_buffer;
    char *psz_converted_end;
    char *psz_converted = psz_converted_end = malloc( i_target_buffer );

    if( unlikely(!psz_converted) )
        return NULL;

    if( VLC_ICONV_ERR == vlc_iconv( p_handle->iconv_u16be, &psz_toconvert, &i_buffer,
                                                           &psz_converted_end, &i_target_remaining ) )
    {
        free( psz_converted );
        psz_converted = NULL;
    }
    else
        psz_converted[ i_target_buffer - i_target_remaining - 1 ] = 0;

    return psz_converted;
}