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
struct TYPE_3__ {scalar_t__ dwDriver; } ;
typedef  TYPE_1__* PACMDRVSTREAMINSTANCE ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 

__attribute__((used)) static	LRESULT	ADPCM_StreamClose(PACMDRVSTREAMINSTANCE adsi)
{
    HeapFree(GetProcessHeap(), 0, (void*)adsi->dwDriver);
    return MMSYSERR_NOERROR;
}