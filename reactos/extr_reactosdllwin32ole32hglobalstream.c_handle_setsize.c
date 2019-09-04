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
struct handle_wrapper {scalar_t__ size; int /*<<< orphan*/  lock; scalar_t__ hglobal; } ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 scalar_t__ GlobalReAlloc (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT handle_setsize(struct handle_wrapper *handle, ULONG size)
{
    HRESULT hr = S_OK;

    EnterCriticalSection(&handle->lock);

    if (handle->size != size)
    {
        HGLOBAL hglobal = GlobalReAlloc(handle->hglobal, size, GMEM_MOVEABLE);
        if (hglobal)
        {
            handle->hglobal = hglobal;
            handle->size = size;
        }
        else
            hr = E_OUTOFMEMORY;
    }

    LeaveCriticalSection(&handle->lock);
    return hr;
}