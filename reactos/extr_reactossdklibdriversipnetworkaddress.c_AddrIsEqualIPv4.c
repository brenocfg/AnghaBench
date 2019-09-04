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
struct TYPE_4__ {scalar_t__ IPv4Address; } ;
struct TYPE_5__ {scalar_t__ Type; TYPE_1__ Address; } ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  scalar_t__ IPv4_RAW_ADDRESS ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IP_ADDRESS_V4 ; 

BOOLEAN AddrIsEqualIPv4(
    PIP_ADDRESS Address1,
    IPv4_RAW_ADDRESS Address2)
{
    if (Address1->Type == IP_ADDRESS_V4)
        return (Address1->Address.IPv4Address == Address2);

    return FALSE;
}