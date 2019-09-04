#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  (* contextProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {size_t eScript; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 TYPE_3__* ShapingData ; 
 int /*<<< orphan*/  load_ot_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void SHAPE_ContextualShaping(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwcChars, INT cChars, WORD* pwOutGlyphs, INT* pcGlyphs, INT cMaxGlyphs, WORD *pwLogClust)
{
    load_ot_tables(hdc, psc);

    if (ShapingData[psa->eScript].contextProc)
        ShapingData[psa->eScript].contextProc(hdc, psc, psa, pwcChars, cChars, pwOutGlyphs, pcGlyphs, cMaxGlyphs, pwLogClust);
}