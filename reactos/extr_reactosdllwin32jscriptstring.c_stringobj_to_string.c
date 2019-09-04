#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_3__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ StringInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  jsstr_addref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ ) ; 
 TYPE_1__* string_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT stringobj_to_string(vdisp_t *jsthis, jsval_t *r)
{
    StringInstance *string;

    if(!(string = string_this(jsthis))) {
        WARN("this is not a string object\n");
        return E_FAIL;
    }

    if(r)
        *r = jsval_string(jsstr_addref(string->str));
    return S_OK;
}