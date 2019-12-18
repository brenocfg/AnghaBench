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
 int /*<<< orphan*/  strspn (char const*,char*) ; 

__attribute__((used)) static bool IsWhitespace( const char *psz_string )
{
    psz_string += strspn( psz_string, " \t\r\n" );
    return !*psz_string;
}