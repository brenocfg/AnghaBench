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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  f; } ;
struct reader {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
libc_seek( struct reader *p_reader, uint64_t i_offset )
{
    return fseek( p_reader->u.f, (long) i_offset, SEEK_SET );
}