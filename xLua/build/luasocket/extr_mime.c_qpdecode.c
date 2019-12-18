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
typedef  int UC ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,int) ; 
 int* qpunbase ; 

__attribute__((used)) static size_t qpdecode(UC c, UC *input, size_t size, luaL_Buffer *buffer) {
    int d;
    input[size++] = c;
    /* deal with all characters we can deal */
    switch (input[0]) {
        /* if we have an escape character */
        case '=': 
            if (size < 3) return size; 
            /* eliminate soft line break */
            if (input[1] == '\r' && input[2] == '\n') return 0;
            /* decode quoted representation */
            c = qpunbase[input[1]]; d = qpunbase[input[2]];
            /* if it is an invalid, do not decode */
            if (c > 15 || d > 15) luaL_addlstring(buffer, (char *)input, 3);
            else luaL_addchar(buffer, (char) ((c << 4) + d));
            return 0;
        case '\r':
            if (size < 2) return size; 
            if (input[1] == '\n') luaL_addlstring(buffer, (char *)input, 2);
            return 0;
        default:
            if (input[0] == '\t' || (input[0] > 31 && input[0] < 127))
                luaL_addchar(buffer, input[0]);
            return 0;
    }
}