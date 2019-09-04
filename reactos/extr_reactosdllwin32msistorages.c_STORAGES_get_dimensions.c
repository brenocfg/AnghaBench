#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  num_rows; } ;
typedef  TYPE_1__ MSISTORAGESVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  NUM_STORAGES_COLS ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT STORAGES_get_dimensions(struct tagMSIVIEW *view, UINT *rows, UINT *cols)
{
    MSISTORAGESVIEW *sv = (MSISTORAGESVIEW *)view;

    TRACE("(%p, %p, %p)\n", view, rows, cols);

    if (cols) *cols = NUM_STORAGES_COLS;
    if (rows) *rows = sv->num_rows;

    return ERROR_SUCCESS;
}