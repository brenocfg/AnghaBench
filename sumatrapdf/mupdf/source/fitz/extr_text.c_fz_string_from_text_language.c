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
typedef  int fz_text_language ;

/* Variables and functions */
 int FZ_LANG_zh_Hans ; 
 int FZ_LANG_zh_Hant ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 

char *fz_string_from_text_language(char str[8], fz_text_language lang)
{
	int c;

	/* str is supposed to be at least 8 chars in size */
	if (str == NULL)
		return NULL;

	if (lang == FZ_LANG_zh_Hant)
		fz_strlcpy(str, "zh-Hant", 8);
	else if (lang == FZ_LANG_zh_Hans)
		fz_strlcpy(str, "zh-Hans", 8);
	else
	{
		c = lang % 27;
		lang = lang / 27;
		str[0] = c == 0 ? 0 : c - 1 + 'a';
		c = lang % 27;
		lang = lang / 27;
		str[1] = c == 0 ? 0 : c - 1 + 'a';
		c = lang % 27;
		str[2] = c == 0 ? 0 : c - 1 + 'a';
		str[3] = 0;
	}

	return str;
}