#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {scalar_t__ nlocks; } ;
typedef  TYPE_1__ MyMtx ;

/* Variables and functions */
 int /*<<< orphan*/  Die (char*) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static
void MyMtxDestroy(cmsContext id, void* mtx)
{
    MyMtx* mtx_ = (MyMtx*) mtx;

    if (mtx_->nlocks != 0)
        Die("Locks != 0 when setting free a mutex");

    _cmsFree(id, mtx);

}