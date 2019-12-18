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
struct MemoryStream {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  off64_t ;

/* Variables and functions */

__attribute__((used)) static off64_t memory_tell(void *data)
{
    struct MemoryStream *stm = data;
    return stm->offset;
}