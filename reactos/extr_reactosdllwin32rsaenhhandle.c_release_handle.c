#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct handle_table {unsigned int iFirstFree; int /*<<< orphan*/  mutex; TYPE_1__* paEntries; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* destructor ) (TYPE_2__*) ;int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {unsigned int iNextFree; TYPE_2__* pObject; } ;
typedef  TYPE_2__ OBJECTHDR ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 unsigned int HANDLE2INDEX (int /*<<< orphan*/ ) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct handle_table*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_valid_handle (struct handle_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

BOOL release_handle(struct handle_table *lpTable, HCRYPTKEY handle, DWORD dwType)
{
    unsigned int index = HANDLE2INDEX(handle);
    OBJECTHDR *pObject;
    BOOL ret = FALSE;

    TRACE("(lpTable=%p, handle=%ld)\n", lpTable, handle);
    
    EnterCriticalSection(&lpTable->mutex);
    
    if (!is_valid_handle(lpTable, handle, dwType))
        goto exit;

    pObject = lpTable->paEntries[index].pObject;
    if (InterlockedDecrement(&pObject->refcount) == 0)
    {
        TRACE("destroying handle %ld\n", handle);
        if (pObject->destructor)
            pObject->destructor(pObject);
    }

    lpTable->paEntries[index].pObject = NULL;
    lpTable->paEntries[index].iNextFree = lpTable->iFirstFree;
    lpTable->iFirstFree = index;

    ret = TRUE;
exit:
    LeaveCriticalSection(&lpTable->mutex);
    return ret;
}