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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 scalar_t__ eolcandidate (int) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int eolprocess(int c, int last, const char *marker, 
        luaL_Buffer *buffer)
{
    if (eolcandidate(c)) {
        if (eolcandidate(last)) {
            if (c == last) luaL_addstring(buffer, marker);
            return 0;
        } else {
            luaL_addstring(buffer, marker);
            return c;
        }
    } else {
        luaL_addchar(buffer, (char) c);
        return 0;
    }
}