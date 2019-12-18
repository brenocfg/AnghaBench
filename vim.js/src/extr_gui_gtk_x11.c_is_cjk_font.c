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
typedef  int gunichar ;
struct TYPE_2__ {int /*<<< orphan*/  text_context; } ;
typedef  int /*<<< orphan*/  PangoFontDescription ;
typedef  int /*<<< orphan*/  PangoFont ;
typedef  int /*<<< orphan*/  PangoCoverage ;

/* Variables and functions */
 int FALSE ; 
 unsigned int G_N_ELEMENTS (char const* const*) ; 
 scalar_t__ PANGO_COVERAGE_EXACT ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/ * pango_context_load_font (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pango_coverage_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pango_coverage_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pango_font_get_coverage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_language_from_string (char const* const) ; 

__attribute__((used)) static int
is_cjk_font(PangoFontDescription *font_desc)
{
    static const char * const cjk_langs[] =
	{"zh_CN", "zh_TW", "zh_HK", "ja", "ko"};

    PangoFont	*font;
    unsigned	i;
    int		is_cjk = FALSE;

    font = pango_context_load_font(gui.text_context, font_desc);

    if (font == NULL)
	return FALSE;

    for (i = 0; !is_cjk && i < G_N_ELEMENTS(cjk_langs); ++i)
    {
	PangoCoverage	*coverage;
	gunichar	uc;

	coverage = pango_font_get_coverage(
		font, pango_language_from_string(cjk_langs[i]));

	if (coverage != NULL)
	{
	    uc = (cjk_langs[i][0] == 'k') ? 0xAC00 : 0x4E00;
	    is_cjk = (pango_coverage_get(coverage, uc) == PANGO_COVERAGE_EXACT);
	    pango_coverage_unref(coverage);
	}
    }

    g_object_unref(font);

    return is_cjk;
}