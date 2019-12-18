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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 scalar_t__ VLC_KEYSTORE_NAME ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ghashtable_insert_vlc_id(GHashTable *g_hash)
{
    g_hash_table_insert(g_hash, (gpointer) ".created_by",
                        (gpointer) VLC_KEYSTORE_NAME);
}