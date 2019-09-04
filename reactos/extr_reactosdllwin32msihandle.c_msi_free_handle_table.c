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
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_handle_cs ; 
 int /*<<< orphan*/  MSI_object_cs ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msihandletable ; 
 scalar_t__ msihandletable_size ; 

void msi_free_handle_table(void)
{
    msi_free( msihandletable );
    msihandletable = NULL;
    msihandletable_size = 0;
    DeleteCriticalSection(&MSI_handle_cs);
    DeleteCriticalSection(&MSI_object_cs);
}