#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PCONSOLE_SCREEN_BUFFER ;
typedef  int /*<<< orphan*/  CONSOLE_IO_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  TEXTMODE_BUFFER ; 

CONSOLE_IO_OBJECT_TYPE
TEXTMODE_BUFFER_GetType(PCONSOLE_SCREEN_BUFFER This)
{
    // return This->Header.Type;
    return TEXTMODE_BUFFER;
}