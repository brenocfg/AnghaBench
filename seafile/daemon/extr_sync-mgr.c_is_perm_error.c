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
typedef  int gboolean ;

/* Variables and functions */
 int SYNC_ERROR_ID_ACCESS_DENIED ; 
 int SYNC_ERROR_ID_FOLDER_PERM_DENIED ; 
 int SYNC_ERROR_ID_NO_WRITE_PERMISSION ; 
 int SYNC_ERROR_ID_PERM_NOT_SYNCABLE ; 

__attribute__((used)) static gboolean
is_perm_error (int error)
{
    return (error == SYNC_ERROR_ID_ACCESS_DENIED ||
            error == SYNC_ERROR_ID_NO_WRITE_PERMISSION ||
            error == SYNC_ERROR_ID_PERM_NOT_SYNCABLE ||
            error == SYNC_ERROR_ID_FOLDER_PERM_DENIED);
}