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
typedef  int UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_ALLOCATED ; 
 int /*<<< orphan*/  DSERR_GENERIC ; 
 int /*<<< orphan*/  DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DSERR_UNSUPPORTED ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  MMSYSERR_ALLOCATED 138 
#define  MMSYSERR_ERROR 137 
#define  MMSYSERR_INVALHANDLE 136 
#define  MMSYSERR_INVALPARAM 135 
#define  MMSYSERR_NODRIVER 134 
#define  MMSYSERR_NOERROR 133 
#define  MMSYSERR_NOMEM 132 
#define  MMSYSERR_NOTSUPPORTED 131 
#define  WAVERR_BADFORMAT 130 
#define  WAVERR_STILLPLAYING 129 
#define  WAVERR_UNPREPARED 128 

HRESULT mmErr(UINT err)
{
	switch(err) {
	case MMSYSERR_NOERROR:
		return DS_OK;
	case MMSYSERR_ALLOCATED:
		return DSERR_ALLOCATED;
	case MMSYSERR_ERROR:
	case MMSYSERR_INVALHANDLE:
	case WAVERR_STILLPLAYING:
		return DSERR_GENERIC; /* FIXME */
	case MMSYSERR_NODRIVER:
		return DSERR_NODRIVER;
	case MMSYSERR_NOMEM:
		return DSERR_OUTOFMEMORY;
	case MMSYSERR_INVALPARAM:
	case WAVERR_BADFORMAT:
	case WAVERR_UNPREPARED:
		return DSERR_INVALIDPARAM;
	case MMSYSERR_NOTSUPPORTED:
		return DSERR_UNSUPPORTED;
	default:
		FIXME("Unknown MMSYS error %d\n",err);
		return DSERR_GENERIC;
	}
}