#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {int enc_version; int /*<<< orphan*/  random_key; } ;
typedef  TYPE_1__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static gboolean
load_enc_info_cb (sqlite3_stmt *stmt, void *data)
{
    CloneTask *task = data;
    int enc_version;
    const char *random_key;

    enc_version = sqlite3_column_int (stmt, 0);
    random_key = (const char *)sqlite3_column_text (stmt, 1);

    task->enc_version = enc_version;
    task->random_key = g_strdup (random_key);

    return FALSE;
}