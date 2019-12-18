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
 int FT_Get_Name_Index (void*,char*) ; 
 char** fz_duplicate_glyph_names_from_unicode (int) ; 
 int fz_unicode_from_glyph_name (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int ft_name_index(void *face, const char *name)
{
	int code = FT_Get_Name_Index(face, (char*)name);
	if (code == 0)
	{
		int unicode = fz_unicode_from_glyph_name(name);
		if (unicode)
		{
			const char **dupnames = fz_duplicate_glyph_names_from_unicode(unicode);
			while (*dupnames)
			{
				code = FT_Get_Name_Index(face, (char*)*dupnames);
				if (code)
					break;
				dupnames++;
			}
			if (code == 0)
			{
				char buf[10];
				sprintf(buf, "uni%04X", unicode);
				code = FT_Get_Name_Index(face, buf);
			}
		}
	}
	return code;
}