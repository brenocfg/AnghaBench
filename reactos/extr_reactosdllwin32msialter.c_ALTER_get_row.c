#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {TYPE_3__* table; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_row ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;} ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ MSIALTERVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT ALTER_get_row( struct tagMSIVIEW *view, UINT row, MSIRECORD **rec )
{
    MSIALTERVIEW *av = (MSIALTERVIEW*)view;

    TRACE("%p %d %p\n", av, row, rec );

    return av->table->ops->get_row(av->table, row, rec);
}