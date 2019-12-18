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
typedef  void* uint_fast8_t ;
typedef  int uint_fast32_t ;
struct vlc_h2_frame {size_t* data; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SetDWBE (size_t*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 struct vlc_h2_frame* malloc (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct vlc_h2_frame *
vlc_h2_frame_alloc(uint_fast8_t type, uint_fast8_t flags,
                   uint_fast32_t stream_id, size_t length)
{
    assert((stream_id >> 31) == 0);

    if (unlikely(length >= (1u << 24)))
    {
        errno = EINVAL;
        return NULL;
    }

    struct vlc_h2_frame *f = malloc(sizeof (*f) + 9 + length);
    if (unlikely(f == NULL))
        return NULL;

    f->next = NULL;
    f->data[0] = length >> 16;
    f->data[1] = length >> 8;
    f->data[2] = length;
    f->data[3] = type;
    f->data[4] = flags;
    SetDWBE(f->data + 5, stream_id);
    return f;
}