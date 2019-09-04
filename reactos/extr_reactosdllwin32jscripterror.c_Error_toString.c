#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_4__ {int version; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * get_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propget_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc (char const*) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (unsigned int,char**) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,char*) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  messageW ; 
 int /*<<< orphan*/  nameW ; 
 int /*<<< orphan*/  to_string (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Error_toString(script_ctx_t *ctx, vdisp_t *vthis, WORD flags,
        unsigned argc, jsval_t *argv, jsval_t *r)
{
    jsdisp_t *jsthis;
    jsstr_t *name = NULL, *msg = NULL, *ret = NULL;
    jsval_t v;
    HRESULT hres;

    static const WCHAR object_errorW[] = {'[','o','b','j','e','c','t',' ','E','r','r','o','r',']',0};

    TRACE("\n");

    jsthis = get_jsdisp(vthis);
    if(!jsthis || ctx->version < 2) {
        if(r) {
            jsstr_t *str;

            str = jsstr_alloc(object_errorW);
            if(!str)
                return E_OUTOFMEMORY;
            *r = jsval_string(str);
        }
        return S_OK;
    }

    hres = jsdisp_propget_name(jsthis, nameW, &v);
    if(FAILED(hres))
        return hres;

    if(!is_undefined(v)) {
        hres = to_string(ctx, v, &name);
        jsval_release(v);
        if(FAILED(hres))
            return hres;
    }

    hres = jsdisp_propget_name(jsthis, messageW, &v);
    if(SUCCEEDED(hres)) {
        if(!is_undefined(v)) {
            hres = to_string(ctx, v, &msg);
            jsval_release(v);
        }
    }

    if(SUCCEEDED(hres)) {
        unsigned name_len = name ? jsstr_length(name) : 0;
        unsigned msg_len = msg ? jsstr_length(msg) : 0;

        if(name_len && msg_len) {
            WCHAR *ptr;

            ret = jsstr_alloc_buf(name_len + msg_len + 2, &ptr);
            if(ret) {
                jsstr_flush(name, ptr);
                ptr[name_len] = ':';
                ptr[name_len+1] = ' ';
                jsstr_flush(msg, ptr+name_len+2);
            }else {
                hres = E_OUTOFMEMORY;
            }
        }else if(name_len) {
            ret = name;
            name = NULL;
        }else if(msg_len) {
            ret = msg;
            msg = NULL;
        }else {
            ret = jsstr_alloc(object_errorW);
        }
    }

    if(msg)
        jsstr_release(msg);
    if(name)
        jsstr_release(name);
    if(FAILED(hres))
        return hres;
    if(!ret)
        return E_OUTOFMEMORY;

    if(r)
        *r = jsval_string(ret);
    else
        jsstr_release(ret);
    return S_OK;
}