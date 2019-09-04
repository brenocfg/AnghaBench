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
typedef  int /*<<< orphan*/  letter_a_with_ring ;
typedef  int /*<<< orphan*/  letter_a_ring ;
typedef  int /*<<< orphan*/  bufferW ;
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_BAD_QUERY_SYNTAX ; 
 int /*<<< orphan*/  ERROR_NO_MORE_ITEMS ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiDatabaseOpenViewW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiRecordGetStringA (int /*<<< orphan*/ ,int,char*,int*) ; 
 int /*<<< orphan*/  MsiRecordGetStringW (int /*<<< orphan*/ ,int,char*,int*) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  run_queryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_collation(void)
{
    static const WCHAR query1[] =
        {'I','N','S','E','R','T',' ','I','N','T','O',' ','`','b','a','r','`',' ',
         '(','`','f','o','o','`',',','`','b','a','z','`',')',' ','V','A','L','U','E','S',' ',
         '(','\'','a',0x30a,'\'',',','\'','C','\'',')',0};
    static const WCHAR query2[] =
        {'I','N','S','E','R','T',' ','I','N','T','O',' ','`','b','a','r','`',' ',
         '(','`','f','o','o','`',',','`','b','a','z','`',')',' ','V','A','L','U','E','S',' ',
         '(','\'',0xe5,'\'',',','\'','D','\'',')',0};
    static const WCHAR query3[] =
        {'C','R','E','A','T','E',' ','T','A','B','L','E',' ','`','b','a','z','`',' ',
         '(',' ','`','a',0x30a,'`',' ','L','O','N','G','C','H','A','R',' ','N','O','T',' ','N','U','L','L',',',
           ' ','`',0xe5,'`',' ','L','O','N','G','C','H','A','R',' ','N','O','T',' ','N','U','L','L',' ',
           'P','R','I','M','A','R','Y',' ','K','E','Y',' ','`','a',0x30a,'`',')',0};
    static const WCHAR query4[] =
        {'C','R','E','A','T','E',' ','T','A','B','L','E',' ','`','a',0x30a,'`',' ',
         '(',' ','`','f','o','o','`',' ','L','O','N','G','C','H','A','R',' ','N','O','T',' ',
         'N','U','L','L',' ','P','R','I','M','A','R','Y',' ','K','E','Y',' ','`','f','o','o','`',')',0};
    static const WCHAR query5[] =
        {'C','R','E','A','T','E',' ','T','A','B','L','E',' ','`',0xe5,'`',' ',
         '(',' ','`','f','o','o','`',' ','L','O','N','G','C','H','A','R',' ','N','O','T',' ',
         'N','U','L','L',' ','P','R','I','M','A','R','Y',' ','K','E','Y',' ','`','f','o','o','`',')',0};
    static const WCHAR query6[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','`','b','a','r','`',' ','W','H','E','R','E',
         ' ','`','f','o','o','`',' ','=','\'',0xe5,'\'',0};
    static const WCHAR letter_C[] = {'C',0};
    static const WCHAR letter_D[] = {'D',0};
    static const WCHAR letter_a_ring[] = {'a',0x30a,0};
    static const WCHAR letter_a_with_ring[] = {0xe5,0};
    const char *query;
    MSIHANDLE hdb = 0, hview = 0, hrec = 0;
    UINT r;
    char buffer[100];
    WCHAR bufferW[100];
    DWORD sz;

    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    query = "CREATE TABLE `bar` ( "
        "`foo` LONGCHAR NOT NULL, "
        "`baz` LONGCHAR NOT NULL "
        "PRIMARY KEY `foo` )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "failed to create table\n");

    r = run_query(hdb, 0, query);
    ok(r == ERROR_BAD_QUERY_SYNTAX, "wrong error %u\n", r);

    r = run_query(hdb, 0, "INSERT INTO `bar` "
            "( `foo`, `baz` ) VALUES ( '\2', 'A' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table %u\n", r);

    r = run_query(hdb, 0, "INSERT INTO `bar` "
            "( `foo`, `baz` ) VALUES ( '\1', 'B' )");
    ok(r == ERROR_SUCCESS, "cannot add value to table %u\n", r);

    r = run_queryW(hdb, 0, query1);
    ok(r == ERROR_SUCCESS, "cannot add value to table %u\n", r);

    r = run_queryW(hdb, 0, query2);
    ok(r == ERROR_SUCCESS, "cannot add value to table %u\n", r);

    r = run_queryW(hdb, 0, query3);
    ok(r == ERROR_SUCCESS, "cannot create table %u\n", r);

    r = run_queryW(hdb, 0, query4);
    ok(r == ERROR_SUCCESS, "cannot create table %u\n", r);

    r = run_queryW(hdb, 0, query5);
    ok(r == ERROR_SUCCESS, "cannot create table %u\n", r);

    query = "SELECT * FROM `bar`";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "\2"), "Expected \\2, got '%s'\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "A"), "Expected A, got '%s'\n", buffer);
    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "\1"), "Expected \\1, got '%s'\n", buffer);
    sz = sizeof(buffer);
    r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buffer, "B"), "Expected B, got '%s'\n", buffer);
    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(bufferW) / sizeof(bufferW[0]);
    r = MsiRecordGetStringW(hrec, 1, bufferW, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!memcmp(bufferW, letter_a_ring, sizeof(letter_a_ring)),
       "Expected %s, got %s\n", wine_dbgstr_w(letter_a_ring), wine_dbgstr_w(bufferW));
    sz = sizeof(bufferW) / sizeof(bufferW[0]);
    r = MsiRecordGetStringW(hrec, 2, bufferW, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(bufferW, letter_C), "Expected C, got %s\n", wine_dbgstr_w(bufferW));
    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(bufferW) / sizeof(bufferW[0]);
    r = MsiRecordGetStringW(hrec, 1, bufferW, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!memcmp(bufferW, letter_a_with_ring, sizeof(letter_a_with_ring)),
       "Expected %s, got %s\n", wine_dbgstr_w(letter_a_with_ring), wine_dbgstr_w(bufferW));
    sz = sizeof(bufferW) / sizeof(bufferW[0]);
    r = MsiRecordGetStringW(hrec, 2, bufferW, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(bufferW, letter_D), "Expected D, got %s\n", wine_dbgstr_w(bufferW));
    MsiCloseHandle(hrec);

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiDatabaseOpenViewW(hdb, query6, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_SUCCESS, "MsiViewFetch failed\n");
    sz = sizeof(bufferW) / sizeof(bufferW[0]);
    r = MsiRecordGetStringW(hrec, 1, bufferW, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!memcmp(bufferW, letter_a_with_ring, sizeof(letter_a_with_ring)),
       "Expected %s, got %s\n", wine_dbgstr_w(letter_a_with_ring), wine_dbgstr_w(bufferW));
    sz = sizeof(bufferW) / sizeof(bufferW[0]);
    r = MsiRecordGetStringW(hrec, 2, bufferW, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpW(bufferW, letter_D), "Expected D, got %s\n", wine_dbgstr_w(bufferW));
    MsiCloseHandle(hrec);

    r = MsiViewFetch(hview, &hrec);
    ok(r == ERROR_NO_MORE_ITEMS, "MsiViewFetch failed\n");

    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    r = MsiCloseHandle(hdb);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    DeleteFileA(msifile);
}