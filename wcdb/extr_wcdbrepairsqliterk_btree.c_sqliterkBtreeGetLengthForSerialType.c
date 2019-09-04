#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static int sqliterkBtreeGetLengthForSerialType(int serialType)
{
    if (serialType < 0) {
        return 0;
    }
    static int sqliterk_btree_serialtype_fixlengths[12] = {0, 1, 2, 3, 4, 6,
                                                           8, 8, 0, 0, 0, 0};
    if (serialType < 12) {
        return sqliterk_btree_serialtype_fixlengths[serialType];
    }
    return (serialType - 12 - serialType % 2) / 2;
}