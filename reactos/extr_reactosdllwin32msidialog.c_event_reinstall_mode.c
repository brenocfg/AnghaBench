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
struct TYPE_5__ {TYPE_1__* package; } ;
typedef  TYPE_2__ msi_dialog ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  szReinstallMode ; 

__attribute__((used)) static UINT event_reinstall_mode( msi_dialog *dialog, const WCHAR *argument )
{
    return msi_set_property( dialog->package->db, szReinstallMode, argument, -1 );
}