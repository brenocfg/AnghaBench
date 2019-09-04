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
struct TYPE_2__ {int len; char* data; } ;
struct output_stream {TYPE_1__ gif_block; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 scalar_t__ IStream_Write (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static inline int write_byte(struct output_stream *out, char byte)
{
    if (out->gif_block.len == 255)
    {
        if (IStream_Write(out->out, &out->gif_block, sizeof(out->gif_block), NULL) != S_OK)
            return 0;

        out->gif_block.len = 0;
    }

    out->gif_block.data[out->gif_block.len++] = byte;

    return 1;
}