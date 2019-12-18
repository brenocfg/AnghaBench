#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* synctex_scanner_t ;
struct TYPE_6__ {char* output; } ;

/* Variables and functions */
 scalar_t__ SYNCTEX_IS_PATH_SEPARATOR (char const) ; 
 int _synctex_scanner_get_tag (TYPE_1__*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 TYPE_1__* synctex_scanner_parse (TYPE_1__*) ; 

int synctex_scanner_get_tag(synctex_scanner_t scanner,const char * name) {
	size_t char_index = strlen(name);
	if ((scanner = synctex_scanner_parse(scanner)) && (0 < char_index)) {
		/*  the name is not void */
		char_index -= 1;
		if (!SYNCTEX_IS_PATH_SEPARATOR(name[char_index])) {
			/*  the last character of name is not a path separator */
			int result = _synctex_scanner_get_tag(scanner,name);
			if (result) {
				return result;
			} else {
				/*  the given name was not the one known by TeX
				 *  try a name relative to the enclosing directory of the scanner->output file */
				const char * relative = name;
				const char * ptr = scanner->output;
				while((strlen(relative) > 0) && (strlen(ptr) > 0) && (*relative == *ptr))
				{
					relative += 1;
					ptr += 1;
				}
				/*  Find the last path separator before relative */
				while(relative > name) {
					if (SYNCTEX_IS_PATH_SEPARATOR(*(relative-1))) {
						break;
					}
					relative -= 1;
				}
				if ((relative > name) && (result = _synctex_scanner_get_tag(scanner,relative))) {
					return result;
				}
				if (SYNCTEX_IS_PATH_SEPARATOR(name[0])) {
					/*  No tag found for the given absolute name,
					 *  Try each relative path starting from the shortest one */
					while(0<char_index) {
						char_index -= 1;
						if (SYNCTEX_IS_PATH_SEPARATOR(name[char_index])
								&& (result = _synctex_scanner_get_tag(scanner,name+char_index+1))) {
							return result;
						}
					}
				}
			}
			return result;
		}
	}
	return 0;
}