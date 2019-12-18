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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ UnitFileChange ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_FILE_SYMLINK ; 
 int /*<<< orphan*/  UNIT_FILE_UNLINK ; 

__attribute__((used)) static inline bool unit_file_changes_have_modification(const UnitFileChange* changes, size_t n_changes) {
        size_t i;
        for (i = 0; i < n_changes; i++)
                if (IN_SET(changes[i].type, UNIT_FILE_SYMLINK, UNIT_FILE_UNLINK))
                        return true;
        return false;
}