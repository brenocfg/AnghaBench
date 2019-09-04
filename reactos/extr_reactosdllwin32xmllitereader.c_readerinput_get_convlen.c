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
struct TYPE_7__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ xmlreaderinput ;
struct TYPE_8__ {int written; int cur; } ;
typedef  TYPE_3__ encoded_buffer ;
struct TYPE_6__ {scalar_t__ code_page; TYPE_3__ encoded; } ;

/* Variables and functions */
 scalar_t__ CP_UTF8 ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int readerinput_get_utf8_convlen (TYPE_2__*) ; 

__attribute__((used)) static int readerinput_get_convlen(xmlreaderinput *readerinput)
{
    encoded_buffer *buffer = &readerinput->buffer->encoded;
    int len;

    if (readerinput->buffer->code_page == CP_UTF8)
        len = readerinput_get_utf8_convlen(readerinput);
    else
        len = buffer->written;

    TRACE("%d\n", len - buffer->cur);
    return len - buffer->cur;
}