#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* input; } ;
typedef  TYPE_3__ xmlreader ;
struct TYPE_10__ {int cur; scalar_t__ data; } ;
typedef  TYPE_4__ encoded_buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {TYPE_1__* buffer; } ;
struct TYPE_7__ {TYPE_4__ utf16; } ;

/* Variables and functions */
 int /*<<< orphan*/  reader_more (TYPE_3__*) ; 

__attribute__((used)) static inline WCHAR *reader_get_ptr(xmlreader *reader)
{
    encoded_buffer *buffer = &reader->input->buffer->utf16;
    WCHAR *ptr = (WCHAR*)buffer->data + buffer->cur;
    if (!*ptr) reader_more(reader);
    return (WCHAR*)buffer->data + buffer->cur;
}