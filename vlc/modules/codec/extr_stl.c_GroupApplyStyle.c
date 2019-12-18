#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {TYPE_3__* p_style; } ;
typedef  TYPE_1__ stl_sg_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_style_flags; } ;

/* Variables and functions */
 TYPE_3__* CreateGroupStyle () ; 
#define  STL_TF_BOXING_OFF 133 
#define  STL_TF_BOXING_ON 132 
#define  STL_TF_ITALICS_OFF 131 
#define  STL_TF_ITALICS_ON 130 
#define  STL_TF_UNDERLINE_OFF 129 
#define  STL_TF_UNDERLINE_ON 128 
 int /*<<< orphan*/  STYLE_ITALIC ; 
 int /*<<< orphan*/  STYLE_UNDERLINE ; 

__attribute__((used)) static void GroupApplyStyle(stl_sg_t *p_group, uint8_t code)
{
    if(p_group->p_style == NULL &&
      !(p_group->p_style = CreateGroupStyle()))
        return;

    switch(code)
    {
        case STL_TF_ITALICS_ON:
            p_group->p_style->i_style_flags |= STYLE_ITALIC;
            break;
        case STL_TF_ITALICS_OFF:
            p_group->p_style->i_style_flags &= ~STYLE_ITALIC;
            break;
        case STL_TF_UNDERLINE_ON:
            p_group->p_style->i_style_flags |= STYLE_UNDERLINE;
            break;
        case STL_TF_UNDERLINE_OFF:
            p_group->p_style->i_style_flags &= ~STYLE_UNDERLINE;
            break;
        case STL_TF_BOXING_ON:
        case STL_TF_BOXING_OFF:
        default:
            break;
    }
}