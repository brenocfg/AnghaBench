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
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 void* GlobalLock (scalar_t__) ; 
 scalar_t__ GlobalReAlloc (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,scalar_t__) ; 

__attribute__((used)) static ULONG handle_write(struct handle_wrapper *handle, ULONG *pos, const void *source, ULONG len)
{
    void *dest;

    if (!len)
        return 0;

    EnterCriticalSection(&handle->lock);

    if (*pos + len > handle->size)
    {
        HGLOBAL hglobal = GlobalReAlloc(handle->hglobal, *pos + len, GMEM_MOVEABLE);
        if (hglobal)
        {
            handle->hglobal = hglobal;
            handle->size = *pos + len;
        }
        else
        {
            len = 0;
            goto done;
        }
    }

    dest = GlobalLock(handle->hglobal);
    if (dest)
    {
        memcpy((char *)dest + *pos, source, len);
        *pos += len;
        GlobalUnlock(handle->hglobal);
    }
    else
    {
        WARN("write to invalid hglobal %p\n", handle->hglobal);
        /* len = 0; */
    }

done:
    LeaveCriticalSection(&handle->lock);
    return len;
}