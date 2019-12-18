#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct vlc_stream_memory_private {size_t i_size; int /*<<< orphan*/ * p_buffer; scalar_t__ i_pos; } ;
struct TYPE_5__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  Seek ; 
 int /*<<< orphan*/  stream_MemoryDelete ; 
 int /*<<< orphan*/  stream_MemoryPreserveDelete ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_stream_CustomNew (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 struct vlc_stream_memory_private* vlc_stream_Private (TYPE_1__*) ; 

stream_t *(vlc_stream_MemoryNew)(vlc_object_t *p_this, uint8_t *p_buffer,
                                 size_t i_size, bool preserve)
{
    struct vlc_stream_memory_private *p_sys;
    stream_t *s = vlc_stream_CustomNew(p_this,
                                       preserve ? stream_MemoryPreserveDelete
                                                : stream_MemoryDelete,
                                       sizeof (*p_sys), "stream");
    if (unlikely(s == NULL))
        return NULL;

    p_sys = vlc_stream_Private(s);
    p_sys->i_pos = 0;
    p_sys->i_size = i_size;
    p_sys->p_buffer = p_buffer;

    s->pf_read    = Read;
    s->pf_seek    = Seek;
    s->pf_control = Control;

    return s;
}