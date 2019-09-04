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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  seaf_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  writen (int /*<<< orphan*/ ,void const*,size_t) ; 

ssize_t seaf_pipe_writen (seaf_pipe_t fd, const void *vptr, size_t n)
{
    return writen (fd, vptr, n);
}