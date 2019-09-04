#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct output_buffer {scalar_t__ written; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream; struct output_buffer buffer; } ;
typedef  TYPE_1__ xmlwriteroutput ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISequentialStream_Write (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT writeroutput_flush_stream(xmlwriteroutput *output)
{
    struct output_buffer *buffer;
    ULONG written, offset = 0;
    HRESULT hr;

    if (!output || !output->stream)
        return S_OK;

    buffer = &output->buffer;

    /* It will loop forever until everything is written or an error occurred. */
    do {
        written = 0;
        hr = ISequentialStream_Write(output->stream, buffer->data + offset, buffer->written, &written);
        if (FAILED(hr)) {
            WARN("write to stream failed (0x%08x)\n", hr);
            buffer->written = 0;
            return hr;
        }

        offset += written;
        buffer->written -= written;
    } while (buffer->written > 0);

    return S_OK;
}