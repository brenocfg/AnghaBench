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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  INSTALLUI_HANDLER_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_INSTALL_USEREXIT ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INSTALLLOGMODE_SHOWDIALOG ; 
 int /*<<< orphan*/  INSTALLUILEVEL_FULL ; 
 int /*<<< orphan*/  MSITEST_INSTALLLOGMODE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseImportA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MsiDoActionA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MsiSetExternalUIA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiSetExternalUIRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiSetInternalUI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_control_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_controlevent_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_custom_action_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_dialog_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  closehandle_sequence ; 
 int /*<<< orphan*/  controlevent_spawn2_sequence ; 
 int /*<<< orphan*/  controlevent_spawn_sequence ; 
 int /*<<< orphan*/  create_control_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_controlevent_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_custom_action_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_dialog_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_file_data (char*,char*) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  externalui_message_callback ; 
 int /*<<< orphan*/  externalui_message_string_callback ; 
 int /*<<< orphan*/  flush_sequence () ; 
 char* msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpackage_sequence ; 
 scalar_t__ package_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  winetest_interactive ; 

__attribute__((used)) static void test_controlevent(void)
{
    INSTALLUI_HANDLER_RECORD prev;
    MSIHANDLE hdb, hpkg;
    UINT r;

    if (!winetest_interactive)
    {
        skip("interactive ControlEvent tests\n");
        return;
    }

    MsiSetInternalUI(INSTALLUILEVEL_FULL, NULL);

    MsiSetExternalUIA(externalui_message_string_callback, INSTALLLOGMODE_SHOWDIALOG, NULL);
    r = MsiSetExternalUIRecord(externalui_message_callback, MSITEST_INSTALLLOGMODE, NULL, &prev);

    flush_sequence();

    CoInitialize(NULL);

    hdb = create_package_db();
    ok(hdb, "failed to create database\n");

    create_file_data("forcecodepage.idt", "\r\n\r\n1252\t_ForceCodepage\r\n");
    r = MsiDatabaseImportA(hdb, CURR_DIR, "forcecodepage.idt");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    create_dialog_table(hdb);
    add_dialog_entry(hdb, "'spawn', 50, 50, 100, 100, 3, 'button'");
    add_dialog_entry(hdb, "'spawn2', 50, 50, 100, 100, 3, 'button'");
    add_dialog_entry(hdb, "'child1', 50, 50, 80, 40, 3, 'exit'");
    add_dialog_entry(hdb, "'child2', 50, 50, 80, 40, 3, 'exit'");

    create_control_table(hdb);
    add_control_entry(hdb, "'spawn', 'button', 'PushButton', 10, 10, 66, 17, 3, 'Click me'");
    add_control_entry(hdb, "'spawn2', 'button', 'PushButton', 10, 10, 66, 17, 3, 'Click me'");
    add_control_entry(hdb, "'child1', 'exit', 'PushButton', 10, 10, 66, 17, 3, 'Click me'");
    add_control_entry(hdb, "'child2', 'exit', 'PushButton', 10, 10, 66, 17, 3, 'Click me'");

    create_controlevent_table(hdb);
    add_controlevent_entry(hdb, "'child1', 'exit', 'EndDialog', 'Exit', 1, 1");
    add_controlevent_entry(hdb, "'child2', 'exit', 'EndDialog', 'Exit', 1, 1");

    create_custom_action_table(hdb);
    add_custom_action_entry(hdb, "'custom', 51, 'dummy', 'dummy value'");

    /* SpawnDialog and EndDialog should trigger after all other events */
    add_controlevent_entry(hdb, "'spawn', 'button', 'SpawnDialog', 'child1', 1, 1");
    add_controlevent_entry(hdb, "'spawn', 'button', 'DoAction', 'custom', 1, 2");

    /* Multiple dialog events cause only the last one to be triggered */
    add_controlevent_entry(hdb, "'spawn2', 'button', 'SpawnDialog', 'child1', 1, 1");
    add_controlevent_entry(hdb, "'spawn2', 'button', 'SpawnDialog', 'child2', 1, 2");
    add_controlevent_entry(hdb, "'spawn2', 'button', 'DoAction', 'custom', 1, 3");

    r = package_from_db(hdb, &hpkg);
    ok(r == ERROR_SUCCESS, "failed to create package: %u\n", r);
    ok_sequence(openpackage_sequence, "MsiOpenPackage()", FALSE);

    r = MsiDoActionA(hpkg, "spawn");
    ok(r == ERROR_INSTALL_USEREXIT, "expected ERROR_INSTALL_USEREXIT, got %u\n", r);
    ok_sequence(controlevent_spawn_sequence, "control event: spawn", FALSE);

    r = MsiDoActionA(hpkg, "spawn2");
    ok(r == ERROR_INSTALL_USEREXIT, "expected ERROR_INSTALL_USEREXIT, got %u\n", r);
    ok_sequence(controlevent_spawn2_sequence, "control event: spawn2", FALSE);

    MsiCloseHandle(hpkg);
    ok_sequence(closehandle_sequence, "MsiCloseHandle()", FALSE);

    CoUninitialize();
    DeleteFileA(msifile);
    DeleteFileA("forcecodepage.idt");
}