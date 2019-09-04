#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct temp_file {int handle; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int (* close ) (int,int*,int /*<<< orphan*/ ) ;int (* delete ) (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pv; } ;
typedef  TYPE_1__ FCI_Int ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCIERR_TEMP_FILE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  set_error (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int,int*,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL close_temp_file( FCI_Int *fci, struct temp_file *file )
{
    int err;

    if (file->handle == -1) return TRUE;
    if (fci->close( file->handle, &err, fci->pv ) == -1)
    {
        set_error( fci, FCIERR_TEMP_FILE, err );
        return FALSE;
    }
    file->handle = -1;
    if (fci->delete( file->name, &err, fci->pv ) == -1)
    {
        set_error( fci, FCIERR_TEMP_FILE, err );
        return FALSE;
    }
    return TRUE;
}