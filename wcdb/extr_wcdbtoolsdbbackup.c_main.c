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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  mm_recover_ctx ;
typedef  int /*<<< orphan*/  mm_backup_ctx ;

/* Variables and functions */
 scalar_t__ DBBAK_OP_BACKUP ; 
 scalar_t__ DBBAK_OP_RECOVER ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_db_path ; 
 scalar_t__ g_dbkey ; 
 int /*<<< orphan*/  g_dump_path ; 
 int /*<<< orphan*/  g_flags ; 
 scalar_t__ g_key ; 
 int /*<<< orphan*/  g_num_tabdesc ; 
 scalar_t__ g_operation ; 
 int /*<<< orphan*/  g_tabdesc ; 
 int /*<<< orphan*/  g_tabdesc_buffer ; 
 scalar_t__ g_tabdesc_path ; 
 int /*<<< orphan*/  mm_backup_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mm_backup_init (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mm_backup_run (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_recover_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mm_recover_init (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int mm_recover_run (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 int /*<<< orphan*/  parse_tabdesc (scalar_t__) ; 
 int /*<<< orphan*/  print_log ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_key (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int sqlite3_open (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	int ret;
	sqlite3 *db;
	
	parse_options(argc, argv);
	if (g_tabdesc_path) parse_tabdesc(g_tabdesc_path);
	
	int key_len = g_key ? strlen(g_key) : 0;
	
	ret = sqlite3_open(g_db_path, &db);
	if (ret != SQLITE_OK) return -3;
	
	if (g_dbkey)
		sqlite3_key(db, g_dbkey, strlen(g_dbkey));
	
	if (g_operation == DBBAK_OP_BACKUP)
	{
		mm_backup_ctx *ctx = mm_backup_init((const uint8_t *) g_key, key_len, g_dump_path,
				g_flags, print_log);
		if (!ctx) return -2;
		
		ret = mm_backup_run(ctx, db, g_tabdesc, g_num_tabdesc);
		if (ret != 0) return -4;
		
		mm_backup_finish(ctx);
	}
	else if (g_operation == DBBAK_OP_RECOVER)
	{
		mm_recover_ctx *ctx = mm_recover_init(g_dump_path, (const uint8_t *) g_key, key_len, print_log);
		if (!ctx) return -2;
		
		ret = mm_recover_run(ctx, db, 1);
		if (ret != 0) return -4;
		
		mm_recover_finish(ctx);
	}
	else usage(argv[0]);
	
	free(g_tabdesc_buffer);
	free(g_tabdesc);
	
	sqlite3_close(db);
	return 0;
}