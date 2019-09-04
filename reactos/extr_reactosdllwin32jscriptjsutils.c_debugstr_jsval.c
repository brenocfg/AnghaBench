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

/* Variables and functions */
#define  JSV_BOOL 134 
#define  JSV_NULL 133 
#define  JSV_NUMBER 132 
#define  JSV_OBJECT 131 
#define  JSV_STRING 130 
#define  JSV_UNDEFINED 129 
#define  JSV_VARIANT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_jsstr (int /*<<< orphan*/ ) ; 
 char const* debugstr_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bool (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_number (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_variant (int /*<<< orphan*/  const) ; 
 int jsval_type (int /*<<< orphan*/  const) ; 
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ) ; 

const char *debugstr_jsval(const jsval_t v)
{
    switch(jsval_type(v)) {
    case JSV_UNDEFINED:
        return "undefined";
    case JSV_NULL:
        return "null";
    case JSV_OBJECT:
        return wine_dbg_sprintf("obj(%p)", get_object(v));
    case JSV_STRING:
        return wine_dbg_sprintf("str(%s)", debugstr_jsstr(get_string(v)));
    case JSV_NUMBER:
        return wine_dbg_sprintf("%lf", get_number(v));
    case JSV_BOOL:
        return get_bool(v) ? "true" : "false";
    case JSV_VARIANT:
        return debugstr_variant(get_variant(v));
    }

    assert(0);
    return NULL;
}