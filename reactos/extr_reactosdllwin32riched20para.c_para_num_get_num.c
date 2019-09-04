#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int wNumberingStart; } ;
struct TYPE_8__ {TYPE_4__ fmt; TYPE_3__* prev_para; } ;
struct TYPE_7__ {TYPE_2__ para; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ member; } ;
typedef  TYPE_2__ ME_Paragraph ;
typedef  TYPE_3__ ME_DisplayItem ;

/* Variables and functions */
 scalar_t__ diParagraph ; 
 int /*<<< orphan*/  para_num_same_list (TYPE_4__*,TYPE_4__*) ; 

__attribute__((used)) static int para_num_get_num( ME_Paragraph *para )
{
    ME_DisplayItem *prev;
    int num = para->fmt.wNumberingStart;

    for (prev = para->prev_para; prev->type == diParagraph;
         para = &prev->member.para, prev = prev->member.para.prev_para, num++)
    {
        if (!para_num_same_list( &prev->member.para.fmt, &para->fmt )) break;
    }
    return num;
}