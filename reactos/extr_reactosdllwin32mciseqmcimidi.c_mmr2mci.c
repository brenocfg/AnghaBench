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
typedef  int DWORD ;

/* Variables and functions */
 int MCIERR_OUT_OF_MEMORY ; 
 int MCIERR_SEQ_PORT_INUSE ; 
 int MCIERR_SEQ_PORT_MAPNODEVICE ; 
 int MCIERR_SEQ_PORT_NONEXISTENT ; 
#define  MIDIERR_INVALIDSETUP 131 
#define  MMSYSERR_ALLOCATED 130 
#define  MMSYSERR_BADDEVICEID 129 
#define  MMSYSERR_NOMEM 128 

__attribute__((used)) static DWORD mmr2mci(DWORD ret)
{
    switch (ret) {
    case MMSYSERR_ALLOCATED:
	return			MCIERR_SEQ_PORT_INUSE;
    case MMSYSERR_NOMEM:
	return			MCIERR_OUT_OF_MEMORY;
    case MMSYSERR_BADDEVICEID:	/* wine*.drv disabled */
      return			MCIERR_SEQ_PORT_NONEXISTENT;
    case MIDIERR_INVALIDSETUP:	/* from midimap.dll without snd-seq module  */
	return			MCIERR_SEQ_PORT_MAPNODEVICE;
    default:
	return ret;
    }
}