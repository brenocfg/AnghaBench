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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/ * LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ MSI_RecordStreamToFile (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_create_temp_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_get_binary_record (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HANDLE msi_load_image( MSIDATABASE *db, LPCWSTR name, UINT type,
                              UINT cx, UINT cy, UINT flags )
{
    MSIRECORD *rec;
    HANDLE himage = NULL;
    LPWSTR tmp;
    UINT r;

    TRACE("%p %s %u %u %08x\n", db, debugstr_w(name), cx, cy, flags);

    if (!(tmp = msi_create_temp_file( db ))) return NULL;

    rec = msi_get_binary_record( db, name );
    if( rec )
    {
        r = MSI_RecordStreamToFile( rec, 2, tmp );
        if( r == ERROR_SUCCESS )
        {
            himage = LoadImageW( 0, tmp, type, cx, cy, flags );
        }
        msiobj_release( &rec->hdr );
    }
    DeleteFileW( tmp );

    msi_free( tmp );
    return himage;
}