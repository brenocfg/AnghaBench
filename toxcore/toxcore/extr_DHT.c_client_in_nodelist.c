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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ Node_format ;

/* Variables and functions */
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int client_in_nodelist(const Node_format *list, uint16_t length, const uint8_t *public_key)
{
    uint32_t i;

    for (i = 0; i < length; ++i) {
        if (id_equal(list[i].public_key, public_key))
            return 1;
    }

    return 0;
}