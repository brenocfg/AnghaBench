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
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  JSCLASS_ARRAY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* array_from_jsdisp (int /*<<< orphan*/ *) ; 
 scalar_t__ is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lengthW ; 

__attribute__((used)) static HRESULT set_length(jsdisp_t *obj, DWORD length)
{
    if(is_class(obj, JSCLASS_ARRAY)) {
        array_from_jsdisp(obj)->length = length;
        return S_OK;
    }

    return jsdisp_propput_name(obj, lengthW, jsval_number(length));
}