#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  ip_port; int /*<<< orphan*/  timestamp; } ;
struct TYPE_11__ {TYPE_3__ assoc6; TYPE_3__ assoc4; int /*<<< orphan*/  public_key; } ;
struct TYPE_8__ {scalar_t__ family; } ;
struct TYPE_9__ {TYPE_1__ ip; } ;
typedef  TYPE_2__ IP_Port ;
typedef  TYPE_3__ IPPTsPng ;
typedef  TYPE_4__ Client_data ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ ipport_equal (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int in_list(const Client_data *list, uint16_t length, const uint8_t *public_key, IP_Port ip_port)
{
    unsigned int i;

    for (i = 0; i < length; ++i) {
        if (id_equal(list[i].public_key, public_key)) {
            const IPPTsPng *ipptp;

            if (ip_port.ip.family == AF_INET) {
                ipptp = &list[i].assoc4;
            } else {
                ipptp = &list[i].assoc6;
            }

            if (!is_timeout(ipptp->timestamp, BAD_NODE_TIMEOUT) && ipport_equal(&ipptp->ip_port, &ip_port))
                return 1;
        }
    }

    return 0;
}