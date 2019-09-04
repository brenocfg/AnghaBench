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

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FONTBUFFERSIZE ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  MmUnmapIoSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PICE_free (scalar_t__) ; 
 int /*<<< orphan*/  SCREEN_BUFFER_SIZE ; 
 int /*<<< orphan*/  pFontBufferVga ; 
 int /*<<< orphan*/  pScreenBufferHardwareVga ; 
 scalar_t__ pScreenBufferTempVga ; 
 scalar_t__ pScreenBufferVga ; 

void ConsoleShutdownVga(void)
{
    ENTER_FUNC();

	if(pScreenBufferVga)
    {
        PICE_free(pScreenBufferVga);
        PICE_free(pScreenBufferTempVga);
		MmUnmapIoSpace(pScreenBufferHardwareVga,SCREEN_BUFFER_SIZE);
		MmUnmapIoSpace(pFontBufferVga,FONTBUFFERSIZE);
    }

    LEAVE_FUNC();
}