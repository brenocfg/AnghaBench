#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t WORD ;
struct TYPE_4__ {size_t numAddresses; int /*<<< orphan*/ * addresses; } ;
struct TYPE_3__ {TYPE_2__* cacheEntry; int /*<<< orphan*/  ret; } ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__ NetBTNameQueryData ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBNameCacheEntry ; 
 int /*<<< orphan*/  NRC_OSRESNOTAV ; 
 int /*<<< orphan*/ * addresses ; 

__attribute__((used)) static BOOL NetBTFindNameAnswerCallback(void *pVoid, WORD answerCount,
 WORD answerIndex, PUCHAR rData, WORD rLen)
{
    NetBTNameQueryData *queryData = pVoid;
    BOOL ret;

    if (queryData)
    {
        if (queryData->cacheEntry == NULL)
        {
            queryData->cacheEntry = HeapAlloc(GetProcessHeap(), 0,
             FIELD_OFFSET(NBNameCacheEntry, addresses[answerCount]));
            if (queryData->cacheEntry)
                queryData->cacheEntry->numAddresses = 0;
            else
                queryData->ret = NRC_OSRESNOTAV;
        }
        if (rLen == 6 && queryData->cacheEntry &&
         queryData->cacheEntry->numAddresses < answerCount)
        {
            queryData->cacheEntry->addresses[queryData->cacheEntry->
             numAddresses++] = *(const DWORD *)(rData + 2);
            ret = queryData->cacheEntry->numAddresses < answerCount;
        }
        else
            ret = FALSE;
    }
    else
        ret = FALSE;
    return ret;
}