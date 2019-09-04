#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* jsval_t ;
struct TYPE_19__ {TYPE_3__* builtin_info; int /*<<< orphan*/  ctx; TYPE_6__* props; struct TYPE_19__* prototype; } ;
typedef  TYPE_5__ jsdisp_t ;
struct TYPE_16__ {int /*<<< orphan*/  getter; } ;
struct TYPE_18__ {int ref; int /*<<< orphan*/  idx; TYPE_2__ accessor; void* val; TYPE_1__* p; } ;
struct TYPE_20__ {int type; int /*<<< orphan*/  name; TYPE_4__ u; } ;
typedef  TYPE_6__ dispex_prop_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* idx_get ) (TYPE_5__*,int /*<<< orphan*/ ,void**) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * invoke; int /*<<< orphan*/  (* getter ) (int /*<<< orphan*/ ,TYPE_5__*,void**) ;} ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
#define  PROP_ACCESSOR 131 
#define  PROP_BUILTIN 130 
#define  PROP_IDX 129 
#define  PROP_JSVAL 128 
 int PROP_PROTREF ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_builtin_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__**) ; 
 int /*<<< orphan*/  debugstr_jsval (void*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_addref (TYPE_5__*) ; 
 int /*<<< orphan*/  jsdisp_call_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  jsval_copy (void*,void**) ; 
 void* jsval_obj (TYPE_5__*) ; 
 void* jsval_undefined () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_5__*,void**) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  to_disp (TYPE_5__*) ; 

__attribute__((used)) static HRESULT prop_get(jsdisp_t *This, dispex_prop_t *prop,  jsval_t *r)
{
    jsdisp_t *prop_obj = This;
    HRESULT hres;

    while(prop->type == PROP_PROTREF) {
        prop_obj = prop_obj->prototype;
        prop = prop_obj->props + prop->u.ref;
    }

    switch(prop->type) {
    case PROP_BUILTIN:
        if(prop->u.p->getter) {
            hres = prop->u.p->getter(This->ctx, This, r);
        }else {
            jsdisp_t *obj;

            assert(prop->u.p->invoke != NULL);
            hres = create_builtin_function(This->ctx, prop->u.p->invoke, prop->u.p->name, NULL,
                    prop->u.p->flags, NULL, &obj);
            if(FAILED(hres))
                break;

            prop->type = PROP_JSVAL;
            prop->u.val = jsval_obj(obj);

            jsdisp_addref(obj);
            *r = jsval_obj(obj);
        }
        break;
    case PROP_JSVAL:
        hres = jsval_copy(prop->u.val, r);
        break;
    case PROP_ACCESSOR:
        if(prop->u.accessor.getter) {
            hres = jsdisp_call_value(prop->u.accessor.getter, to_disp(This),
                                     DISPATCH_METHOD, 0, NULL, r);
        }else {
            *r = jsval_undefined();
            hres = S_OK;
        }
        break;
    case PROP_IDX:
        hres = prop_obj->builtin_info->idx_get(prop_obj, prop->u.idx, r);
        break;
    default:
        ERR("type %d\n", prop->type);
        return E_FAIL;
    }

    if(FAILED(hres)) {
        TRACE("fail %08x\n", hres);
        return hres;
    }

    TRACE("%s ret %s\n", debugstr_w(prop->name), debugstr_jsval(*r));
    return hres;
}