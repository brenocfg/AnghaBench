#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ written; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_3__ encoded; } ;
struct TYPE_6__ {scalar_t__ xml_enc; int /*<<< orphan*/  dest; TYPE_1__ buffer; } ;
typedef  TYPE_2__ mxwriter ;
typedef  TYPE_3__ encoded_buffer ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ XmlEncoding_UTF8 ; 

__attribute__((used)) static HRESULT write_data_to_stream(mxwriter *writer)
{
    encoded_buffer *buffer = &writer->buffer.encoded;
    ULONG written = 0;

    if (!writer->dest)
        return S_OK;

    if (buffer->written == 0)
    {
        if (writer->xml_enc == XmlEncoding_UTF8)
            IStream_Write(writer->dest, buffer->data, 0, &written);
    }
    else
    {
        IStream_Write(writer->dest, buffer->data, buffer->written, &written);
        buffer->written = 0;
    }

    return S_OK;
}