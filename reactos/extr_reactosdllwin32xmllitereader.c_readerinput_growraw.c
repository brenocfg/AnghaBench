#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pending; int /*<<< orphan*/  stream; TYPE_1__* buffer; } ;
typedef  TYPE_2__ xmlreaderinput ;
struct TYPE_8__ {int allocated; int written; int data; } ;
typedef  TYPE_3__ encoded_buffer ;
typedef  int ULONG ;
struct TYPE_6__ {TYPE_3__ encoded; } ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_PENDING ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ ISequentialStream_Read (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int,int,int,int,scalar_t__) ; 
 int readerinput_realloc (TYPE_2__*,int,int) ; 

__attribute__((used)) static HRESULT readerinput_growraw(xmlreaderinput *readerinput)
{
    encoded_buffer *buffer = &readerinput->buffer->encoded;
    /* to make sure aligned length won't exceed allocated length */
    ULONG len = buffer->allocated - buffer->written - 4;
    ULONG read;
    HRESULT hr;

    /* always try to get aligned to 4 bytes, so the only case we can get partially read characters is
       variable width encodings like UTF-8 */
    len = (len + 3) & ~3;
    /* try to use allocated space or grow */
    if (buffer->allocated - buffer->written < len)
    {
        buffer->allocated *= 2;
        buffer->data = readerinput_realloc(readerinput, buffer->data, buffer->allocated);
        len = buffer->allocated - buffer->written;
    }

    read = 0;
    hr = ISequentialStream_Read(readerinput->stream, buffer->data + buffer->written, len, &read);
    TRACE("written=%d, alloc=%d, requested=%d, read=%d, ret=0x%08x\n", buffer->written, buffer->allocated, len, read, hr);
    readerinput->pending = hr == E_PENDING;
    if (FAILED(hr)) return hr;
    buffer->written += read;

    return hr;
}