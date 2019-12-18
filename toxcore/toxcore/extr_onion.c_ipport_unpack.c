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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ IP_Port ;

/* Variables and functions */
 unsigned int SIZE_IP ; 
 unsigned int SIZE_PORT ; 
 int ip_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,_Bool) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int ipport_unpack(IP_Port *target, const uint8_t *data, unsigned int data_size, _Bool disable_family_check)
{
    if (data_size < (SIZE_IP + SIZE_PORT))
        return -1;

    if (ip_unpack(&target->ip, data, data_size, disable_family_check) == -1)
        return -1;

    memcpy(&target->port, data + SIZE_IP, SIZE_PORT);
    return 0;
}