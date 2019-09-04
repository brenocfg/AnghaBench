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
typedef  int /*<<< orphan*/  empty ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ LFN_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  DELETED_FLAG ; 
 int /*<<< orphan*/  fs_write (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * lfn_offsets ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_lfn_slots(int start, int end)
{
    int i;
    LFN_ENT empty;

    /* New dir entry is zeroed except first byte, which is set to 0xe5.
     * This is to avoid that some FAT-reading OSes (not Linux! ;) stop reading
     * a directory at the first zero entry...
     */
    memset(&empty, 0, sizeof(empty));
    empty.id = DELETED_FLAG;

    for (i = start; i <= end; ++i) {
	fs_write(lfn_offsets[i], sizeof(LFN_ENT), &empty);
    }
}