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
typedef  int /*<<< orphan*/ * RPC_BINDING_HANDLE ;
typedef  int /*<<< orphan*/ * HSTRING_TABLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * LocalBindingHandle ; 
 int /*<<< orphan*/ * LocalStringTable ; 
 scalar_t__ PnpBindRpc (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pSetupStringTableAddString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pSetupStringTableDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pSetupStringTableInitialize () ; 

BOOL
PnpGetLocalHandles(RPC_BINDING_HANDLE *BindingHandle,
                   HSTRING_TABLE *StringTable)
{
    if (LocalBindingHandle != NULL)
    {
        if (BindingHandle != NULL)
            *BindingHandle = LocalBindingHandle;

        if (StringTable != NULL)
            *StringTable = LocalStringTable;

        return TRUE;
    }

    LocalStringTable = pSetupStringTableInitialize();
    if (LocalStringTable == NULL)
        return FALSE;

    if (PnpBindRpc(NULL, &LocalBindingHandle) != RPC_S_OK)
    {
        pSetupStringTableDestroy(LocalStringTable);
        return FALSE;
    }

    pSetupStringTableAddString(LocalStringTable, L"PLT", 1);

    if (BindingHandle != NULL)
        *BindingHandle = LocalBindingHandle;

    if (StringTable != NULL)
        *StringTable = LocalStringTable;

    return TRUE;
}