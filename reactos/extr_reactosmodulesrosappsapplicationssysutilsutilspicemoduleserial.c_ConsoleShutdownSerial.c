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
 int /*<<< orphan*/  Connect (int,int) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FlushSerialBuffer () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PICE_free (scalar_t__) ; 
 scalar_t__ pScreenBufferSerial ; 

void ConsoleShutdownSerial(void)
{
    ENTER_FUNC();

    Connect(80,25);

    FlushSerialBuffer();

    if(pScreenBufferSerial)
        PICE_free(pScreenBufferSerial);

    LEAVE_FUNC();
}