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
struct TYPE_4__ {int (* open ) (int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pv; int /*<<< orphan*/  (* gettemp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ FCI_Int ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CB_MAX_FILENAME ; 
 int ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCIERR_TEMP_FILE ; 
 int /*<<< orphan*/  TRUE ; 
 int _O_BINARY ; 
 int _O_CREAT ; 
 int _O_EXCL ; 
 int _O_RDWR ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int /*<<< orphan*/  set_error (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL create_temp_file( FCI_Int *fci, struct temp_file *file )
{
    int err;

    if (!fci->gettemp( file->name, CB_MAX_FILENAME, fci->pv ))
    {
        set_error( fci, FCIERR_TEMP_FILE, ERROR_FUNCTION_FAILED );
        return FALSE;
    }
    if ((file->handle = fci->open( file->name, _O_RDWR | _O_CREAT | _O_EXCL | _O_BINARY,
                                   _S_IREAD | _S_IWRITE, &err, fci->pv )) == -1)
    {
        set_error( fci, FCIERR_TEMP_FILE, err );
        return FALSE;
    }
    return TRUE;
}