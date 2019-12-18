#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ jobject ;
typedef  enum AWindow_ID { ____Placeholder_AWindow_ID } AWindow_ID ;
struct TYPE_6__ {TYPE_1__* views; } ;
struct TYPE_5__ {scalar_t__ jsurface; } ;
typedef  TYPE_2__ AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/  AWindowHandler_getANativeWindow (TYPE_2__*,int) ; 
 int AWindow_Max ; 
 int /*<<< orphan*/  assert (int) ; 

jobject
AWindowHandler_getSurface(AWindowHandler *p_awh, enum AWindow_ID id)
{
    assert(id < AWindow_Max);

    if (p_awh->views[id].jsurface)
        return p_awh->views[id].jsurface;

    AWindowHandler_getANativeWindow(p_awh, id);
    return p_awh->views[id].jsurface;
}