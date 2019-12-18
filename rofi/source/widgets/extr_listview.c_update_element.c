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
struct TYPE_4__ {unsigned int selected; TYPE_3__* boxes; int /*<<< orphan*/  udata; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ listview ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  TextBoxFontType ;
struct TYPE_5__ {int /*<<< orphan*/  icon; int /*<<< orphan*/  textbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALT ; 
 int /*<<< orphan*/  HIGHLIGHT ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  listview_set_state (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_element ( listview *lv, unsigned int tb, unsigned int index, gboolean full )
{
    // Select drawing mode
    TextBoxFontType type = ( index & 1 ) == 0 ? NORMAL : ALT;
    type = ( index ) == lv->selected ? HIGHLIGHT : type;

    if ( lv->callback ) {
        lv->callback ( lv->boxes[tb].textbox, lv->boxes[tb].icon, index, lv->udata, &type, full );
        listview_set_state ( lv->boxes[tb], type);
    }
}