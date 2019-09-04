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
typedef  int /*<<< orphan*/  str_value ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  char* LPCSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_BAD_QUERY_SYNTAX ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int MsiGetSummaryInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiSummaryInfoGetPropertyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,char*,int*) ; 
 int MsiSummaryInfoGetPropertyCount (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  PID_APPNAME ; 
 int /*<<< orphan*/  PID_AUTHOR ; 
 int /*<<< orphan*/  PID_CODEPAGE ; 
 int /*<<< orphan*/  PID_COMMENTS ; 
 int /*<<< orphan*/  PID_CREATE_DTM ; 
 int /*<<< orphan*/  PID_KEYWORDS ; 
 int /*<<< orphan*/  PID_LASTSAVE_DTM ; 
 int /*<<< orphan*/  PID_PAGECOUNT ; 
 int /*<<< orphan*/  PID_REVNUMBER ; 
 int /*<<< orphan*/  PID_SECURITY ; 
 int /*<<< orphan*/  PID_SUBJECT ; 
 int /*<<< orphan*/  PID_TEMPLATE ; 
 int /*<<< orphan*/  PID_TITLE ; 
 int /*<<< orphan*/  PID_WORDCOUNT ; 
 int VT_FILETIME ; 
 int VT_I2 ; 
 int VT_I4 ; 
 int VT_LPSTR ; 
 int add_table_to_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  suminfo ; 

__attribute__((used)) static void test_suminfo_import(void)
{
    MSIHANDLE hdb, hsi, view = 0;
    LPCSTR query;
    UINT r, count, size, type;
    char str_value[50];
    INT int_value;
    FILETIME ft_value;

    GetCurrentDirectoryA(MAX_PATH, CURR_DIR);

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    r = add_table_to_db(hdb, suminfo);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    /* _SummaryInformation is not imported as a regular table... */

    query = "SELECT * FROM `_SummaryInformation`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "Expected ERROR_BAD_QUERY_SYNTAX, got %u\n", r);
    MsiCloseHandle(view);

    /* ...its data is added to the special summary information stream */

    r = MsiGetSummaryInformationA(hdb, NULL, 0, &hsi);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    r = MsiSummaryInfoGetPropertyCount(hsi, &count);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(count == 14, "Expected 14, got %u\n", count);

    r = MsiSummaryInfoGetPropertyA(hsi, PID_CODEPAGE, &type, &int_value, NULL, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type ==  VT_I2, "Expected VT_I2, got %u\n", type);
    ok(int_value == 1252, "Expected 1252, got %d\n", int_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_TITLE, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(size == 18, "Expected 18, got %u\n", size);
    ok(!strcmp(str_value, "Installer Database"),
       "Expected \"Installer Database\", got %s\n", str_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_SUBJECT, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(!strcmp(str_value, "Installer description"),
       "Expected \"Installer description\", got %s\n", str_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_AUTHOR, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(!strcmp(str_value, "WineHQ"),
       "Expected \"WineHQ\", got %s\n", str_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_KEYWORDS, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(!strcmp(str_value, "Installer"),
       "Expected \"Installer\", got %s\n", str_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_COMMENTS, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(!strcmp(str_value, "Installer comments"),
       "Expected \"Installer comments\", got %s\n", str_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_TEMPLATE, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(!strcmp(str_value, "Intel;1033,2057"),
       "Expected \"Intel;1033,2057\", got %s\n", str_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_REVNUMBER, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(!strcmp(str_value, "{12345678-1234-1234-1234-123456789012}"),
       "Expected \"{12345678-1234-1234-1234-123456789012}\", got %s\n", str_value);

    r = MsiSummaryInfoGetPropertyA(hsi, PID_CREATE_DTM, &type, NULL, &ft_value, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_FILETIME, "Expected VT_FILETIME, got %u\n", type);

    r = MsiSummaryInfoGetPropertyA(hsi, PID_LASTSAVE_DTM, &type, NULL, &ft_value, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_FILETIME, "Expected VT_FILETIME, got %u\n", type);

    r = MsiSummaryInfoGetPropertyA(hsi, PID_PAGECOUNT, &type, &int_value, NULL, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type ==  VT_I4, "Expected VT_I4, got %u\n", type);
    ok(int_value == 200, "Expected 200, got %d\n", int_value);

    r = MsiSummaryInfoGetPropertyA(hsi, PID_WORDCOUNT, &type, &int_value, NULL, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type ==  VT_I4, "Expected VT_I4, got %u\n", type);
    ok(int_value == 2, "Expected 2, got %d\n", int_value);

    r = MsiSummaryInfoGetPropertyA(hsi, PID_SECURITY, &type, &int_value, NULL, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type ==  VT_I4, "Expected VT_I4, got %u\n", type);
    ok(int_value == 2, "Expected 2, got %d\n", int_value);

    size = sizeof(str_value);
    r = MsiSummaryInfoGetPropertyA(hsi, PID_APPNAME, &type, NULL, NULL, str_value, &size);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);
    ok(type == VT_LPSTR, "Expected VT_LPSTR, got %u\n", type);
    ok(!strcmp(str_value, "Vim"), "Expected \"Vim\", got %s\n", str_value);

    MsiCloseHandle(hsi);
    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}