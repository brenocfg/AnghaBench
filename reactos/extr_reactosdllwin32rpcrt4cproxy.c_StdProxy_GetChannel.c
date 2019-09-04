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
struct TYPE_4__ {int /*<<< orphan*/  pChannel; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ StdProxyImpl ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPRPCCHANNELBUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* impl_from_proxy_obj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void StdProxy_GetChannel(LPVOID iface,
                                   LPRPCCHANNELBUFFER *ppChannel)
{
  StdProxyImpl *This = impl_from_proxy_obj( iface );
  TRACE("(%p)->GetChannel(%p) %s\n",This,ppChannel,This->name);

  *ppChannel = This->pChannel;
}