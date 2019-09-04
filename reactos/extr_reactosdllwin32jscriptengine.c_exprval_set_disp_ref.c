#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * disp; } ;
struct TYPE_6__ {TYPE_1__ idref; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ exprval_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  EXPRVAL_IDREF ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void exprval_set_disp_ref(exprval_t *ref, IDispatch *obj, DISPID id)
{
    ref->type = EXPRVAL_IDREF;
#ifdef __REACTOS__ /* FIXME: Inspect */
    IDispatch_AddRef(obj);
    ref->u.idref.disp = obj;
#else
    IDispatch_AddRef(ref->u.idref.disp = obj);
#endif
    ref->u.idref.id = id;
}