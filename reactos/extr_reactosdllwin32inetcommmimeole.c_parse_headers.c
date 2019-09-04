#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* prop; int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ header_t ;
struct TYPE_14__ {int /*<<< orphan*/  headers; } ;
struct TYPE_12__ {int id; } ;
typedef  TYPE_3__ MimeBody ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  PID_HDR_CNTTYPE 129 
#define  PID_HDR_CNTXFER 128 
 int /*<<< orphan*/  copy_headers_to_buf (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  init_content_encoding (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  init_content_type (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* read_prop (TYPE_3__*,char**) ; 
 int /*<<< orphan*/  read_value (TYPE_2__*,char**) ; 

__attribute__((used)) static HRESULT parse_headers(MimeBody *body, IStream *stm)
{
    char *header_buf, *cur_header_ptr;
    HRESULT hr;
    header_t *header;

    hr = copy_headers_to_buf(stm, &header_buf);
    if(FAILED(hr)) return hr;

    cur_header_ptr = header_buf;
    while((header = read_prop(body, &cur_header_ptr)))
    {
        read_value(header, &cur_header_ptr);
        list_add_tail(&body->headers, &header->entry);

        switch(header->prop->id) {
        case PID_HDR_CNTTYPE:
            init_content_type(body, header);
            break;
        case PID_HDR_CNTXFER:
            init_content_encoding(body, header);
            break;
        }
    }

    HeapFree(GetProcessHeap(), 0, header_buf);
    return hr;
}