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
 scalar_t__ UINT8_MAX ; 
 size_t __MIN (size_t,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline size_t Write_AnnexA_String( uint8_t *p_dest, const char *p_src )
{
    size_t i_src;
    if( p_src == NULL || !(i_src = strlen( p_src )) )
    {
        p_dest[0] = 0;
        return 1;
    }

    bool b_latin = (p_src[0] > 0x20);
    for ( size_t i=0; i< i_src && b_latin; i++ )
        b_latin &= !( p_src[i] & 0x80 );

    if( b_latin )
    {
        i_src = __MIN( i_src, UINT8_MAX );
        p_dest[0] = i_src; /* Total size */
        memcpy( &p_dest[1], p_src, i_src );
        return 1 + i_src;
    }
    else
    {
        i_src = __MIN( i_src, UINT8_MAX - 1 );
        p_dest[0] = 1 + i_src; /* Total size */
        p_dest[1] = 0x15; /* UTF8 Encoding */
        memcpy( &p_dest[2], p_src, i_src );
        return 2 + i_src;
    }
}