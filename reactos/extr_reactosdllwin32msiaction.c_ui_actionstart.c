#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONSTART ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int MSI_ProcessMessage (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* MSI_QueryGetRecord (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT ui_actionstart(MSIPACKAGE *package, LPCWSTR action, LPCWSTR description, LPCWSTR template)
{
    WCHAR query[] = {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        '`','A','c','t','i','o','n','T','e','x','t','`',' ','W','H','E','R','E',' ',
        '`','A','c','t','i','o','n','`',' ','=',' ','\'','%','s','\'',0};
    MSIRECORD *row, *textrow;
    INT rc;

    textrow = MSI_QueryGetRecord(package->db, query, action);
    if (textrow)
    {
        description = MSI_RecordGetString(textrow, 2);
        template = MSI_RecordGetString(textrow, 3);
    }

    row = MSI_CreateRecord(3);
    if (!row) return -1;
    MSI_RecordSetStringW(row, 1, action);
    MSI_RecordSetStringW(row, 2, description);
    MSI_RecordSetStringW(row, 3, template);
    rc = MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONSTART, row);
    if (textrow) msiobj_release(&textrow->hdr);
    msiobj_release(&row->hdr);
    return rc;
}