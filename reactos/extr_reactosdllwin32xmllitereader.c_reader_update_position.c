#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int line_position; int /*<<< orphan*/  line_number; } ;
struct TYPE_5__ {TYPE_1__ position; } ;
typedef  TYPE_2__ xmlreader ;
typedef  char WCHAR ;

/* Variables and functions */

__attribute__((used)) static void reader_update_position(xmlreader *reader, WCHAR ch)
{
    if (ch == '\r')
        reader->position.line_position = 1;
    else if (ch == '\n')
    {
        reader->position.line_number++;
        reader->position.line_position = 1;
    }
    else
        reader->position.line_position++;
}