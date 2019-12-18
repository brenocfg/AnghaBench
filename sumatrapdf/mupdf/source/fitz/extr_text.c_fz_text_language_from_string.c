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
 int FZ_LANG_UNSET ; 
 int FZ_LANG_zh_Hans ; 
 int FZ_LANG_zh_Hant ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

fz_text_language fz_text_language_from_string(const char *str)
{
	fz_text_language lang;

	if (str == NULL)
		return FZ_LANG_UNSET;

	if (!strcmp(str, "zh-Hant") ||
			!strcmp(str, "zh-HK") ||
			!strcmp(str, "zh-MO") ||
			!strcmp(str, "zh-SG") ||
			!strcmp(str, "zh-TW"))
		return FZ_LANG_zh_Hant;
	if (!strcmp(str, "zh-Hans") ||
			!strcmp(str, "zh-CN"))
		return FZ_LANG_zh_Hans;

	/* 1st char */
	if (str[0] >= 'a' && str[0] <= 'z')
		lang = str[0] - 'a' + 1;
	else if (str[0] >= 'A' && str[0] <= 'Z')
		lang = str[0] - 'A' + 1;
	else
		return 0;

	/* 2nd char */
	if (str[1] >= 'a' && str[1] <= 'z')
		lang += 27*(str[1] - 'a' + 1);
	else if (str[1] >= 'A' && str[1] <= 'Z')
		lang += 27*(str[1] - 'A' + 1);
	else
		return 0; /* There are no valid 1 char language codes */

	/* 3nd char */
	if (str[2] >= 'a' && str[2] <= 'z')
		lang += 27*27*(str[2] - 'a' + 1);
	else if (str[2] >= 'A' && str[2] <= 'Z')
		lang += 27*27*(str[2] - 'A' + 1);

	/* We don't support iso 639-6 4 char codes, cos the standard
	 * has been withdrawn, and no one uses them. */
	return lang;
}