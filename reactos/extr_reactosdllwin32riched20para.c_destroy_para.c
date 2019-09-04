#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ nWidth; int /*<<< orphan*/  para_num; int /*<<< orphan*/  text; scalar_t__ nRows; } ;
struct TYPE_12__ {TYPE_1__ para; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_2__ member; } ;
struct TYPE_13__ {scalar_t__ nTotalWidth; int /*<<< orphan*/  total_rows; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  ME_DestroyDisplayItem (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_DestroyString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ diParagraph ; 
 scalar_t__ get_total_width (TYPE_3__*) ; 
 int /*<<< orphan*/  para_num_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_marked_para (TYPE_3__*,TYPE_4__*) ; 

void destroy_para(ME_TextEditor *editor, ME_DisplayItem *item)
{
    assert(item->type == diParagraph);

    if (item->member.para.nWidth == editor->nTotalWidth)
    {
        item->member.para.nWidth = 0;
        editor->nTotalWidth = get_total_width(editor);
    }
    editor->total_rows -= item->member.para.nRows;
    ME_DestroyString(item->member.para.text);
    para_num_clear( &item->member.para.para_num );
    remove_marked_para(editor, item);
    ME_DestroyDisplayItem(item);
}