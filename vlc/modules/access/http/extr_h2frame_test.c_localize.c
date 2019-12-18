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
struct vlc_h2_frame {int* data; } ;

/* Variables and functions */
 int STREAM_ID ; 

__attribute__((used)) static struct vlc_h2_frame *localize(struct vlc_h2_frame *f)
{
    f->data[5] = (STREAM_ID >> 24) & 0xff;
    f->data[6] = (STREAM_ID >> 16) & 0xff;
    f->data[7] = (STREAM_ID >>  8) & 0xff;
    f->data[8] =  STREAM_ID        & 0xff;
    return f;
}