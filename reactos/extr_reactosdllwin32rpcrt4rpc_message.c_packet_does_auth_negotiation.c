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
struct TYPE_4__ {int ptype; } ;
struct TYPE_5__ {TYPE_1__ common; } ;
typedef  TYPE_2__ RpcPktHdr ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  PKT_ALTER_CONTEXT 132 
#define  PKT_ALTER_CONTEXT_RESP 131 
#define  PKT_AUTH3 130 
#define  PKT_BIND 129 
#define  PKT_BIND_ACK 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL packet_does_auth_negotiation(const RpcPktHdr *Header)
{
    switch (Header->common.ptype)
    {
    case PKT_BIND:
    case PKT_BIND_ACK:
    case PKT_AUTH3:
    case PKT_ALTER_CONTEXT:
    case PKT_ALTER_CONTEXT_RESP:
        return TRUE;
    default:
        return FALSE;
    }
}