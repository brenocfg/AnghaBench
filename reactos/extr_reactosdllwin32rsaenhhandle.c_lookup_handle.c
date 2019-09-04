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
struct handle_table {int /*<<< orphan*/  mutex; TYPE_1__* paEntries; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pObject; } ;
typedef  int /*<<< orphan*/  OBJECTHDR ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t HANDLE2INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct handle_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_valid_handle (struct handle_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL lookup_handle(struct handle_table *lpTable, HCRYPTKEY handle, DWORD dwType, OBJECTHDR **lplpObject)
{
    BOOL ret = FALSE;

    TRACE("(lpTable=%p, handle=%ld, lplpObject=%p)\n", lpTable, handle, lplpObject);
    
    EnterCriticalSection(&lpTable->mutex);
    if (!is_valid_handle(lpTable, handle, dwType)) 
    {
        *lplpObject = NULL;
        goto exit;
    }
    *lplpObject = lpTable->paEntries[HANDLE2INDEX(handle)].pObject;

    ret = TRUE;
exit:
    LeaveCriticalSection(&lpTable->mutex);
    return ret;
}