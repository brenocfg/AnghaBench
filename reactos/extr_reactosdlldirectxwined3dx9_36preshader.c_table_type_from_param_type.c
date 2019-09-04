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
typedef  enum pres_value_type { ____Placeholder_pres_value_type } pres_value_type ;
typedef  int D3DXPARAMETER_TYPE ;

/* Variables and functions */
#define  D3DXPT_BOOL 130 
#define  D3DXPT_FLOAT 129 
#define  D3DXPT_INT 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int PRES_VT_BOOL ; 
 int PRES_VT_COUNT ; 
 int PRES_VT_FLOAT ; 
 int PRES_VT_INT ; 

__attribute__((used)) static enum pres_value_type table_type_from_param_type(D3DXPARAMETER_TYPE type)
{
    switch (type)
    {
        case D3DXPT_FLOAT:
            return PRES_VT_FLOAT;
        case D3DXPT_INT:
            return PRES_VT_INT;
        case D3DXPT_BOOL:
            return PRES_VT_BOOL;
        default:
            FIXME("Unsupported type %u.\n", type);
            return PRES_VT_COUNT;
    }
}