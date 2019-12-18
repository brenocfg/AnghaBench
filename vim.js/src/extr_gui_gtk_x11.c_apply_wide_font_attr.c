#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {int /*<<< orphan*/  wide_font; } ;
typedef  int /*<<< orphan*/  PangoAttrList ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_PANGO_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  pango_attr_font_desc_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf_byte2len (int /*<<< orphan*/ ) ; 
 int utf_char2cells (int) ; 
 int /*<<< orphan*/  utf_iscomposing (int) ; 
 int utf_ptr2char (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
apply_wide_font_attr(char_u *s, int len, PangoAttrList *attr_list)
{
    char_u  *start = NULL;
    char_u  *p;
    int	    uc;

    for (p = s; p < s + len; p += utf_byte2len(*p))
    {
	uc = utf_ptr2char(p);

	if (start == NULL)
	{
	    if (uc >= 0x80 && utf_char2cells(uc) == 2)
		start = p;
	}
	else if (uc < 0x80 /* optimization shortcut */
		 || (utf_char2cells(uc) != 2 && !utf_iscomposing(uc)))
	{
	    INSERT_PANGO_ATTR(pango_attr_font_desc_new(gui.wide_font),
			      attr_list, start - s, p - s);
	    start = NULL;
	}
    }

    if (start != NULL)
	INSERT_PANGO_ATTR(pango_attr_font_desc_new(gui.wide_font),
			  attr_list, start - s, len);
}