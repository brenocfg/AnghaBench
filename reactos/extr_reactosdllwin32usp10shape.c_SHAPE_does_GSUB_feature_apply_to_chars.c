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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ GSUB_E_NOGLYPH ; 
 int /*<<< orphan*/  GetGlyphIndicesW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apply_GSUB_feature_to_glyph (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*,char const*) ; 
 int /*<<< orphan*/ * heap_calloc (int,int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

int SHAPE_does_GSUB_feature_apply_to_chars(HDC hdc, SCRIPT_ANALYSIS *psa, ScriptCache *psc,
        const WCHAR *chars, int write_dir, int count, const char *feature)
{
    WORD *glyphs;
    INT glyph_count = count;
    INT rc;

    glyphs = heap_calloc(count, 2 * sizeof(*glyphs));
    GetGlyphIndicesW(hdc, chars, count, glyphs, 0);
    rc = apply_GSUB_feature_to_glyph(hdc, psa, psc, glyphs, 0, write_dir, &glyph_count, feature);
    if (rc > GSUB_E_NOGLYPH)
        rc = count - glyph_count;
    else
        rc = 0;

    heap_free(glyphs);
    return rc;
}