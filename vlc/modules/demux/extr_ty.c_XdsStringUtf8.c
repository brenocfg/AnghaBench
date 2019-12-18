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
 int /*<<< orphan*/  E2 (int,int,int) ; 

__attribute__((used)) static void XdsStringUtf8( char dst[2*32+1], const uint8_t *p_src, size_t i_src )
{
    size_t i_dst = 0;
    for( size_t i = 0; i < i_src; i++ )
    {
        switch( p_src[i] )
        {
#define E2( c, u1, u2 ) case c: dst[i_dst++] = u1; dst[i_dst++] = u2; break
        E2( 0x2a, 0xc3,0xa1); // lowercase a, acute accent
        E2( 0x5c, 0xc3,0xa9); // lowercase e, acute accent
        E2( 0x5e, 0xc3,0xad); // lowercase i, acute accent
        E2( 0x5f, 0xc3,0xb3); // lowercase o, acute accent
        E2( 0x60, 0xc3,0xba); // lowercase u, acute accent
        E2( 0x7b, 0xc3,0xa7); // lowercase c with cedilla
        E2( 0x7c, 0xc3,0xb7); // division symbol
        E2( 0x7d, 0xc3,0x91); // uppercase N tilde
        E2( 0x7e, 0xc3,0xb1); // lowercase n tilde
#undef E2
        default:
            dst[i_dst++] = p_src[i];
            break;
        }
    }
    dst[i_dst++] = '\0';
}