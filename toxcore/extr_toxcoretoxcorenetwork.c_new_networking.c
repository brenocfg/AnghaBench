#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  Networking_Core ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ TOX_PORTRANGE_FROM ; 
 scalar_t__ TOX_PORTRANGE_TO ; 
 int /*<<< orphan*/ * new_networking_ex (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

Networking_Core *new_networking(IP ip, uint16_t port)
{
    return new_networking_ex(ip, port, port + (TOX_PORTRANGE_TO - TOX_PORTRANGE_FROM), 0);
}