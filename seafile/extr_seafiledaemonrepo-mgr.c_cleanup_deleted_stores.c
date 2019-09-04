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

/* Variables and functions */
 int G_USEC_PER_SEC ; 
 int /*<<< orphan*/  cleanup_deleted_stores_by_type (char*) ; 
 int /*<<< orphan*/  g_usleep (int) ; 

__attribute__((used)) static void *
cleanup_deleted_stores (void *vdata)
{
    while (1) {
        cleanup_deleted_stores_by_type ("commits");
        cleanup_deleted_stores_by_type ("fs");
        cleanup_deleted_stores_by_type ("blocks");
        g_usleep (60 * G_USEC_PER_SEC);
    }
    return NULL;
}