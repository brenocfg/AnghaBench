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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {char* p_sys; scalar_t__ psz_location; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/ * pf_block; int /*<<< orphan*/  pf_read; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  Seek ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    stream_t *access = (stream_t *)obj;

    access->pf_read = Read;
    access->pf_block = NULL;
    access->pf_seek = Seek;
    access->pf_control = Control;
    access->p_sys = (char *)access->psz_location;

    return VLC_SUCCESS;
}