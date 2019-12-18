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
typedef  int /*<<< orphan*/  vlc_inhibit_t ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ inhibit_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 

void vlc_inhibit_Destroy (vlc_inhibit_t *ih)
{
    assert (ih != NULL);

    module_unneed (ih, ((inhibit_t *)ih)->module);
    vlc_object_delete(ih);
}