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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  iSockaddrLength; int /*<<< orphan*/  lpSockaddr; } ;
struct TYPE_5__ {TYPE_1__ Address; } ;
typedef  TYPE_1__ SOCKET_ADDRESS ;
typedef  TYPE_2__ IP_ADAPTER_UNICAST_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ GetNameInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NAMEREQD ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *get_dnshostname( IP_ADAPTER_UNICAST_ADDRESS *addr )
{
    const SOCKET_ADDRESS *sa = &addr->Address;
    WCHAR buf[NI_MAXHOST];

    if (!addr) return NULL;
    if (GetNameInfoW( sa->lpSockaddr, sa->iSockaddrLength, buf, ARRAY_SIZE( buf ), NULL,
                      0, NI_NAMEREQD )) return NULL;
    return heap_strdupW( buf );
}