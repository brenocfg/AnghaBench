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
typedef  int uint8_t ;

/* Variables and functions */
 char* FromCharset (char*,int const*,size_t) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int const*,size_t) ; 

__attribute__((used)) static const char * ID3TextConv( const uint8_t *p_buf, size_t i_buf,
                                 uint8_t i_charset, char **ppsz_allocated )
{
    char *p_alloc = NULL;
    const char *psz = p_alloc;
    if( i_buf > 0 && i_charset < 0x04 )
    {
        switch( i_charset )
        {
            case 0x00:
                psz = p_alloc = FromCharset( "ISO_8859-1", p_buf, i_buf );
                break;
            case 0x01:
                psz = p_alloc = FromCharset( "UTF-16LE", p_buf, i_buf );
                break;
            case 0x02:
                psz = p_alloc = FromCharset( "UTF-16BE", p_buf, i_buf );
                break;
            default:
            case 0x03:
                if( p_buf[ i_buf - 1 ] != 0x00 )
                {
                    psz = p_alloc = (char *) malloc( i_buf + 1 );
                    if( p_alloc )
                    {
                        memcpy( p_alloc, p_buf, i_buf - 1 );
                        p_alloc[i_buf] = '\0';
                    }
                }
                else
                {
                    psz = (const char *) p_buf;
                }
                break;
        }
    }
    *ppsz_allocated = p_alloc;
    return psz;
}