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
 int /*<<< orphan*/  strncat (char*,char const*,scalar_t__) ; 
 scalar_t__ strnlen (char*,int) ; 

__attribute__((used)) static void Eia608Strlcat( char *d, const char *s, int i_max )
{
    if( i_max > 1 )
        strncat( d, s, i_max-1 - strnlen(d, i_max-1));
    if( i_max > 0 )
        d[i_max-1] = '\0';
}