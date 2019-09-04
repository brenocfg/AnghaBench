#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_5__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  num_cols; TYPE_1__ view; } ;
typedef  int /*<<< orphan*/  MSIVIEW ;
typedef  TYPE_2__ MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  MSIDATABASE ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  NUM_STREAMS_COLS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ load_streams (int /*<<< orphan*/ *) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  streams_ops ; 

UINT STREAMS_CreateView(MSIDATABASE *db, MSIVIEW **view)
{
    MSISTREAMSVIEW *sv;
    UINT r;

    TRACE("(%p, %p)\n", db, view);

    r = load_streams( db );
    if (r != ERROR_SUCCESS)
        return r;

    if (!(sv = msi_alloc_zero( sizeof(MSISTREAMSVIEW) )))
        return ERROR_OUTOFMEMORY;

    sv->view.ops = &streams_ops;
    sv->num_cols = NUM_STREAMS_COLS;
    sv->db = db;

    *view = (MSIVIEW *)sv;

    return ERROR_SUCCESS;
}