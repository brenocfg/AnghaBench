#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct table {int data; int num_rows; } ;
struct record_diskdrive {int index; int size; int /*<<< orphan*/  serialnumber; int /*<<< orphan*/  pnpdevice_id; int /*<<< orphan*/  model; int /*<<< orphan*/  mediatype; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  interfacetype; int /*<<< orphan*/  device_id; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  char WCHAR ;
typedef  int UINT64 ;
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int DRIVE_FIXED ; 
 int DRIVE_REMOVABLE ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 int GetDriveTypeW (char*) ; 
 int GetLogicalDrives () ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  diskdrive_interfacetypeW ; 
 int /*<<< orphan*/  diskdrive_manufacturerW ; 
 int /*<<< orphan*/  diskdrive_mediatype_fixedW ; 
 int /*<<< orphan*/  diskdrive_mediatype_removableW ; 
 int /*<<< orphan*/  diskdrive_modelW ; 
 int /*<<< orphan*/  diskdrive_pnpdeviceidW ; 
 int /*<<< orphan*/  diskdrive_serialW ; 
 int /*<<< orphan*/  free_row_values (struct table*,int) ; 
 int /*<<< orphan*/  get_freespace (char*,int*) ; 
 int /*<<< orphan*/  heap_strdupW (char*) ; 
 int /*<<< orphan*/  match_row (struct table*,int,struct expr const*,int*) ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int) ; 

__attribute__((used)) static enum fill_status fill_diskdrive( struct table *table, const struct expr *cond )
{
    static const WCHAR fmtW[] =
        {'\\','\\','\\','\\','.','\\','\\','P','H','Y','S','I','C','A','L','D','R','I','V','E','%','u',0};
    WCHAR device_id[ARRAY_SIZE( fmtW ) + 10], root[] = {'A',':','\\',0};
    struct record_diskdrive *rec;
    UINT i, row = 0, offset = 0, index = 0, type;
    UINT64 size = 1024 * 1024 * 1024;
    DWORD drives = GetLogicalDrives();
    enum fill_status status = FILL_STATUS_UNFILTERED;

    if (!resize_table( table, 2, sizeof(*rec) )) return FILL_STATUS_FAILED;

    for (i = 0; i < 26; i++)
    {
        if (drives & (1 << i))
        {
            root[0] = 'A' + i;
            type = GetDriveTypeW( root );
            if (type != DRIVE_FIXED && type != DRIVE_REMOVABLE)
                continue;

            if (!resize_table( table, row + 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

            rec = (struct record_diskdrive *)(table->data + offset);
            sprintfW( device_id, fmtW, index );
            rec->device_id     = heap_strdupW( device_id );
            rec->index         = index;
            rec->interfacetype = diskdrive_interfacetypeW;
            rec->manufacturer  = diskdrive_manufacturerW;
            if (type == DRIVE_FIXED)
                rec->mediatype = diskdrive_mediatype_fixedW;
            else
                rec->mediatype = diskdrive_mediatype_removableW;
            rec->model         = diskdrive_modelW;
            rec->pnpdevice_id  = diskdrive_pnpdeviceidW;
            rec->serialnumber  = diskdrive_serialW;
            get_freespace( root, &size );
            rec->size          = size;
            if (!match_row( table, row, cond, &status ))
            {
                free_row_values( table, row );
                continue;
            }
            offset += sizeof(*rec);
            index++;
            row++;
        }
    }
    TRACE("created %u rows\n", row);
    table->num_rows = row;
    return status;
}