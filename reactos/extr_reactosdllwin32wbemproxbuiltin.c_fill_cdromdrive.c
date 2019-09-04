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
struct record_cdromdrive {void* pnpdevice_id; int /*<<< orphan*/  name; int /*<<< orphan*/  mediatype; int /*<<< orphan*/  drive; void* device_id; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  char WCHAR ;
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DRIVE_CDROM ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 scalar_t__ GetDriveTypeW (char*) ; 
 int GetLogicalDrives () ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  cdromdrive_mediatypeW ; 
 int /*<<< orphan*/  cdromdrive_nameW ; 
 void* cdromdrive_pnpdeviceidW ; 
 int /*<<< orphan*/  free_row_values (struct table*,int) ; 
 int /*<<< orphan*/  heap_strdupW (char*) ; 
 int /*<<< orphan*/  match_row (struct table*,int,struct expr const*,int*) ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char) ; 

__attribute__((used)) static enum fill_status fill_cdromdrive( struct table *table, const struct expr *cond )
{
    static const WCHAR fmtW[] = {'%','c',':',0};
    WCHAR drive[3], root[] = {'A',':','\\',0};
    struct record_cdromdrive *rec;
    UINT i, row = 0, offset = 0;
    DWORD drives = GetLogicalDrives();
    enum fill_status status = FILL_STATUS_UNFILTERED;

    if (!resize_table( table, 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

    for (i = 0; i < 26; i++)
    {
        if (drives & (1 << i))
        {
            root[0] = 'A' + i;
            if (GetDriveTypeW( root ) != DRIVE_CDROM)
                continue;

            if (!resize_table( table, row + 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

            rec = (struct record_cdromdrive *)(table->data + offset);
            rec->device_id    = cdromdrive_pnpdeviceidW;
            sprintfW( drive, fmtW, 'A' + i );
            rec->drive        = heap_strdupW( drive );
            rec->mediatype    = cdromdrive_mediatypeW;
            rec->name         = cdromdrive_nameW;
            rec->pnpdevice_id = cdromdrive_pnpdeviceidW;
            if (!match_row( table, row, cond, &status ))
            {
                free_row_values( table, row );
                continue;
            }
            offset += sizeof(*rec);
            row++;
        }
    }
    TRACE("created %u rows\n", row);
    table->num_rows = row;
    return status;
}