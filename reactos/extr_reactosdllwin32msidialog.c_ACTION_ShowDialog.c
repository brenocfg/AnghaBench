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
typedef  char WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  INSTALLMESSAGE_INFO ; 
 int /*<<< orphan*/  INSTALLMESSAGE_SHOWDIALOG ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int MSI_ProcessMessage (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  TABLE_Exists (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

INT ACTION_ShowDialog( MSIPACKAGE *package, const WCHAR *dialog )
{
    static const WCHAR szDialog[] = {'D','i','a','l','o','g',0};
    MSIRECORD *row;
    INT rc;

    if (!TABLE_Exists(package->db, szDialog)) return 0;

    row = MSI_CreateRecord(0);
    if (!row) return -1;
    MSI_RecordSetStringW(row, 0, dialog);
    rc = MSI_ProcessMessage(package, INSTALLMESSAGE_SHOWDIALOG, row);
    msiobj_release(&row->hdr);

    if (rc == -2) rc = 0;

    if (!rc)
    {
        MSIRECORD *row = MSI_CreateRecord(2);
        if (!row) return -1;
        MSI_RecordSetInteger(row, 1, 2726);
        MSI_RecordSetStringW(row, 2, dialog);
        MSI_ProcessMessage(package, INSTALLMESSAGE_INFO, row);

        msiobj_release(&row->hdr);
    }
    return rc;
}