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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  empty ;
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ DIR_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  DELETED_FLAG ; 
 int /*<<< orphan*/  fs_write (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lfn_remove(off_t from, off_t to)
{
    DIR_ENT empty;

    /* New dir entry is zeroed except first byte, which is set to 0xe5.
     * This is to avoid that some FAT-reading OSes (not Linux! ;) stop reading
     * a directory at the first zero entry...
     */
    memset(&empty, 0, sizeof(empty));
    empty.name[0] = DELETED_FLAG;

    for (; from < to; from += sizeof(empty)) {
	fs_write(from, sizeof(DIR_ENT), &empty);
    }
}