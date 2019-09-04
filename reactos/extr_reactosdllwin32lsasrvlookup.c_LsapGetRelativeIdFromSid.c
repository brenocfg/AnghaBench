#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int SubAuthorityCount; int /*<<< orphan*/ * SubAuthority; } ;
typedef  TYPE_1__* PSID ;
typedef  TYPE_1__* PISID ;

/* Variables and functions */

ULONG
LsapGetRelativeIdFromSid(PSID Sid_)
{
    PISID Sid = Sid_;

    if (Sid->SubAuthorityCount != 0)
        return Sid->SubAuthority[Sid->SubAuthorityCount - 1];

    return 0;
}