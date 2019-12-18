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

/* Variables and functions */
 int FIRST_CHAR ; 

__attribute__((used)) static int test_buffer ( char *buf, int chunk_size, int n_chunks )
{
    char c, *p;
    int i;
    for ( c = FIRST_CHAR, p = buf; c < FIRST_CHAR + n_chunks; c++, p += chunk_size )
    {
        for ( i = 0; i < chunk_size; i++ )
            if ( p[i] != c ) return i;
    }
    return -1;
}