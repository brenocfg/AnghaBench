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
typedef  int WORD ;
struct TYPE_3__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
#define  edt4 131 
#define  edt5 130 
#define  edt6 129 
#define  edt7 128 

__attribute__((used)) static inline LONG *element_from_margin_id(RECT *rc, WORD id)
{
    switch(id)
    {
    case edt4: return &rc->left;
    case edt5: return &rc->top;
    case edt6: return &rc->right;
    case edt7: return &rc->bottom;
    }
    return NULL;
}