#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;

/* Variables and functions */
 int /*<<< orphan*/  INSTALLMESSAGE_PROGRESS ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  msi_dialog_check_messages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

void msi_ui_progress( MSIPACKAGE *package, int a, int b, int c, int d )
{
    MSIRECORD *row;

    row = MSI_CreateRecord( 4 );
    MSI_RecordSetInteger( row, 1, a );
    MSI_RecordSetInteger( row, 2, b );
    MSI_RecordSetInteger( row, 3, c );
    MSI_RecordSetInteger( row, 4, d );
    MSI_ProcessMessage( package, INSTALLMESSAGE_PROGRESS, row );
    msiobj_release( &row->hdr );

    msi_dialog_check_messages( NULL );
}