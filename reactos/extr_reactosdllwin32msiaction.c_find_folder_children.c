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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Parent; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_1__ MSIFOLDER ;
typedef  int /*<<< orphan*/ * LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_folder_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* msi_get_loaded_folder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT find_folder_children( MSIRECORD *row, LPVOID param )
{
    MSIPACKAGE *package = param;
    MSIFOLDER *parent, *child;

    if (!(child = msi_get_loaded_folder( package, MSI_RecordGetString( row, 1 ) )))
        return ERROR_FUNCTION_FAILED;

    if (!child->Parent) return ERROR_SUCCESS;

    if (!(parent = msi_get_loaded_folder( package, child->Parent )))
        return ERROR_FUNCTION_FAILED;

    return add_folder_child( parent, child );
}