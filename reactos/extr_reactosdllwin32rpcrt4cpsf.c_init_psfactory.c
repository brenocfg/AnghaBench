#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__ const** pProxyFileList; scalar_t__ RefCount; int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {void** Vtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/  DispatchTableCount; } ;
struct TYPE_10__ {TYPE_1__ header; int /*<<< orphan*/  Vtbl; } ;
struct TYPE_9__ {size_t TableSize; int TableVersion; scalar_t__* pDelegatedIIDs; TYPE_3__** pStubVtblList; TYPE_4__** pProxyVtblList; } ;
typedef  TYPE_2__ ProxyFileInfo ;
typedef  TYPE_3__* PCInterfaceStubVtblList ;
typedef  TYPE_4__* PCInterfaceProxyVtblList ;
typedef  int /*<<< orphan*/  IUnknownVtbl ;
typedef  int /*<<< orphan*/  IRpcStubBufferVtbl ;
typedef  size_t DWORD ;
typedef  TYPE_5__ CStdPSFactoryBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  CStdPSFactory_Vtbl ; 
 int /*<<< orphan*/  CStdStubBuffer_Delegating_Vtbl ; 
 int /*<<< orphan*/  CStdStubBuffer_Vtbl ; 
 int /*<<< orphan*/  fill_delegated_proxy_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_psfactory( CStdPSFactoryBuffer *psfac, const ProxyFileInfo **file_list )
{
    DWORD i, j, k;

    psfac->lpVtbl = &CStdPSFactory_Vtbl;
    psfac->RefCount = 0;
    psfac->pProxyFileList = file_list;
    for (i = 0; file_list[i]; i++)
    {
        const PCInterfaceProxyVtblList *proxies = file_list[i]->pProxyVtblList;
        const PCInterfaceStubVtblList *stubs = file_list[i]->pStubVtblList;

        for (j = 0; j < file_list[i]->TableSize; j++)
        {
            /* FIXME: i think that different vtables should be copied for
             * async interfaces */
            void * const *pSrcRpcStubVtbl = (void * const *)&CStdStubBuffer_Vtbl;
            void **pRpcStubVtbl = (void **)&stubs[j]->Vtbl;

            if (file_list[i]->pDelegatedIIDs && file_list[i]->pDelegatedIIDs[j])
            {
                void **vtbl = proxies[j]->Vtbl;
                if (file_list[i]->TableVersion > 1) vtbl++;
                fill_delegated_proxy_table( (IUnknownVtbl *)vtbl, stubs[j]->header.DispatchTableCount );
                pSrcRpcStubVtbl = (void * const *)&CStdStubBuffer_Delegating_Vtbl;
            }

            for (k = 0; k < sizeof(IRpcStubBufferVtbl)/sizeof(void *); k++)
                if (!pRpcStubVtbl[k]) pRpcStubVtbl[k] = pSrcRpcStubVtbl[k];
        }
    }
}