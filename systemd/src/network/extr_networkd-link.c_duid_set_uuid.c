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
typedef  int /*<<< orphan*/  sd_id128_t ;
struct TYPE_4__ {int raw_data_len; scalar_t__ type; int /*<<< orphan*/  raw_data; } ;
typedef  TYPE_1__ DUID ;

/* Variables and functions */
 scalar_t__ DUID_TYPE_UUID ; 
 int EINVAL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int duid_set_uuid(DUID *duid, sd_id128_t uuid) {
        assert(duid);

        if (duid->raw_data_len > 0)
                return 0;

        if (duid->type != DUID_TYPE_UUID)
                return -EINVAL;

        memcpy(&duid->raw_data, &uuid, sizeof(sd_id128_t));
        duid->raw_data_len = sizeof(sd_id128_t);

        return 1;
}