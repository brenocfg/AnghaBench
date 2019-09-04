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
typedef  int /*<<< orphan*/  cd ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ const INT ;

/* Variables and functions */
#define  ANSI_CHARSET 131 
#define  CP_SYMBOL 130 
 int /*<<< orphan*/  FALSE ; 
#define  RUSSIAN_CHARSET 129 
#define  SYMBOL_CHARSET 128 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ get_glyph_indices (scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_font_installed (char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetGlyphIndicesA ; 
 int /*<<< orphan*/  pGetGlyphIndicesW ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_font_charset(void)
{
    static struct charset_data
    {
        INT charset;
        UINT code_page;
        WORD font_idxA[128], font_idxW[128];
    } cd[] =
    {
        { ANSI_CHARSET, 1252 },
        { RUSSIAN_CHARSET, 1251 },
        { SYMBOL_CHARSET, CP_SYMBOL } /* keep it as the last one */
    };
    int i;

    if (!pGetGlyphIndicesA || !pGetGlyphIndicesW)
    {
        win_skip("Skipping the font charset test on a Win9x platform\n");
        return;
    }

    if (!is_font_installed("Arial"))
    {
        skip("Arial is not installed\n");
        return;
    }

    for (i = 0; i < sizeof(cd)/sizeof(cd[0]); i++)
    {
        if (cd[i].charset == SYMBOL_CHARSET)
        {
            if (!is_font_installed("Symbol") && !is_font_installed("Wingdings"))
            {
                skip("Symbol or Wingdings is not installed\n");
                break;
            }
        }
        if (get_glyph_indices(cd[i].charset, cd[i].code_page, cd[i].font_idxA, 128, FALSE) &&
            get_glyph_indices(cd[i].charset, cd[i].code_page, cd[i].font_idxW, 128, TRUE))
            ok(!memcmp(cd[i].font_idxA, cd[i].font_idxW, 128*sizeof(WORD)), "%d: indices don't match\n", i);
    }

    ok(memcmp(cd[0].font_idxW, cd[1].font_idxW, 128*sizeof(WORD)), "0 vs 1: indices shouldn't match\n");
    if (i > 2)
    {
        ok(memcmp(cd[0].font_idxW, cd[2].font_idxW, 128*sizeof(WORD)), "0 vs 2: indices shouldn't match\n");
        ok(memcmp(cd[1].font_idxW, cd[2].font_idxW, 128*sizeof(WORD)), "1 vs 2: indices shouldn't match\n");
    }
    else
        skip("Symbol or Wingdings is not installed\n");
}