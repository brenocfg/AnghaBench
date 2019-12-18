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
typedef  int /*<<< orphan*/  FT_Face ;

/* Variables and functions */
 char* FT_Get_Font_Format (int /*<<< orphan*/ ) ; 
 char* FT_Get_X11_Font_Format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int ft_font_file_kind(FT_Face face)
{
#ifdef FT_FONT_FORMATS_H
	const char *kind = FT_Get_Font_Format(face);
#else
	const char *kind = FT_Get_X11_Font_Format(face);
#endif
	if (!strcmp(kind, "TrueType")) return 2;
	if (!strcmp(kind, "Type 1")) return 1;
	if (!strcmp(kind, "CFF")) return 3;
	if (!strcmp(kind, "CID Type 1")) return 1;
	return 0;
}