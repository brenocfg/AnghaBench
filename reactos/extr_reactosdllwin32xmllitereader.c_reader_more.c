#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ xmlreaderinput ;
struct TYPE_13__ {TYPE_2__* input; } ;
typedef  TYPE_3__ xmlreader ;
struct TYPE_14__ {int written; scalar_t__ cur; scalar_t__ data; } ;
typedef  TYPE_4__ encoded_buffer ;
typedef  scalar_t__ WCHAR ;
typedef  int UINT ;
struct TYPE_11__ {int code_page; TYPE_4__ utf16; TYPE_4__ encoded; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int MultiByteToWideChar (int,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  fixup_buffer_cr (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int readerinput_get_convlen (TYPE_2__*) ; 
 int /*<<< orphan*/  readerinput_grow (TYPE_2__*,int) ; 
 int /*<<< orphan*/  readerinput_growraw (TYPE_2__*) ; 
 int /*<<< orphan*/  readerinput_shrinkraw (TYPE_2__*,int) ; 

__attribute__((used)) static HRESULT reader_more(xmlreader *reader)
{
    xmlreaderinput *readerinput = reader->input;
    encoded_buffer *src = &readerinput->buffer->encoded;
    encoded_buffer *dest = &readerinput->buffer->utf16;
    UINT cp = readerinput->buffer->code_page;
    int len, dest_len, prev_len;
    HRESULT hr;
    WCHAR *ptr;

    /* get some raw data from stream first */
    hr = readerinput_growraw(readerinput);
    len = readerinput_get_convlen(readerinput);
    prev_len = dest->written / sizeof(WCHAR);

    /* just copy for UTF-16 case */
    if (cp == 1200)
    {
        readerinput_grow(readerinput, len);
        memcpy(dest->data + dest->written, src->data + src->cur, len);
        dest->written += len*sizeof(WCHAR);
    }
    else
    {
        dest_len = MultiByteToWideChar(cp, 0, src->data + src->cur, len, NULL, 0);
        readerinput_grow(readerinput, dest_len);
        ptr = (WCHAR*)(dest->data + dest->written);
        MultiByteToWideChar(cp, 0, src->data + src->cur, len, ptr, dest_len);
        ptr[dest_len] = 0;
        dest->written += dest_len*sizeof(WCHAR);
        /* get rid of processed data */
        readerinput_shrinkraw(readerinput, len);
    }

    fixup_buffer_cr(dest, prev_len);
    return hr;
}