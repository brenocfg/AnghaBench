#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_2__ patch_header; TYPE_1__ patch; } ;
typedef  TYPE_3__ patch_data ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void validate_patch(patch_data* current)
{
    UINT crc;

    crc = crc32(~0, current->patch.data, current->patch.len);
    ok(crc == 0, "Invalid patch crc 0x%x for %s\n", crc, current->name);

    crc = crc32(~0, current->patch_header.data, current->patch_header.len);
    ok(crc == 0, "Invalid patch_header crc 0x%x for %s\n", crc, current->name);
}