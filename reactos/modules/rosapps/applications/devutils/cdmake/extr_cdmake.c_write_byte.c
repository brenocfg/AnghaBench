#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t count; scalar_t__ offset; int /*<<< orphan*/  sector; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t BUFFER_SIZE ; 
 scalar_t__ SECTOR_SIZE ; 
 TYPE_1__ cd ; 
 int /*<<< orphan*/  flush_buffer () ; 

__attribute__((used)) static void write_byte(BYTE x)
{
    if (cd.file != NULL)
    {
        cd.buffer[cd.count] = x;
        if (++cd.count == BUFFER_SIZE)
            flush_buffer();
    }
    if (++cd.offset == SECTOR_SIZE)
    {
        cd.sector++;
        cd.offset = 0;
    }
}