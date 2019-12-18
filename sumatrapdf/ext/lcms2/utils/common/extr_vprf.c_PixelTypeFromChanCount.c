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
 int /*<<< orphan*/  FatalError (char*,int) ; 
 int PT_CMYK ; 
 int PT_GRAY ; 
 int PT_MCH10 ; 
 int PT_MCH11 ; 
 int PT_MCH12 ; 
 int PT_MCH13 ; 
 int PT_MCH14 ; 
 int PT_MCH15 ; 
 int PT_MCH2 ; 
 int PT_MCH3 ; 
 int PT_MCH5 ; 
 int PT_MCH6 ; 
 int PT_MCH7 ; 
 int PT_MCH8 ; 
 int PT_MCH9 ; 

int PixelTypeFromChanCount(int ColorChannels)
{
    switch (ColorChannels) {

        case 1: return PT_GRAY;
        case 2: return PT_MCH2;
        case 3: return PT_MCH3;
        case 4: return PT_CMYK;
        case 5: return PT_MCH5;
        case 6: return PT_MCH6;
        case 7: return PT_MCH7;
        case 8: return PT_MCH8;
        case 9: return PT_MCH9;
        case 10: return PT_MCH10;
        case 11: return PT_MCH11;
        case 12: return PT_MCH12;
        case 13: return PT_MCH13;
        case 14: return PT_MCH14;
        case 15: return PT_MCH15;

        default:

            FatalError("What a weird separation of %d channels?!?!", ColorChannels);
            return -1;
    }
}