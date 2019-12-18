#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ rw_type; struct TYPE_5__* store_id; struct TYPE_5__* tmp_file; } ;
typedef  int /*<<< orphan*/  BlockBackend ;
typedef  TYPE_1__ BHandle ;

/* Variables and functions */
 scalar_t__ BLOCK_WRITE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_unlink (TYPE_1__*) ; 

__attribute__((used)) static void
block_backend_fs_block_handle_free (BlockBackend *bend,
                                    BHandle *handle)
{
    if (handle->rw_type == BLOCK_WRITE) {
        /* make sure the tmp file is removed even on failure. */
        g_unlink (handle->tmp_file);
        g_free (handle->tmp_file);
    }
    g_free (handle->store_id);
    g_free (handle);
}