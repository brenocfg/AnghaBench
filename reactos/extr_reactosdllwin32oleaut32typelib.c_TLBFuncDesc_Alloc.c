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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TLBFuncDesc ;

/* Variables and functions */
 int /*<<< orphan*/  TLBFuncDesc_Constructor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 

__attribute__((used)) static TLBFuncDesc *TLBFuncDesc_Alloc(UINT n)
{
    TLBFuncDesc *ret;

    ret = heap_alloc_zero(sizeof(TLBFuncDesc) * n);
    if(!ret)
        return NULL;

    while(n){
        TLBFuncDesc_Constructor(&ret[n-1]);
        --n;
    }

    return ret;
}