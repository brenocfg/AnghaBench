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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_ENUMERABLE ; 
 int PROPF_WRITABLE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  alloc_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  descriptionW ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  messageW ; 
 int /*<<< orphan*/  numberW ; 

__attribute__((used)) static HRESULT create_error(script_ctx_t *ctx, jsdisp_t *constr,
        UINT number, jsstr_t *msg, jsdisp_t **ret)
{
    jsdisp_t *err;
    HRESULT hres;

    hres = alloc_error(ctx, NULL, constr, &err);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(err, numberW, PROPF_WRITABLE | PROPF_CONFIGURABLE,
                                       jsval_number((INT)number));
    if(FAILED(hres)) {
        jsdisp_release(err);
        return hres;
    }

    hres = jsdisp_define_data_property(err, messageW,
                                       PROPF_WRITABLE | PROPF_ENUMERABLE | PROPF_CONFIGURABLE,
                                       jsval_string(msg));
    if(SUCCEEDED(hres))
        hres = jsdisp_define_data_property(err, descriptionW, PROPF_WRITABLE | PROPF_CONFIGURABLE,
                                           jsval_string(msg));
    if(FAILED(hres)) {
        jsdisp_release(err);
        return hres;
    }

    *ret = err;
    return S_OK;
}