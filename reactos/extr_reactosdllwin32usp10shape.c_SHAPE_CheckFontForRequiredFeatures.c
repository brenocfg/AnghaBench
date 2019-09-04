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
struct TYPE_6__ {scalar_t__* requiredFeatures; } ;
struct TYPE_5__ {size_t eScript; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  LoadedFeature ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_ALL_TABLES ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* ShapingData ; 
 int /*<<< orphan*/  USP_E_SCRIPT_NOT_IN_FONT ; 
 int /*<<< orphan*/ * load_OT_feature (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  load_ot_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT SHAPE_CheckFontForRequiredFeatures(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa)
{
    LoadedFeature *feature;
    int i;

    if (!ShapingData[psa->eScript].requiredFeatures)
        return S_OK;

    load_ot_tables(hdc, psc);

    /* we need to have at least one of the required features */
    i = 0;
    while (ShapingData[psa->eScript].requiredFeatures[i])
    {
        feature = load_OT_feature(hdc, psa, psc, FEATURE_ALL_TABLES, ShapingData[psa->eScript].requiredFeatures[i]);
        if (feature)
            return S_OK;
        i++;
    }

    return USP_E_SCRIPT_NOT_IN_FONT;
}