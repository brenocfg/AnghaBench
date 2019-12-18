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
struct TYPE_3__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_THREADING ; 
 size_t get_attrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *get_coclass_threading( const type_t *class )
{
    static const char * const models[] =
    {
        NULL,
        "Apartment", /* THREADING_APARTMENT */
        "Neutral",   /* THREADING_NEUTRAL */
        "Single",    /* THREADING_SINGLE */
        "Free",      /* THREADING_FREE */
        "Both",      /* THREADING_BOTH */
    };
    return models[get_attrv( class->attrs, ATTR_THREADING )];
}