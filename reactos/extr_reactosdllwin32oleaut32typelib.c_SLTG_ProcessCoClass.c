#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sltg_ref_lookup_t ;
typedef  scalar_t__ WORD ;
struct TYPE_7__ {int /*<<< orphan*/  pTypeLib; } ;
struct TYPE_6__ {int href_table; } ;
typedef  int /*<<< orphan*/  SLTG_TypeInfoTail ;
typedef  TYPE_1__ SLTG_TypeInfoHeader ;
typedef  int /*<<< orphan*/  SLTG_RefInfo ;
typedef  TYPE_2__ ITypeInfoImpl ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SLTG_DoImpls (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SLTG_DoRefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SLTG_IMPL_MAGIC ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SLTG_ProcessCoClass(char *pBlk, ITypeInfoImpl *pTI,
				char *pNameTable, SLTG_TypeInfoHeader *pTIHeader,
				SLTG_TypeInfoTail *pTITail)
{
    char *pFirstItem;
    sltg_ref_lookup_t *ref_lookup = NULL;

    if(pTIHeader->href_table != 0xffffffff) {
        ref_lookup = SLTG_DoRefs((SLTG_RefInfo*)((char *)pTIHeader + pTIHeader->href_table), pTI->pTypeLib,
		    pNameTable);
    }

    pFirstItem = pBlk;

    if(*(WORD*)pFirstItem == SLTG_IMPL_MAGIC) {
        SLTG_DoImpls(pFirstItem, pTI, FALSE, ref_lookup);
    }
    heap_free(ref_lookup);
}