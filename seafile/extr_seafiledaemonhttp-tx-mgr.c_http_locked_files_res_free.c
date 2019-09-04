#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  locked_files; } ;
typedef  TYPE_1__ HttpLockedFilesRes ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 

void
http_locked_files_res_free (HttpLockedFilesRes *res)
{
    if (!res)
        return;

    g_hash_table_destroy (res->locked_files);
    g_free (res);
}