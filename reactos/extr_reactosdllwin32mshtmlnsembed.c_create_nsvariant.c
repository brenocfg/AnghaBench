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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIWritableVariant ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  IID_nsIWritableVariant ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_VARIANT_CONTRACTID ; 
 int /*<<< orphan*/  nsIComponentManager_CreateInstanceByContractID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  pCompMgr ; 

nsIWritableVariant *create_nsvariant(void)
{
    nsIWritableVariant *ret = NULL;
    nsresult nsres;

    if(!pCompMgr)
        return NULL;

    nsres = nsIComponentManager_CreateInstanceByContractID(pCompMgr,
            NS_VARIANT_CONTRACTID, NULL, &IID_nsIWritableVariant, (void**)&ret);
    if(NS_FAILED(nsres))
        ERR("Could not get nsIVariant\n");

    return ret;
}