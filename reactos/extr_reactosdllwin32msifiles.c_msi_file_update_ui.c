#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  FileSize; TYPE_1__* Component; int /*<<< orphan*/  FileName; } ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  Directory; } ;
typedef  TYPE_2__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_3__ MSIFILE ;

/* Variables and functions */
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONDATA ; 
 TYPE_2__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_ui_progress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msi_file_update_ui( MSIPACKAGE *package, MSIFILE *f, const WCHAR *action )
{
    MSIRECORD *uirow;

    uirow = MSI_CreateRecord( 9 );
    MSI_RecordSetStringW( uirow, 1, f->FileName );
    MSI_RecordSetStringW( uirow, 9, f->Component->Directory );
    MSI_RecordSetInteger( uirow, 6, f->FileSize );
    MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONDATA, uirow);
    msiobj_release( &uirow->hdr );
    msi_ui_progress( package, 2, f->FileSize, 0, 0 );
}