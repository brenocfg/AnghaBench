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
struct TYPE_7__ {TYPE_2__* dword_props; TYPE_1__* str_props; } ;
typedef  TYPE_3__ uri_properties ;
struct TYPE_6__ {scalar_t__ expected; } ;
struct TYPE_5__ {scalar_t__ expected; scalar_t__ expected2; int /*<<< orphan*/ * value2; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ S_OK ; 
 size_t Uri_PROPERTY_DWORD_LAST ; 
 size_t Uri_PROPERTY_DWORD_START ; 
 size_t Uri_PROPERTY_STRING_LAST ; 
 size_t Uri_PROPERTY_STRING_START ; 

__attribute__((used)) static DWORD compute_expected_props(uri_properties *test, DWORD *mask)
{
    DWORD ret = 0, i;

    *mask = 0;

    for(i=Uri_PROPERTY_STRING_START; i <= Uri_PROPERTY_STRING_LAST; i++) {
        if(test->str_props[i-Uri_PROPERTY_STRING_START].expected == S_OK)
            ret |= 1<<i;
        if(test->str_props[i-Uri_PROPERTY_STRING_START].value2 == NULL ||
           test->str_props[i-Uri_PROPERTY_STRING_START].expected ==
           test->str_props[i-Uri_PROPERTY_STRING_START].expected2)
            *mask |= 1<<i;
    }

    for(i=Uri_PROPERTY_DWORD_START; i <= Uri_PROPERTY_DWORD_LAST; i++) {
        if(test->dword_props[i-Uri_PROPERTY_DWORD_START].expected == S_OK)
            ret |= 1<<i;
        *mask |= 1<<i;
    }

    return ret;
}