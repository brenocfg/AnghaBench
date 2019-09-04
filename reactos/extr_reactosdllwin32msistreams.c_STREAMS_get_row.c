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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  msi_view_get_row (int /*<<< orphan*/ ,struct tagMSIVIEW*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT STREAMS_get_row( struct tagMSIVIEW *view, UINT row, MSIRECORD **rec )
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;

    TRACE("%p %d %p\n", sv, row, rec);

    return msi_view_get_row( sv->db, view, row, rec );
}