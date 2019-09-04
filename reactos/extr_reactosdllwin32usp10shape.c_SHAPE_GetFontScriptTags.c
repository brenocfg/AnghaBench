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
struct TYPE_5__ {int scriptTag; } ;
struct TYPE_4__ {size_t eScript; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int OPENTYPE_TAG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenType_GetFontScriptTags (int /*<<< orphan*/ *,int,int,int*,int*) ; 
 int /*<<< orphan*/  load_ot_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* scriptInformation ; 

HRESULT SHAPE_GetFontScriptTags( HDC hdc, ScriptCache *psc,
                                 SCRIPT_ANALYSIS *psa, int cMaxTags,
                                 OPENTYPE_TAG *pScriptTags, int *pcTags)
{
    HRESULT hr;
    OPENTYPE_TAG searching = 0x00000000;

    load_ot_tables(hdc, psc);

    if (psa && scriptInformation[psa->eScript].scriptTag)
        searching = scriptInformation[psa->eScript].scriptTag;

    hr = OpenType_GetFontScriptTags(psc, searching, cMaxTags, pScriptTags, pcTags);
    if (FAILED(hr))
        *pcTags = 0;
    return hr;
}