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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ntoh64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t get64bit(const uint8_t **ptr)
{
    uint64_t val_h = ntoh64 (*((uint64_t *)(*ptr)));
    (*ptr)+=8;
    return val_h;
}