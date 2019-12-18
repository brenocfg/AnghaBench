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
typedef  int /*<<< orphan*/  uint64_t ;
struct stat {int /*<<< orphan*/  st_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  f; } ;
struct reader {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 int fstat (int,struct stat*) ; 

__attribute__((used)) static uint64_t
libc_getsize( struct reader *p_reader )
{
    struct stat st;
    int i_fd = fileno( p_reader->u.f );

    assert( i_fd >= 0 );
    assert( fstat( i_fd, &st ) != -1 );

    return st.st_size;
}