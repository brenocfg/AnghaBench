#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  uint8; } ;
struct TYPE_7__ {int /*<<< orphan*/  uint8; } ;
struct TYPE_8__ {scalar_t__ family; TYPE_1__ ip6; TYPE_2__ ip4; } ;
typedef  TYPE_3__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_IP4 ; 
 int /*<<< orphan*/  SIZE_IP6 ; 
 scalar_t__ TOX_AF_INET ; 
 scalar_t__ TOX_TCP_INET ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_net_family (TYPE_3__*) ; 

__attribute__((used)) static void ip_pack(uint8_t *data, IP source)
{
    to_net_family(&source);

    data[0] = source.family;

    if (source.family == TOX_AF_INET || source.family == TOX_TCP_INET) {
        memset(data + 1, 0, SIZE_IP6);
        memcpy(data + 1, source.ip4.uint8, SIZE_IP4);
    } else {
        memcpy(data + 1, source.ip6.uint8, SIZE_IP6);
    }
}