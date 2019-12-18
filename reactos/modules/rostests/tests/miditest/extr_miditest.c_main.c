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
typedef  int UINT ;
struct TYPE_3__ {char* szPname; } ;
typedef  TYPE_1__ MIDIOUTCAPS ;
typedef  char* HMIDIOUT ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_NULL ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ midiOutGetDevCaps (int,TYPE_1__*,int) ; 
 int midiOutGetNumDevs () ; 
 int midiOutOpen (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midiOutShortMsg (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main()
{
    UINT outs = midiOutGetNumDevs();
//    UINT ins = midiInGetNumDevs();

    MIDIOUTCAPS outcaps;
//    MIDIINCAPS incaps;

    int c;

    HMIDIOUT Handle = NULL;
    UINT Result;

    printf("MIDI output devices: %d\n", outs);

    for (c = 0; c < outs; c ++)
    {
        if (midiOutGetDevCaps(c, &outcaps, sizeof(MIDIOUTCAPS)) == MMSYSERR_NOERROR)
            printf("Device #%d: %s\n", c, outcaps.szPname);
    }

    printf("Opening MIDI output #0\n");

    Result = midiOutOpen(&Handle, 0, 0, 0, CALLBACK_NULL);
    printf("Result == %d Handle == %p\n", Result, Handle);

    // play something:
    midiOutShortMsg(Handle, 0x007f3090);

/*
    printf("\nMIDI input devices: %d\n", ins);

    for (c = 0; c < ins; c ++)
    {
        midiInGetDevCaps(c, &incaps, sizeof(incaps));
        printf("Device #%d: %s\n", c, incaps.szPname);
    }
*/
    return 0;
}