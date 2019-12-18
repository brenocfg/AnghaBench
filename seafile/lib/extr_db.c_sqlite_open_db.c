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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  g_warning (char*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_open (char const*,int /*<<< orphan*/ **) ; 

int
sqlite_open_db (const char *db_path, sqlite3 **db)
{
    int result;
    const char *errmsg;

    result = sqlite3_open (db_path, db);
    if (result) {
        errmsg = sqlite3_errmsg (*db);
                                
        g_warning ("Couldn't open database:'%s', %s\n", 
                   db_path, errmsg ? errmsg : "no error given");

        sqlite3_close (*db);
        return -1;
    }

    return 0;
}