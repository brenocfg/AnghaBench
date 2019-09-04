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
struct TYPE_3__ {int /*<<< orphan*/  ctx; scalar_t__ AuthInfo; } ;
typedef  TYPE_1__ RpcConnection ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 

BOOL RPCRT4_default_is_authorized(RpcConnection *Connection)
{
    return Connection->AuthInfo && SecIsValidHandle(&Connection->ctx);
}