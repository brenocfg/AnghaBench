#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct stat {scalar_t__ st_size; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 scalar_t__ CURRENT_FILE_SIZE ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void UpdateFileSize( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;
    struct stat st;

    if( p_sys->size >= p_sys->offset )
        return;

    /* TODO: not sure if this can happen or what to do in this case */
    if( fstat( p_sys->fd, &st ) )
        return;
    if( (uint64_t)st.st_size <= CURRENT_FILE_SIZE )
        return;

    p_sys->size -= CURRENT_FILE_SIZE;
    CURRENT_FILE_SIZE = st.st_size;
    p_sys->size += CURRENT_FILE_SIZE;
}