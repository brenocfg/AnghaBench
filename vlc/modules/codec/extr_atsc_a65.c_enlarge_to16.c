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
typedef  char uint8_t ;

/* Variables and functions */
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 

__attribute__((used)) static char *enlarge_to16( const uint8_t *p_src, size_t i_src, uint8_t i_prefix )
{
    if( i_src == 0 )
        return NULL;

    char *psz_new_allocated = malloc( i_src * 2 + 1 );
    char *psz_new = psz_new_allocated;

    if( psz_new )
    {
        memset( psz_new, i_prefix, i_src * 2 );
        psz_new[ i_src * 2 ] = 0;
        while( i_src-- )
        {
            psz_new[1] = p_src[0];
            p_src++;
            psz_new += 2;
        }
    }
    return psz_new_allocated;
}