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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  MsiDatabaseImportA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_file (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static UINT add_table_to_db(MSIHANDLE hdb, LPCSTR table_data)
{
    UINT r;

    write_file("temp_file", table_data, (lstrlenA(table_data) - 1) * sizeof(char));
    r = MsiDatabaseImportA(hdb, CURR_DIR, "temp_file");
    DeleteFileA("temp_file");

    return r;
}