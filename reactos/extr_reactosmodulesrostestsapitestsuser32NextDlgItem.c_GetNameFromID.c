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
typedef  int INT ;

/* Variables and functions */
#define  IDCANCEL 136 
#define  IDOK 135 
#define  psh1 134 
#define  rad1 133 
#define  rad2 132 
#define  rad3 131 
#define  rad5 130 
#define  rad6 129 
#define  rad7 128 

__attribute__((used)) static const char *
GetNameFromID(INT ID)
{
    switch (ID)
    {
        case rad1:      return "rad1";
        case rad2:      return "rad2";
        case rad3:      return "rad3";
        case psh1:      return "psh1";
        case rad5:      return "rad5";
        case rad6:      return "rad6";
        case rad7:      return "rad7";
        case IDOK:      return "OK button";
        case IDCANCEL:  return "Cancel button";
        default:        return "(unknown)";
    }
}