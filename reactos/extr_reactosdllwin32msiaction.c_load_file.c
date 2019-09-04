#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_17__ {int Attributes; int IsCompressed; int /*<<< orphan*/  entry; void* Sequence; struct TYPE_17__* File; int /*<<< orphan*/  state; void* Language; void* Version; void* FileSize; void* ShortName; int /*<<< orphan*/  LongName; void* FileName; int /*<<< orphan*/  Component; } ;
struct TYPE_16__ {int WordCount; int /*<<< orphan*/  files; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIFILE ;
typedef  TYPE_1__* LPVOID ;
typedef  TYPE_2__* LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 void* FALSE ; 
 void* MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void*) ; 
 int TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (TYPE_2__*) ; 
 int /*<<< orphan*/  folder_split_path (void*,char) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_file_disk_id (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  load_file_hash (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_get_loaded_component (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_reduce_to_long_filename (void*) ; 
 int msidbFileAttributesCompressed ; 
 int msidbFileAttributesNoncompressed ; 
 int msidbFileAttributesPatchAdded ; 
 int msidbSumInfoSourceTypeAdminImage ; 
 int msidbSumInfoSourceTypeCompressed ; 
 int /*<<< orphan*/  msifs_invalid ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT load_file(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE* package = param;
    LPCWSTR component;
    MSIFILE *file;

    /* fill in the data */

    file = msi_alloc_zero( sizeof (MSIFILE) );
    if (!file)
        return ERROR_NOT_ENOUGH_MEMORY;
 
    file->File = msi_dup_record_field( row, 1 );

    component = MSI_RecordGetString( row, 2 );
    file->Component = msi_get_loaded_component( package, component );

    if (!file->Component)
    {
        WARN("Component not found: %s\n", debugstr_w(component));
        msi_free(file->File);
        msi_free(file);
        return ERROR_SUCCESS;
    }

    file->FileName = msi_dup_record_field( row, 3 );
    msi_reduce_to_long_filename( file->FileName );

    file->ShortName = msi_dup_record_field( row, 3 );
    file->LongName = strdupW( folder_split_path(file->ShortName, '|'));
    
    file->FileSize = MSI_RecordGetInteger( row, 4 );
    file->Version = msi_dup_record_field( row, 5 );
    file->Language = msi_dup_record_field( row, 6 );
    file->Attributes = MSI_RecordGetInteger( row, 7 );
    file->Sequence = MSI_RecordGetInteger( row, 8 );

    file->state = msifs_invalid;

    /* if the compressed bits are not set in the file attributes,
     * then read the information from the package word count property
     */
    if (package->WordCount & msidbSumInfoSourceTypeAdminImage)
    {
        file->IsCompressed = FALSE;
    }
    else if (file->Attributes &
             (msidbFileAttributesCompressed | msidbFileAttributesPatchAdded))
    {
        file->IsCompressed = TRUE;
    }
    else if (file->Attributes & msidbFileAttributesNoncompressed)
    {
        file->IsCompressed = FALSE;
    }
    else
    {
        file->IsCompressed = package->WordCount & msidbSumInfoSourceTypeCompressed;
    }

    load_file_hash(package, file);
    load_file_disk_id(package, file);

    TRACE("File loaded (file %s sequence %u)\n", debugstr_w(file->File), file->Sequence);

    list_add_tail( &package->files, &file->entry );
 
    return ERROR_SUCCESS;
}