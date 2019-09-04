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

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ ) ; 
#define  JSV_BOOL 134 
#define  JSV_NULL 133 
#define  JSV_NUMBER 132 
#define  JSV_OBJECT 131 
#define  JSV_STRING 130 
#define  JSV_UNDEFINED 129 
#define  JSV_VARIANT 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_addref (int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_variant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT jsval_copy(jsval_t v, jsval_t *r)
{
    switch(jsval_type(v)) {
    case JSV_UNDEFINED:
    case JSV_NULL:
    case JSV_NUMBER:
    case JSV_BOOL:
        *r = v;
        return S_OK;
    case JSV_OBJECT:
        if(get_object(v))
            IDispatch_AddRef(get_object(v));
        *r = v;
        return S_OK;
    case JSV_STRING: {
        jsstr_addref(get_string(v));
        *r = v;
        return S_OK;
    }
    case JSV_VARIANT:
        return jsval_variant(r, get_variant(v));
    }

    assert(0);
    return E_FAIL;
}