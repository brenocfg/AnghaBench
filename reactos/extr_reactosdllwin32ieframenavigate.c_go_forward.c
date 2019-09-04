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
struct TYPE_5__ {scalar_t__ position; scalar_t__ length; } ;
struct TYPE_6__ {TYPE_1__ travellog; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  navigate_history (TYPE_2__*,scalar_t__) ; 

HRESULT go_forward(DocHost *This)
{
    if(This->travellog.position >= This->travellog.length) {
        WARN("No history available\n");
        return E_FAIL;
    }

    return navigate_history(This, This->travellog.position+1);
}