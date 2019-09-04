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
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PNAME_SERVER_LIST_PRIVATE ;
typedef  int /*<<< orphan*/  LSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CreateNameServerListCallbackTrampoline ; 
 int /*<<< orphan*/  EnumInterfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

LSTATUS
MakeNameServerList(
    PNAME_SERVER_LIST_PRIVATE PrivateData )
{
    return EnumInterfaces(CreateNameServerListCallbackTrampoline, (PVOID)PrivateData);
}