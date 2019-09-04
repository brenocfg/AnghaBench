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
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int num_cols; } ;
typedef  TYPE_1__ MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ STREAMS_set_row (struct tagMSIVIEW*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ streams_find_row (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static UINT streams_modify_update(struct tagMSIVIEW *view, MSIRECORD *rec)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;
    UINT r, row;

    r = streams_find_row(sv, rec, &row);
    if (r != ERROR_SUCCESS)
        return ERROR_FUNCTION_FAILED;

    return STREAMS_set_row( view, row, rec, (1 << sv->num_cols) - 1 );
}