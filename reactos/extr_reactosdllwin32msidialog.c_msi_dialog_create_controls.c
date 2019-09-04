#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msi_dialog ;
typedef  size_t UINT ;
struct TYPE_2__ {int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  control_type; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 size_t NUM_CONTROL_TYPES ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_dialog_handler ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT msi_dialog_create_controls( MSIRECORD *rec, LPVOID param )
{
    msi_dialog *dialog = param;
    LPCWSTR control_type;
    UINT i;

    /* find and call the function that can create this type of control */
    control_type = MSI_RecordGetString( rec, 3 );
    for( i=0; i<NUM_CONTROL_TYPES; i++ )
        if (!strcmpiW( msi_dialog_handler[i].control_type, control_type ))
            break;
    if( i != NUM_CONTROL_TYPES )
        msi_dialog_handler[i].func( dialog, rec );
    else
        ERR("no handler for element type %s\n", debugstr_w(control_type));

    return ERROR_SUCCESS;
}