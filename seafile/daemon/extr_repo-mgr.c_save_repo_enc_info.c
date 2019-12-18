#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  sql ;
struct TYPE_8__ {int enc_version; char* id; int /*<<< orphan*/  enc_iv; int /*<<< orphan*/  enc_key; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
save_repo_enc_info (SeafRepoManager *manager,
                    SeafRepo *repo)
{
    sqlite3 *db = manager->priv->db;
    char sql[512];
    char key[65], iv[33];

    if (repo->enc_version == 1) {
        rawdata_to_hex (repo->enc_key, key, 16);
        rawdata_to_hex (repo->enc_iv, iv, 16);
    } else if (repo->enc_version >= 2) {
        rawdata_to_hex (repo->enc_key, key, 32);
        rawdata_to_hex (repo->enc_iv, iv, 16);
    }

    snprintf (sql, sizeof(sql), "REPLACE INTO RepoKeys VALUES ('%s', '%s', '%s')",
              repo->id, key, iv);
    if (sqlite_query_exec (db, sql) < 0)
        return -1;

    return 0;
}