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
 int atoi (char const*) ; 
 int /*<<< orphan*/  put_word (int) ; 
 int toupper (unsigned char) ; 

__attribute__((used)) static inline void put_resource_id( const char *str )
{
    if (str[0] != '#')
    {
        while (*str)
        {
            unsigned char ch = *str++;
            put_word( toupper(ch) );
        }
        put_word( 0 );
    }
    else
    {
        put_word( 0xffff );
        put_word( atoi( str + 1 ));
    }
}