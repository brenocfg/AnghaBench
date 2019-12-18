#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ByteReader {TYPE_2__* input; TYPE_3__* zip; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_left; } ;
struct TYPE_6__ {TYPE_1__ progress; } ;
struct TYPE_5__ {int* data; int /*<<< orphan*/  offset; int /*<<< orphan*/  bytes_left; } ;
typedef  int Byte ;

/* Variables and functions */
 int /*<<< orphan*/  zip_fill_input_buffer (TYPE_3__*) ; 

__attribute__((used)) static Byte gPpmd_ByteIn_Read(void *p)
{
    struct ByteReader *self = p;
    if (!self->input->bytes_left && (!self->zip->progress.data_left || !zip_fill_input_buffer(self->zip)))
        return 0xFF;
    self->input->bytes_left--;
    return self->input->data[self->input->offset++];
}