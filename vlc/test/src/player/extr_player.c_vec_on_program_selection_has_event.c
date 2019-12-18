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
struct TYPE_3__ {size_t size; struct report_program_selection* data; } ;
typedef  TYPE_1__ vec_on_program_selection_changed ;
struct report_program_selection {int unselected_id; int selected_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t
vec_on_program_selection_has_event(vec_on_program_selection_changed *vec,
                                   size_t from_idx,
                                   int unselected_id, int selected_id)
{
    assert(vec->size >= from_idx);
    bool has_unselected_id = false, has_selected_id = false;
    for (size_t i = from_idx; i < vec->size; ++i)
    {
        struct report_program_selection report = vec->data[i];
        if (unselected_id != -1 && report.unselected_id == unselected_id)
        {
            assert(!has_unselected_id);
            has_unselected_id = true;
        }
        if (selected_id != -1 && report.selected_id == selected_id)
        {
            assert(!has_selected_id);
            has_selected_id = true;
        }
    }
    if (unselected_id != -1 && selected_id != -1)
        return has_unselected_id && has_selected_id;
    else if (unselected_id)
    {
        assert(!has_selected_id);
        return has_unselected_id;
    }
    else
    {
        assert(selected_id != -1);
        assert(!has_unselected_id);
        return has_selected_id;
    }
}