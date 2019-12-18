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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline int scalar_number( const uint8_t *p, int header_len )
{
    assert( header_len == 1 || header_len == 2 || header_len == 4 );

    if( header_len == 1 )
        return( p[0] );
    else if( header_len == 2 )
        return( (p[0] << 8) + p[1] );
    else if( header_len == 4 )
        return( (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3] );
    else
        abort();
}