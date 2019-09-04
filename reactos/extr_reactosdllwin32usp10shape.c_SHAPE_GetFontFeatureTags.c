#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ scriptTag; } ;
struct TYPE_4__ {size_t eScript; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  OPENTYPE_TAG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FEATURE_ALL_TABLES ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  OpenType_GetFontFeatureTags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  load_ot_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* scriptInformation ; 

HRESULT SHAPE_GetFontFeatureTags( HDC hdc, ScriptCache *psc,
                                  SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
                                  OPENTYPE_TAG tagLangSys, int cMaxTags,
                                  OPENTYPE_TAG *pFeatureTags, int *pcTags)
{
    HRESULT hr;
    BOOL filter = FALSE;

    load_ot_tables(hdc, psc);

    if (psa && scriptInformation[psa->eScript].scriptTag)
    {
        FIXME("Filtering not implemented\n");
        filter = TRUE;
    }

    hr = OpenType_GetFontFeatureTags(psc, tagScript, tagLangSys, filter, 0x00000000, FEATURE_ALL_TABLES, cMaxTags, pFeatureTags, pcTags, NULL);

    if (FAILED(hr))
        *pcTags = 0;
    return hr;
}