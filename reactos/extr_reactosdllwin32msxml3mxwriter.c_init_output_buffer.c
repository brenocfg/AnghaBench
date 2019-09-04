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
typedef  int /*<<< orphan*/  xml_encoding ;
struct TYPE_3__ {scalar_t__ utf16_total; int /*<<< orphan*/  blocks; int /*<<< orphan*/  encoded; int /*<<< orphan*/  code_page; } ;
typedef  TYPE_1__ output_buffer ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ S_OK ; 
 scalar_t__ get_code_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ init_encoded_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT init_output_buffer(xml_encoding encoding, output_buffer *buffer)
{
    HRESULT hr;

    hr = get_code_page(encoding, &buffer->code_page);
    if (hr != S_OK)
        return hr;

    hr = init_encoded_buffer(&buffer->encoded);
    if (hr != S_OK)
        return hr;

    list_init(&buffer->blocks);
    buffer->utf16_total = 0;

    return S_OK;
}