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
struct TYPE_5__ {int /*<<< orphan*/  Feature_Parent; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_1__ MSIFEATURE ;
typedef  int /*<<< orphan*/ * LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_feature_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* msi_get_loaded_feature (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT find_feature_children(MSIRECORD * row, LPVOID param)
{
    MSIPACKAGE *package = param;
    MSIFEATURE *parent, *child;

    child = msi_get_loaded_feature( package, MSI_RecordGetString( row, 1 ) );
    if (!child)
        return ERROR_FUNCTION_FAILED;

    if (!child->Feature_Parent)
        return ERROR_SUCCESS;

    parent = msi_get_loaded_feature( package, child->Feature_Parent );
    if (!parent)
        return ERROR_FUNCTION_FAILED;

    add_feature_child( parent, child );
    return ERROR_SUCCESS;
}