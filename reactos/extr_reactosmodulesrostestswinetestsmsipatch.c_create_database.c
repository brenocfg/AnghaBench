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
struct msi_table {int size; int /*<<< orphan*/  filename; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseImportA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_suminfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void create_database( const char *filename, const struct msi_table *tables, UINT num_tables )
{
    MSIHANDLE hdb;
    UINT r, i;
    WCHAR *filenameW;
    int len;

    len = MultiByteToWideChar( CP_ACP, 0, filename, -1, NULL, 0 );
    if (!(filenameW = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) ))) return;
    MultiByteToWideChar( CP_ACP, 0, filename, -1, filenameW, len );

    r = MsiOpenDatabaseW( filenameW, MSIDBOPEN_CREATE, &hdb );
    ok(r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r);

    /* import the tables into the database */
    for (i = 0; i < num_tables; i++)
    {
        const struct msi_table *table = &tables[i];

        write_file( table->filename, table->data, (table->size - 1) * sizeof(char) );

        r = MsiDatabaseImportA( hdb, CURR_DIR, table->filename );
        ok(r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r);

        DeleteFileA( table->filename );
    }

    r = MsiDatabaseCommit( hdb );
    ok(r == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", r);

    MsiCloseHandle( hdb );
    set_suminfo( filenameW );
    HeapFree( GetProcessHeap(), 0, filenameW );
}