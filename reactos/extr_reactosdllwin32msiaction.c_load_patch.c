#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  File; } ;
struct TYPE_12__ {int /*<<< orphan*/  entry; void* Sequence; TYPE_4__* File; void* Attributes; void* PatchSize; } ;
struct TYPE_11__ {int /*<<< orphan*/  filepatches; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIFILEPATCH ;
typedef  TYPE_1__* LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 void* MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_patch_disk_id (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 
 TYPE_4__* msi_get_loaded_file (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static UINT load_patch(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE *package = param;
    MSIFILEPATCH *patch;
    const WCHAR *file_key;

    patch = msi_alloc_zero( sizeof (MSIFILEPATCH) );
    if (!patch)
        return ERROR_NOT_ENOUGH_MEMORY;

    file_key = MSI_RecordGetString( row, 1 );
    patch->File = msi_get_loaded_file( package, file_key );
    if (!patch->File)
    {
        ERR("Failed to find target for patch in File table\n");
        msi_free(patch);
        return ERROR_FUNCTION_FAILED;
    }

    patch->Sequence = MSI_RecordGetInteger( row, 2 );
    patch->PatchSize = MSI_RecordGetInteger( row, 3 );
    patch->Attributes = MSI_RecordGetInteger( row, 4 );

    /* FIXME:
     * Header field - for patch validation.
     * _StreamRef   - External key into MsiPatchHeaders (instead of the header field)
     */

    load_patch_disk_id( package, patch );

    TRACE("Patch loaded (file %s sequence %u)\n", debugstr_w(patch->File->File), patch->Sequence);

    list_add_tail( &package->filepatches, &patch->entry );

    return ERROR_SUCCESS;
}