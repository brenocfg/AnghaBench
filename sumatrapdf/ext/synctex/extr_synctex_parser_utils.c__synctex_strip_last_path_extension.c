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
 char* strstr (char*,char*) ; 

void _synctex_strip_last_path_extension(char * string) {
	if(NULL != string){
		char * last_component = NULL;
		char * last_extension = NULL;
		char * next = NULL;
		/*  first we find the last path component */
		if(NULL == (last_component = strstr(string,"/"))){
			last_component = string;
		} else {
			++last_component;
			while((next = strstr(last_component,"/"))){
				last_component = next+1;
			}
		}
#       ifdef	SYNCTEX_WINDOWS
		/*  On Windows, the '\' is also a path separator. */
		while((next = strstr(last_component,"\\"))){
			last_component = next+1;
		}
#       endif
		/*  then we find the last path extension */
		if((last_extension = strstr(last_component,"."))){
			++last_extension;
			while((next = strstr(last_extension,"."))){
				last_extension = next+1;
			}
			--last_extension;/*  back to the "." */
			if(last_extension>last_component){/*  filter out paths like ....my/dir/.hidden"*/
				last_extension[0] = '\0';
			}
		}
	}
}