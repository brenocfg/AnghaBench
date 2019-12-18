#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int i_int; int f_float; } ;
typedef  TYPE_4__ vlc_value_t ;
struct TYPE_10__ {int i_int; float f_float; } ;
struct TYPE_9__ {int i_int; int f_float; } ;
struct TYPE_8__ {int i_int; int f_float; } ;
struct TYPE_12__ {int i_type; TYPE_3__ step; TYPE_2__ max; TYPE_1__ min; } ;
typedef  TYPE_5__ variable_t ;

/* Variables and functions */
#define  VLC_VAR_FLOAT 129 
#define  VLC_VAR_INTEGER 128 
 int VLC_VAR_TYPE ; 
 int /*<<< orphan*/  isgreater (int,int) ; 
 int /*<<< orphan*/  isless (int,int) ; 
 int roundf (int) ; 

__attribute__((used)) static void CheckValue(variable_t *var, vlc_value_t *val)
{
    /* Check that our variable is within the bounds */
    switch (var->i_type & VLC_VAR_TYPE)
    {
        case VLC_VAR_INTEGER:
            if (val->i_int < var->min.i_int)
               val->i_int = var->min.i_int;
            else if (val->i_int > var->max.i_int)
                val->i_int = var->max.i_int;
            if (var->step.i_int != 0 && (val->i_int % var->step.i_int))
            {
                if (val->i_int > 0)
                    val->i_int = (val->i_int + (var->step.i_int / 2))
                                 / var->step.i_int * var->step.i_int;
                else
                    val->i_int = (val->i_int - (var->step.i_int / 2))
                                 / var->step.i_int * var->step.i_int;
            }
            break;

        case VLC_VAR_FLOAT:
            if (isless(val->f_float, var->min.f_float))
                val->f_float = var->min.f_float;
            else if (isgreater(val->f_float, var->max.f_float))
                val->f_float = var->max.f_float;
            if (var->step.f_float != 0.f)
                val->f_float = var->step.f_float
                              * roundf(val->f_float / var->step.f_float);
            break;
    }
}