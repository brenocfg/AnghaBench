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
struct vlc_h2_frame {size_t* data; } ;

/* Variables and functions */

__attribute__((used)) static struct vlc_h2_frame *resize(struct vlc_h2_frame *f, size_t size)
{   /* NOTE: increasing size would require realloc() */
    f->data[0] = size >> 16;
    f->data[1] = size >> 8;
    f->data[2] = size;
    return f;
}