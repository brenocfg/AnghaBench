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
struct TYPE_2__ {int /*<<< orphan*/  f; } ;
struct reader {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  fread (void*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
libc_read( struct reader *p_reader, void *p_buf, size_t i_len )
{
    return fread( p_buf, 1, i_len , p_reader->u.f );
}