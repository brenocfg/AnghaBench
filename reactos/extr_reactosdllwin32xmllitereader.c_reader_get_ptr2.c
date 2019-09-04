#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* input; } ;
typedef  TYPE_3__ xmlreader ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_4__ encoded_buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_7__ {TYPE_1__* buffer; } ;
struct TYPE_6__ {TYPE_4__ utf16; } ;

/* Variables and functions */

__attribute__((used)) static inline WCHAR *reader_get_ptr2(const xmlreader *reader, UINT offset)
{
    encoded_buffer *buffer = &reader->input->buffer->utf16;
    return (WCHAR*)buffer->data + offset;
}