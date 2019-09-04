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
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/  StdMediaSample2 ;
typedef  TYPE_1__ IMediaSample2 ;
typedef  int /*<<< orphan*/  IMediaSample ;

/* Variables and functions */
 int /*<<< orphan*/  StdMediaSample2_VTable ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * impl_from_IMediaSample2 (TYPE_1__*) ; 

__attribute__((used)) static inline StdMediaSample2 *unsafe_impl_from_IMediaSample(IMediaSample * iface)
{
    IMediaSample2 *iface2 = (IMediaSample2 *)iface;

    if (!iface)
        return NULL;
    assert(iface2->lpVtbl == &StdMediaSample2_VTable);
    return impl_from_IMediaSample2(iface2);
}