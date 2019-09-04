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
struct TYPE_7__ {int hour; int min; int sec; int frame; } ;
struct TYPE_8__ {int cb; int sample; int ms; TYPE_1__ smpte; } ;
struct TYPE_10__ {scalar_t__ wType; TYPE_2__ u; } ;
struct TYPE_9__ {int nBlockAlign; int nAvgBytesPerSec; } ;
typedef  TYPE_3__* LPWAVEFORMATEX ;
typedef  TYPE_4__* LPMMTIME ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ TIME_BYTES ; 
 scalar_t__ TIME_MS ; 
 scalar_t__ TIME_SAMPLES ; 
 scalar_t__ TIME_SMPTE ; 
 int /*<<< orphan*/  trace (char*) ; 

DWORD time_to_bytes(LPMMTIME mmtime, LPWAVEFORMATEX pwfx)
{
    if (mmtime->wType == TIME_BYTES)
        return mmtime->u.cb;
    else if (mmtime->wType == TIME_SAMPLES)
        return mmtime->u.sample * pwfx->nBlockAlign;
    else if (mmtime->wType == TIME_MS)
        return mmtime->u.ms * pwfx->nAvgBytesPerSec / 1000;
    else if (mmtime->wType == TIME_SMPTE)
        return ((mmtime->u.smpte.hour * 60 * 60) +
                (mmtime->u.smpte.min * 60) +
                (mmtime->u.smpte.sec)) * pwfx->nAvgBytesPerSec +
                mmtime->u.smpte.frame  * pwfx->nAvgBytesPerSec / 30;

    trace("FIXME: time_to_bytes() type not supported\n");
    return -1;
}