#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct output_buffer {int codepage; char* data; int written; } ;
struct TYPE_4__ {struct output_buffer buffer; } ;
typedef  TYPE_1__ xmlwriteroutput ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int WideCharToMultiByte (int,int /*<<< orphan*/ ,scalar_t__ const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grow_output_buffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__ const*,int) ; 
 int strlenW (scalar_t__ const*) ; 

__attribute__((used)) static HRESULT write_output_buffer(xmlwriteroutput *output, const WCHAR *data, int len)
{
    struct output_buffer *buffer = &output->buffer;
    int length;
    HRESULT hr;
    char *ptr;

    if (buffer->codepage == 1200) {
        /* For UTF-16 encoding just copy. */
        length = len == -1 ? strlenW(data) : len;
        if (length) {
            length *= sizeof(WCHAR);

            hr = grow_output_buffer(output, length);
            if (FAILED(hr)) return hr;
            ptr = buffer->data + buffer->written;

            memcpy(ptr, data, length);
            buffer->written += length;
            ptr += length;
            /* null termination */
            *(WCHAR*)ptr = 0;
        }
    }
    else {
        length = WideCharToMultiByte(buffer->codepage, 0, data, len, NULL, 0, NULL, NULL);
        hr = grow_output_buffer(output, length);
        if (FAILED(hr)) return hr;
        ptr = buffer->data + buffer->written;
        length = WideCharToMultiByte(buffer->codepage, 0, data, len, ptr, length, NULL, NULL);
        buffer->written += len == -1 ? length-1 : length;
    }

    return S_OK;
}