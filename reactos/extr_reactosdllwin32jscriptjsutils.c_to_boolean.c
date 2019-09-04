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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  JSV_BOOL 134 
#define  JSV_NULL 133 
#define  JSV_NUMBER 132 
#define  JSV_OBJECT 131 
#define  JSV_STRING 130 
#define  JSV_UNDEFINED 129 
#define  JSV_VARIANT 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ ) ; 
 int get_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_length (int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 

HRESULT to_boolean(jsval_t val, BOOL *ret)
{
    switch(jsval_type(val)) {
    case JSV_UNDEFINED:
    case JSV_NULL:
        *ret = FALSE;
        return S_OK;
    case JSV_OBJECT:
        *ret = get_object(val) != NULL;
        return S_OK;
    case JSV_STRING:
        *ret = jsstr_length(get_string(val)) != 0;
        return S_OK;
    case JSV_NUMBER:
        *ret = !isnan(get_number(val)) && get_number(val);
        return S_OK;
    case JSV_BOOL:
        *ret = get_bool(val);
        return S_OK;
    case JSV_VARIANT:
        FIXME("unimplemented for variant %s\n", debugstr_variant(get_variant(val)));
        return E_NOTIMPL;
    }

    assert(0);
    return E_FAIL;
}