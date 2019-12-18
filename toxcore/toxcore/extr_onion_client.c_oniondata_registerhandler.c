#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  oniondata_handler_callback ;
struct TYPE_5__ {TYPE_1__* Onion_Data_Handlers; } ;
struct TYPE_4__ {void* object; int /*<<< orphan*/  function; } ;
typedef  TYPE_2__ Onion_Client ;

/* Variables and functions */

void oniondata_registerhandler(Onion_Client *onion_c, uint8_t byte, oniondata_handler_callback cb, void *object)
{
    onion_c->Onion_Data_Handlers[byte].function = cb;
    onion_c->Onion_Data_Handlers[byte].object = object;
}