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
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int INT ;

/* Variables and functions */
 int DT_METAFILE ; 
#define  TECHNOLOGY 129 
#define  TEXTCAPS 128 
 int /*<<< orphan*/  TRACE (char*,int) ; 

__attribute__((used)) static INT MFDRV_GetDeviceCaps(PHYSDEV dev, INT cap)
{
    switch(cap)
    {
    case TECHNOLOGY:
        return DT_METAFILE;
    case TEXTCAPS:
        return 0;
    default:
        TRACE(" unsupported capability %d, will return 0\n", cap );
    }
    return 0;
}