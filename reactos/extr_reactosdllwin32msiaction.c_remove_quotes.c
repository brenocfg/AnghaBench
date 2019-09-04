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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strchrW (int /*<<< orphan*/ *,char) ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_quotes( WCHAR *str )
{
    WCHAR *p = str;
    int len = strlenW( str );

    while ((p = strchrW( p, '"' )))
    {
        memmove( p, p + 1, (len - (p - str)) * sizeof(WCHAR) );
        p++;
    }
}