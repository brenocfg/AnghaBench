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
typedef  size_t UCHAR ;
typedef  int /*<<< orphan*/  MMRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CleanupEntrypointMutexes () ; 
 int /*<<< orphan*/ * CreateMutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** EntrypointMutexes ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 size_t SOUND_DEVICE_TYPES ; 
 int /*<<< orphan*/  Win32ErrorToMmResult (int /*<<< orphan*/ ) ; 

MMRESULT
InitEntrypointMutexes()
{
    UCHAR i;
    MMRESULT Result = MMSYSERR_NOERROR;

    /* Blank all entries ni the table first */
    for ( i = 0; i < SOUND_DEVICE_TYPES; ++ i )
    {
        EntrypointMutexes[i] = NULL;
    }

    /* Now create the mutexes */
    for ( i = 0; i < SOUND_DEVICE_TYPES; ++ i )
    {
        EntrypointMutexes[i] = CreateMutex(NULL, FALSE, NULL);

        if ( ! EntrypointMutexes[i] )
        {
            Result = Win32ErrorToMmResult(GetLastError());

            /* Clean up any mutexes we successfully created */
            CleanupEntrypointMutexes();
            break;
        }
    }

    return Result;
}