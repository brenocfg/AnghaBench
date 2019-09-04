#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct patch_offset_list {int /*<<< orphan*/  count; int /*<<< orphan*/  files; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct patch_offset {int /*<<< orphan*/  entry; void* sequence; int /*<<< orphan*/  name; } ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 scalar_t__ MSI_DatabaseOpenViewW (int /*<<< orphan*/ *,char const*,TYPE_2__**) ; 
 void* MSI_RecordGetInteger (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ MSI_ViewExecute (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ MSI_ViewFetch (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,void*) ; 
 struct patch_offset* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_dup_record_field (TYPE_1__*,int) ; 
 scalar_t__ msidbFileAttributesPatchAdded ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void patch_offset_get_files( MSIDATABASE *db, UINT last_sequence, struct patch_offset_list *pos )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','F','i','l','e',' ',
        'W','H','E','R','E',' ','S','e','q','u','e','n','c','e',' ','<','=',' ','?',' ',
        'O','R','D','E','R',' ','B','Y',' ','S','e','q','u','e','n','c','e',0};
    MSIQUERY *view;
    MSIRECORD *rec;
    UINT r;

    r = MSI_DatabaseOpenViewW( db, query, &view );
    if (r != ERROR_SUCCESS)
        return;

    rec = MSI_CreateRecord( 1 );
    MSI_RecordSetInteger( rec, 1, last_sequence );

    r = MSI_ViewExecute( view, rec );
    msiobj_release( &rec->hdr );
    if (r != ERROR_SUCCESS)
        return;

    while (MSI_ViewFetch( view, &rec ) == ERROR_SUCCESS)
    {
        UINT attributes = MSI_RecordGetInteger( rec, 7 );
        if (attributes & msidbFileAttributesPatchAdded)
        {
            struct patch_offset *po = msi_alloc( sizeof(struct patch_offset) );

            po->name     = msi_dup_record_field( rec, 1 );
            po->sequence = MSI_RecordGetInteger( rec, 8 );
            pos->min     = min( pos->min, po->sequence );
            pos->max     = max( pos->max, po->sequence );
            list_add_tail( &pos->files, &po->entry );
            pos->count++;
        }
        msiobj_release( &rec->hdr );
    }
    msiobj_release( &view->hdr );
}