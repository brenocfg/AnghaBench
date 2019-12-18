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
typedef  TYPE_1__* z_streamp ;
struct TYPE_2__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* zfree ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void ZWRAP_freeFunction(void* opaque, void* address)
{
    z_streamp strm = (z_streamp) opaque;
    strm->zfree(strm->opaque, address);
   /* if (address) LOG_WRAPPERC("ZWRAP free %p \n", address); */
}