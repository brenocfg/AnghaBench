#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* (* enumContextsInStore ) (int /*<<< orphan*/ ,void const*) ;scalar_t__ (* serialize ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ;} ;
typedef  TYPE_1__ WINE_CONTEXT_INTERFACE ;
typedef  scalar_t__ (* SerializedOutputFunc ) (void*,int /*<<< orphan*/ *,scalar_t__) ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Context_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  context_from_ptr (void const*) ; 
 void* stub1 (int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ stub2 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ stub3 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static BOOL CRYPT_SerializeContextsToStream(SerializedOutputFunc output,
 void *handle, const WINE_CONTEXT_INTERFACE *contextInterface, HCERTSTORE store)
{
    const void *context = NULL;
    BOOL ret;

    do {
        context = contextInterface->enumContextsInStore(store, context);
        if (context)
        {
            DWORD size = 0;
            LPBYTE buf = NULL;

            ret = contextInterface->serialize(context, 0, NULL, &size);
            if (size)
                buf = CryptMemAlloc(size);
            if (buf)
            {
                ret = contextInterface->serialize(context, 0, buf, &size);
                if (ret)
                    ret = output(handle, buf, size);
            }
            CryptMemFree(buf);
        }
        else
            ret = TRUE;
    } while (ret && context != NULL);
    if (context)
        Context_Release(context_from_ptr(context));
    return ret;
}