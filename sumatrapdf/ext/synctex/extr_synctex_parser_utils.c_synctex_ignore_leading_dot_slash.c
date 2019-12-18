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
 scalar_t__ SYNCTEX_IS_DOT (char const) ; 
 scalar_t__ SYNCTEX_IS_PATH_SEPARATOR (char const) ; 

const char * synctex_ignore_leading_dot_slash(const char * name)
{
    while(SYNCTEX_IS_DOT(*name) && SYNCTEX_IS_PATH_SEPARATOR(name[1])) {
        name += 2;
        while (SYNCTEX_IS_PATH_SEPARATOR(*name)) {
            ++name;
        }
    }
    return name;
}