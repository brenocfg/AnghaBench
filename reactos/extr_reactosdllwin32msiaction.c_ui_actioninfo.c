#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  LastActionResult; int /*<<< orphan*/  db; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  INSTALLMESSAGE_INFO ; 
 int /*<<< orphan*/  MSIERR_INFO_ACTIONENDED ; 
 int /*<<< orphan*/  MSIERR_INFO_ACTIONSTART ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_get_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ui_actioninfo(MSIPACKAGE *package, LPCWSTR action, BOOL start, 
                          INT rc)
{
    MSIRECORD *row;
    WCHAR *template;

    template = msi_get_error_message(package->db, start ? MSIERR_INFO_ACTIONSTART : MSIERR_INFO_ACTIONENDED);

    row = MSI_CreateRecord(2);
    if (!row)
    {
        msi_free(template);
        return;
    }
    MSI_RecordSetStringW(row, 0, template);
    MSI_RecordSetStringW(row, 1, action);
    MSI_RecordSetInteger(row, 2, start ? package->LastActionResult : rc);
    MSI_ProcessMessage(package, INSTALLMESSAGE_INFO, row);
    msiobj_release(&row->hdr);
    msi_free(template);
    if (!start) package->LastActionResult = rc;
}