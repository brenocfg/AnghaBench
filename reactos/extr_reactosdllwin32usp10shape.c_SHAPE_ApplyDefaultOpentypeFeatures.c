#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_6__ {int /*<<< orphan*/  defaultTextRange; } ;
struct TYPE_5__ {size_t eScript; } ;
typedef  int /*<<< orphan*/  TEXTRANGE_PROPERTIES ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  SHAPE_ApplyOpenTypeFeatures (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ShapingData ; 

void SHAPE_ApplyDefaultOpentypeFeatures(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WORD* pwOutGlyphs, INT* pcGlyphs, INT cMaxGlyphs, INT cChars, WORD *pwLogClust)
{
const TEXTRANGE_PROPERTIES *rpRangeProperties;
rpRangeProperties = &ShapingData[psa->eScript].defaultTextRange;

    SHAPE_ApplyOpenTypeFeatures(hdc, psc, psa, pwOutGlyphs, pcGlyphs, cMaxGlyphs, cChars, rpRangeProperties, pwLogClust);
}