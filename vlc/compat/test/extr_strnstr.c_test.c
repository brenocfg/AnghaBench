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
 int /*<<< orphan*/  assert (int) ; 
 size_t strlen (char const*) ; 
 char* strnstr (char const*,char const*,size_t) ; 

__attribute__((used)) static void test( const char* haystack, const char* needle, size_t len, bool res )
{
    if ( len == 0 )
        len = strlen( haystack );
    char* str = strnstr( haystack, needle, len );
    assert( res == ( str != NULL ) );
}