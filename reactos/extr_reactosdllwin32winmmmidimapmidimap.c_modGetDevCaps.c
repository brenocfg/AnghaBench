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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int wMid; int wPid; int vDriverVersion; int wChannelMask; long dwSupport; scalar_t__ wNotes; scalar_t__ wVoices; int /*<<< orphan*/  wTechnology; int /*<<< orphan*/  szPname; } ;
typedef  int /*<<< orphan*/  MIDIMAPDATA ;
typedef  TYPE_1__* LPMIDIOUTCAPSW ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MOD_MAPPER ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static	DWORD	modGetDevCaps(UINT wDevID, MIDIMAPDATA* mom, LPMIDIOUTCAPSW lpMidiCaps, DWORD_PTR size)
{
    static const WCHAR name[] = {'W','i','n','e',' ','m','i','d','i',' ','m','a','p','p','e','r',0};
    lpMidiCaps->wMid = 0x00FF;
    lpMidiCaps->wPid = 0x0001;
    lpMidiCaps->vDriverVersion = 0x0100;
    lstrcpyW(lpMidiCaps->szPname, name);
    lpMidiCaps->wTechnology = MOD_MAPPER;
    lpMidiCaps->wVoices = 0;
    lpMidiCaps->wNotes = 0;
    lpMidiCaps->wChannelMask = 0xFFFF;
    lpMidiCaps->dwSupport = 0L;

    return MMSYSERR_NOERROR;
}