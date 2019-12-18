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
typedef  char* LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL pattern_match(LPCWSTR str, LPCWSTR pattern)
{
	for( ; *str&&*pattern; str++,pattern++) {
		if (*pattern == '*') {
			do pattern++;
			while(*pattern == '*');

			if (!*pattern)
				return TRUE;

			for(; *str; str++)
				if (*str==*pattern && pattern_match(str, pattern))
					return TRUE;

			return FALSE;
		}
		else if (*str!=*pattern && *pattern!='?')
			return FALSE;
	}

	if (*str || *pattern)
		if (*pattern!='*' || pattern[1]!='\0')
			return FALSE;

	return TRUE;
}