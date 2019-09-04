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
struct TYPE_3__ {int /*<<< orphan*/  pending_argument; int /*<<< orphan*/  pending_event; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  event_end_dialog ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static UINT pending_event_end_dialog( msi_dialog *dialog, const WCHAR *argument )
{
    dialog->pending_event = event_end_dialog;
    msi_free( dialog->pending_argument );
    dialog->pending_argument = strdupW( argument );
    return ERROR_SUCCESS;
}