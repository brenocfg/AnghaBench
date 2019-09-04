#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  custdata_list; } ;
typedef  TYPE_1__ TLBParDesc ;

/* Variables and functions */
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TLBParDesc *TLBParDesc_Constructor(UINT n)
{
    TLBParDesc *ret;

    ret = heap_alloc_zero(sizeof(TLBParDesc) * n);
    if(!ret)
        return NULL;

    while(n){
        list_init(&ret[n-1].custdata_list);
        --n;
    }

    return ret;
}