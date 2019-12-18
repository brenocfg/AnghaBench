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
typedef  long uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  f; } ;
struct reader {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 long ftell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
libc_tell( struct reader *p_reader )
{
    long i_ret = ftell( p_reader->u.f );
    assert( i_ret >= 0 );
    return i_ret;
}