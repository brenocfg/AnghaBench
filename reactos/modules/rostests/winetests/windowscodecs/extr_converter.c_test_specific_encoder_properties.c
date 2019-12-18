#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ var_type; scalar_t__ initial_var_type; scalar_t__ i_init_val; scalar_t__ f_init_val; scalar_t__ name; scalar_t__ skippable; } ;
typedef  TYPE_1__ property_opt_test_data ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_8__ {scalar_t__ vt; scalar_t__ dwType; scalar_t__ cfType; scalar_t__ pstrName; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ PROPBAG2 ;
typedef  scalar_t__ LPOLESTR ;
typedef  int /*<<< orphan*/  IPropertyBag2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IPropertyBag2_Read (int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ PROPBAG2_TYPE_DATA ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
#define  VT_BOOL 130 
 scalar_t__ VT_EMPTY ; 
#define  VT_R4 129 
#define  VT_UI1 128 
 scalar_t__ V_UNION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bVal ; 
 int find_property_index (scalar_t__,TYPE_2__*,int) ; 
 int /*<<< orphan*/  fltVal ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  win_skip (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (scalar_t__) ; 

__attribute__((used)) static void test_specific_encoder_properties(IPropertyBag2 *options, const property_opt_test_data* data, PROPBAG2* all_props, int all_prop_cnt)
{
    HRESULT hr;
    int i = 0;
    VARIANT pvarValue;
    HRESULT phrError = S_OK;

    while (data[i].name)
    {
        int idx = find_property_index(data[i].name, all_props, all_prop_cnt);
        PROPBAG2 pb = {0};
        pb.pstrName = (LPOLESTR)data[i].name;

        hr = IPropertyBag2_Read(options, 1, &pb, NULL, &pvarValue, &phrError);

        if (data[i].skippable && idx == -1)
        {
            win_skip("Property %s is not supported on this machine.\n", wine_dbgstr_w(data[i].name));
            i++;
            continue;
        }

        ok(idx >= 0, "Property %s not in output of GetPropertyInfo\n",
           wine_dbgstr_w(data[i].name));
        if (idx >= 0)
        {
            ok(all_props[idx].vt == data[i].var_type, "Property %s has unexpected vt type, vt=%i\n",
               wine_dbgstr_w(data[i].name), all_props[idx].vt);
            ok(all_props[idx].dwType == PROPBAG2_TYPE_DATA, "Property %s has unexpected dw type, vt=%i\n",
               wine_dbgstr_w(data[i].name), all_props[idx].dwType);
            ok(all_props[idx].cfType == 0, "Property %s has unexpected cf type, vt=%i\n",
               wine_dbgstr_w(data[i].name), all_props[idx].cfType);
        }

        ok(SUCCEEDED(hr), "Reading property %s from bag failed, hr=%x\n",
           wine_dbgstr_w(data[i].name), hr);

        if (SUCCEEDED(hr))
        {
            /* On XP the initial type is always VT_EMPTY */
            ok(V_VT(&pvarValue) == data[i].initial_var_type || V_VT(&pvarValue) == VT_EMPTY,
               "Property %s has unexpected initial type, V_VT=%i\n",
               wine_dbgstr_w(data[i].name), V_VT(&pvarValue));

            if(V_VT(&pvarValue) == data[i].initial_var_type)
            {
                switch (data[i].initial_var_type)
                {
                    case VT_BOOL:
                    case VT_UI1:
                        ok(V_UNION(&pvarValue, bVal) == data[i].i_init_val, "Property %s has an unexpected initial value, pvarValue=%i\n",
                           wine_dbgstr_w(data[i].name), V_UNION(&pvarValue, bVal));
                        break;
                    case VT_R4:
                        ok(V_UNION(&pvarValue, fltVal) == data[i].f_init_val, "Property %s has an unexpected initial value, pvarValue=%f\n",
                           wine_dbgstr_w(data[i].name), V_UNION(&pvarValue, fltVal));
                        break;
                    default:
                        break;
                }
            }

            VariantClear(&pvarValue);
        }

        i++;
    }
}