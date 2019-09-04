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
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */

__attribute__((used)) static inline int hash_guid(GUID *guid)
{
    int i, hash = 0;

    for (i = 0; i < 8; i ++)
        hash ^= ((const short *)guid)[i];

    return hash & 0x1f;
}