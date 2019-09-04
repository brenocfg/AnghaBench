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
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ MMRESULT ;

/* Variables and functions */
 scalar_t__ MMSYSERR_NOERROR ; 
 char* mmsys_error (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ waveInGetErrorTextA (scalar_t__,char*,int) ; 

__attribute__((used)) static const char * wave_in_error(MMRESULT error)
{
    static char msg[1024];
    static char long_msg[1100];
    MMRESULT rc;

    rc = waveInGetErrorTextA(error, msg, sizeof(msg));
    if (rc != MMSYSERR_NOERROR)
        sprintf(long_msg, "waveInGetErrorTextA(%x) failed with error %x", error, rc);
    else
        sprintf(long_msg, "%s(%s)", mmsys_error(error), msg);
    return long_msg;
}