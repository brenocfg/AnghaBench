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
typedef  char WCHAR ;
typedef  char UINT ;
typedef  int DWORD ;

/* Variables and functions */
 char DRIVE_NO_ROOT_DIR ; 
 char DRIVE_RAMDISK ; 
 char DRIVE_UNKNOWN ; 
 char GetDriveTypeW (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetLogicalDrives () ; 
 int /*<<< orphan*/  ok (int,char*,char,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 char wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_GetDriveTypeW(void)
{
    WCHAR drive[] = {'?',':','\\',0};
    WCHAR existing_drive_letter = 0;
    DWORD logical_drives;
    UINT type;

    logical_drives = GetLogicalDrives();
    ok(logical_drives != 0, "GetLogicalDrives error %d\n", GetLastError());

    for (drive[0] = 'A'; drive[0] <= 'Z'; drive[0]++)
    {
        type = GetDriveTypeW(drive);
        ok(type > DRIVE_UNKNOWN && type <= DRIVE_RAMDISK,
           "not a valid drive %c: type %u\n", drive[0], type);

        if (!(logical_drives & 1))
            ok(type == DRIVE_NO_ROOT_DIR,
               "GetDriveTypeW should return DRIVE_NO_ROOT_DIR for inexistent drive %c: but not %u\n",
               drive[0], type);
        else if (type != DRIVE_NO_ROOT_DIR)
            existing_drive_letter = drive[0];

        logical_drives >>= 1;
    }

    if (!existing_drive_letter) {
        skip("No drives found, skipping drive spec format tests.\n");
        return;
    }

    drive[0] = existing_drive_letter;
    drive[2] = 0; /* C: */
    type = GetDriveTypeW(drive);
    ok(type > DRIVE_NO_ROOT_DIR && type <= DRIVE_RAMDISK, "got %u for drive spec '%s'\n",
       type, wine_dbgstr_w(drive));

    drive[1] = '?'; /* C? */
    type = GetDriveTypeW(drive);
    ok(type == DRIVE_NO_ROOT_DIR, "got %u for drive spec '%s'\n", type, wine_dbgstr_w(drive));

    drive[1] = 0; /* C */
    type = GetDriveTypeW(drive);
    ok(type == DRIVE_NO_ROOT_DIR, "got %u for drive spec '%s'\n", type, wine_dbgstr_w(drive));

    drive[0] = '?'; /* the string "?" */
    type = GetDriveTypeW(drive);
    ok(type == DRIVE_NO_ROOT_DIR, "got %u for drive spec '%s'\n", type, wine_dbgstr_w(drive));

    drive[0] = 0; /* the empty string */
    type = GetDriveTypeW(drive);
    ok(type == DRIVE_NO_ROOT_DIR, "got %u for drive spec '%s'\n", type, wine_dbgstr_w(drive));
}