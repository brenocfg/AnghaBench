#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double n; } ;
struct TYPE_5__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ jsval_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSV_NUMBER ; 

__attribute__((used)) static inline jsval_t jsval_number(double n)
{
    jsval_t ret;
#ifdef JSVAL_DOUBLE_LAYOUT_PTR32
    ret.u.n = n;
    /* normalize NaN value */
    if((ret.u.s.tag & 0x7ff00000) == 0x7ff00000) {
        /* isinf */
        if(ret.u.s.tag & 0xfffff) {
            ret.u.s.tag = 0x7ff00000;
            ret.u.s.u.as_uintptr = ~0;
        }else if(ret.u.s.u.as_uintptr) {
            ret.u.s.tag = 0x7ff00000;
        }
    }
#else
    ret.type = JSV_NUMBER;
    ret.u.n = n;
#endif
    return ret;
}