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
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  char* LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int MsiRecordGetInteger (int /*<<< orphan*/ ,int) ; 
 int MsiRecordGetStringA (int /*<<< orphan*/ ,int,char*,int*) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 int MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MsiViewGetColumnInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_db () ; 
 int do_query (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_columnorder(void)
{
    MSIHANDLE hdb, view, rec;
    char buf[MAX_PATH];
    LPCSTR query;
    DWORD sz;
    UINT r;

    hdb = create_db();
    ok(hdb, "failed to create db\n");

    /* Each column is a slot:
     * ---------------------
     * | B | C | A | E | D |
     * ---------------------
     *
     * When a column is selected as a primary key,
     * the column occupying the nth primary key slot is swapped
     * with the current position of the primary key in question:
     *
     * set primary key `D`
     * ---------------------    ---------------------
     * | B | C | A | E | D | -> | D | C | A | E | B |
     * ---------------------    ---------------------
     *
     * set primary key `E`
     * ---------------------    ---------------------
     * | D | C | A | E | B | -> | D | E | A | C | B |
     * ---------------------    ---------------------
     */

    query = "CREATE TABLE `T` ( `B` SHORT NOT NULL, `C` SHORT NOT NULL, "
            "`A` CHAR(255), `E` INT, `D` CHAR(255) NOT NULL "
            "PRIMARY KEY `D`, `E`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `T`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_TYPES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("s255", buf), "Expected \"s255\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 2, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("I2", buf), "Expected \"I2\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("S255", buf), "Expected \"S255\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 4, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("i2", buf), "Expected \"i2\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 5, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("i2", buf), "Expected \"i2\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("D", buf), "Expected \"D\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 2, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("E", buf), "Expected \"E\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("A", buf), "Expected \"A\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 4, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("C", buf), "Expected \"C\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 5, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("B", buf), "Expected \"B\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);
    MsiViewClose(view);
    MsiCloseHandle(view);

    query = "INSERT INTO `T` ( `B`, `C`, `A`, `E`, `D` ) "
            "VALUES ( 1, 2, 'a', 3, 'bc' )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `T`";
    r = do_query(hdb, query, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("bc", buf), "Expected \"bc\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 3, "Expected 3, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("a", buf), "Expected \"a\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 4);
    ok(r == 2, "Expected 2, got %d\n", r);

    r = MsiRecordGetInteger(rec, 5);
    ok(r == 1, "Expected 1, got %d\n", r);

    MsiCloseHandle(rec);

    query = "SELECT * FROM `_Columns` WHERE `Table` = 'T'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 1, "Expected 1, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("D", buf), "Expected \"D\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 2, "Expected 2, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("E", buf), "Expected \"E\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 3, "Expected 3, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("A", buf), "Expected \"A\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 4, "Expected 4, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("C", buf), "Expected \"C\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 5, "Expected 5, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("B", buf), "Expected \"B\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(view);
    MsiCloseHandle(view);

    query = "CREATE TABLE `Z` ( `B` SHORT NOT NULL, `C` SHORT NOT NULL, "
            "`A` CHAR(255), `E` INT, `D` CHAR(255) NOT NULL "
            "PRIMARY KEY `C`, `A`, `D`)";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `Z`";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_TYPES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("i2", buf), "Expected \"i2\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 2, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("S255", buf), "Expected \"S255\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("s255", buf), "Expected \"s255\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 4, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("I2", buf), "Expected \"I2\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 5, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("i2", buf), "Expected \"i2\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("C", buf), "Expected \"C\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 2, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("A", buf), "Expected \"A\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("D", buf), "Expected \"D\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 4, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("E", buf), "Expected \"E\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 5, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("B", buf), "Expected \"B\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);
    MsiViewClose(view);
    MsiCloseHandle(view);

    query = "INSERT INTO `Z` ( `B`, `C`, `A`, `E`, `D` ) "
            "VALUES ( 1, 2, 'a', 3, 'bc' )";
    r = run_query(hdb, 0, query);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    query = "SELECT * FROM `Z`";
    r = do_query(hdb, query, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiRecordGetInteger(rec, 1);
    ok(r == 2, "Expected 2, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 2, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("a", buf), "Expected \"a\", got \"%s\"\n", buf);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("bc", buf), "Expected \"bc\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 4);
    ok(r == 3, "Expected 3, got %d\n", r);

    r = MsiRecordGetInteger(rec, 5);
    ok(r == 1, "Expected 1, got %d\n", r);

    MsiCloseHandle(rec);

    query = "SELECT * FROM `_Columns` WHERE `Table` = 'T'";
    r = MsiDatabaseOpenViewA(hdb, query, &view);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    r = MsiViewExecute(view, 0);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 1, "Expected 1, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("D", buf), "Expected \"D\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 2, "Expected 2, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("E", buf), "Expected \"E\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 3, "Expected 3, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("A", buf), "Expected \"A\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 4, "Expected 4, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("C", buf), "Expected \"C\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("T", buf), "Expected \"T\", got \"%s\"\n", buf);

    r = MsiRecordGetInteger(rec, 2);
    ok(r == 5, "Expected 5, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "kiwi");
    r = MsiRecordGetStringA(rec, 3, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA("B", buf), "Expected \"B\", got \"%s\"\n", buf);

    MsiCloseHandle(rec);

    r = MsiViewFetch(view, &rec);
    ok(r == ERROR_NO_MORE_ITEMS, "Expected ERROR_NO_MORE_ITEMS, got %d\n", r);

    MsiViewClose(view);
    MsiCloseHandle(view);

    MsiCloseHandle(hdb);
    DeleteFileA(msifile);
}