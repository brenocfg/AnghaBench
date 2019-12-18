#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_5__ {int* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t Read( sout_access_out_t *p_access, block_t *p_buffer )
{
    int *fdp = p_access->p_sys, fd = *fdp;
    ssize_t val;

    do
        val = read(fd, p_buffer->p_buffer, p_buffer->i_buffer);
    while (val == -1 && errno == EINTR);
    return val;
}