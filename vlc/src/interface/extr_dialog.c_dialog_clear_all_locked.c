#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dialog_array; } ;
typedef  TYPE_1__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;

/* Variables and functions */
 int /*<<< orphan*/  dialog_cancel_locked (TYPE_1__*,int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
dialog_clear_all_locked(vlc_dialog_provider *p_provider)
{
    for (size_t i = 0; i < vlc_array_count(&p_provider->dialog_array); ++i)
    {
        vlc_dialog_id *p_id =
            vlc_array_item_at_index(&p_provider->dialog_array, i);
        dialog_cancel_locked(p_provider, p_id);
    }
}