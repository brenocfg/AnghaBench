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
#define  DSSCL_EXCLUSIVE 131 
#define  DSSCL_NORMAL 130 
#define  DSSCL_PRIORITY 129 
#define  DSSCL_WRITEPRIMARY 128 
 char const* wine_dbg_sprintf (char*,int) ; 

const char * dumpCooperativeLevel(DWORD level)
{
#define LE(x) case x: return #x
    switch (level) {
        LE(DSSCL_NORMAL);
        LE(DSSCL_PRIORITY);
        LE(DSSCL_EXCLUSIVE);
        LE(DSSCL_WRITEPRIMARY);
    }
#undef LE
    return wine_dbg_sprintf("Unknown(%08x)", level);
}