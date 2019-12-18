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
struct TYPE_2__ {int enc_version; int /*<<< orphan*/  enc_iv; int /*<<< orphan*/  enc_key; } ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  hex_to_rawdata (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static gboolean
load_keys_cb (sqlite3_stmt *stmt, void *vrepo)
{
    SeafRepo *repo = vrepo;
    const char *key, *iv;

    key = (const char *)sqlite3_column_text(stmt, 0);
    iv = (const char *)sqlite3_column_text(stmt, 1);

    if (repo->enc_version == 1) {
        hex_to_rawdata (key, repo->enc_key, 16);
        hex_to_rawdata (iv, repo->enc_iv, 16);
    } else if (repo->enc_version >= 2) {
        hex_to_rawdata (key, repo->enc_key, 32);
        hex_to_rawdata (iv, repo->enc_iv, 16);
    }

    return FALSE;
}