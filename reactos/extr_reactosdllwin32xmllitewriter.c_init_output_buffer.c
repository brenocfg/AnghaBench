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
struct output_buffer {int allocated; unsigned int codepage; scalar_t__ written; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  encoding; struct output_buffer buffer; } ;
typedef  TYPE_1__ xmlwriteroutput ;
typedef  unsigned int UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  get_code_page (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeroutput_alloc (TYPE_1__*,int const) ; 

__attribute__((used)) static HRESULT init_output_buffer(xmlwriteroutput *output)
{
    struct output_buffer *buffer = &output->buffer;
    const int initial_len = 0x2000;
    UINT cp = ~0u;
    HRESULT hr;

    if (FAILED(hr = get_code_page(output->encoding, &cp)))
        WARN("Failed to get code page for specified encoding.\n");

    buffer->data = writeroutput_alloc(output, initial_len);
    if (!buffer->data) return E_OUTOFMEMORY;

    memset(buffer->data, 0, 4);
    buffer->allocated = initial_len;
    buffer->written = 0;
    buffer->codepage = cp;

    return S_OK;
}