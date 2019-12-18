#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ sqliterk_os ;
typedef  int /*<<< orphan*/  sqliterk_master_info ;
typedef  int /*<<< orphan*/  sqliterk ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {int key_len; unsigned char* kdf_salt; scalar_t__ key; } ;

/* Variables and functions */
 int SQLITERK_OK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_3__ g_cipher_conf ; 
 int /*<<< orphan*/  g_filter ; 
 int /*<<< orphan*/  g_in_path ; 
 scalar_t__ g_load_master ; 
 int /*<<< orphan*/  g_num_filter ; 
 scalar_t__ g_out_key ; 
 int /*<<< orphan*/  g_out_path ; 
 scalar_t__ g_save_master ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 int /*<<< orphan*/  print_log ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_key (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int sqlite3_open (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqliterk_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterk_free_master (int /*<<< orphan*/ *) ; 
 int sqliterk_load_master (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned char*) ; 
 int sqliterk_make_master (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqliterk_open (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **) ; 
 int sqliterk_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliterk_register (TYPE_1__) ; 
 int sqliterk_save_master (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (scalar_t__) ; 

int main(int argc, char *argv[])
{
	int ret;
	sqlite3 *db;
	sqliterk *rk;
	
    sqliterk_os reg = { print_log };
    sqliterk_register(reg);

	parse_options(argc, argv);
	
	if (g_save_master)
	{
		ret = sqlite3_open(g_in_path, &db);
		if (ret != SQLITE_OK) return -3;
		if (g_cipher_conf.key)
			sqlite3_key(db, g_cipher_conf.key, g_cipher_conf.key_len);

		int out_key_len = g_out_key ? strlen(g_out_key) : 0;
		ret = sqliterk_save_master(db, g_save_master, NULL, 0);
		
		sqlite3_close(db);
		return (ret == SQLITERK_OK) ? 0 : -4;
	}
	else
	{
		sqliterk_master_info *master = NULL;
		unsigned char salt[16];
		if (g_load_master)
		{
			ret = sqliterk_load_master(g_load_master, NULL, 0, g_filter, g_num_filter,
				&master, salt);
			g_cipher_conf.kdf_salt = salt;
		}
		else
			ret = sqliterk_make_master(g_filter, g_num_filter, &master);
		if (ret != SQLITERK_OK) return -6;

		ret = sqliterk_open(g_in_path, g_cipher_conf.key ? &g_cipher_conf : NULL, &rk);
		if (ret != SQLITERK_OK) return -3;

		ret = sqlite3_open(g_out_path, &db);
		if (ret != SQLITE_OK) return -3;
		if (g_out_key)
			sqlite3_key(db, g_out_key, strlen(g_out_key));

		ret = sqliterk_output(rk, db, master, 0);

		sqliterk_free_master(master);
		sqlite3_close(db);
		sqliterk_close(rk);
		free(g_filter);

		return (ret == SQLITERK_OK) ? 0 : -4;
	}
}