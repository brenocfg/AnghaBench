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
 scalar_t__ SYNCTEX_IS_PATH_SEPARATOR (char const) ; 
 int strlen (char const*) ; 

const char * _synctex_last_path_component(const char * name) {
	const char * c = name+strlen(name);
	if(c>name) {
		if(!SYNCTEX_IS_PATH_SEPARATOR(*c)) {
			do {
				--c;
				if(SYNCTEX_IS_PATH_SEPARATOR(*c)) {
					return c+1;
				}
			} while(c>name);
		}
		return c;/* the last path component is the void string*/
	}
	return c;
}