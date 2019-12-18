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
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DDHAL_CB32_CANCREATESURFACE ; 
 int /*<<< orphan*/  DDHAL_CB32_CREATEPALETTE ; 
 int /*<<< orphan*/  DDHAL_CB32_CREATESURFACE ; 
 int /*<<< orphan*/  DDHAL_CB32_GETSCANLINE ; 
 int /*<<< orphan*/  DDHAL_CB32_MAPMEMORY ; 
 int /*<<< orphan*/  DDHAL_CB32_SETCOLORKEY ; 
 int /*<<< orphan*/  DDHAL_CB32_SETMODE ; 
 int /*<<< orphan*/  DDHAL_CB32_WAITFORVERTICALBLANK ; 
 int /*<<< orphan*/  DDHAL_PALCB32_DESTROYPALETTE ; 
 int /*<<< orphan*/  DDHAL_PALCB32_SETENTRIES ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_ADDATTACHEDSURFACE ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_BLT ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_DESTROYSURFACE ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_FLIP ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_GETBLTSTATUS ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_GETFLIPSTATUS ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_LOCK ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_RESERVED4 ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_SETCLIPLIST ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_SETCOLORKEY ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_SETOVERLAYPOSITION ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_SETPALETTE ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_UNLOCK ; 
 int /*<<< orphan*/  DDHAL_SURFCB32_UPDATEOVERLAY ; 
 int /*<<< orphan*/  checkflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  endcheckflag (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
dump_CallBackFlags(DWORD *pCallBackFlags, char *text)
{
    UINT flag;
    INT count;

    printf("dumping the CallBackFlags from %s\n",text);
    printf("pCallBackFlags[0] : ");

    flag=pCallBackFlags[0];
    count=0;
    checkflag(flag,DDHAL_CB32_CANCREATESURFACE,"DDHAL_CB32_CANCREATESURFACE");
    checkflag(flag,DDHAL_CB32_CREATEPALETTE,"DDHAL_CB32_CREATEPALETTE");
    checkflag(flag,DDHAL_CB32_CREATESURFACE,"DDHAL_CB32_CREATESURFACE");
    checkflag(flag,DDHAL_CB32_GETSCANLINE,"DDHAL_CB32_GETSCANLINE");
    checkflag(flag,DDHAL_CB32_MAPMEMORY,"DDHAL_CB32_MAPMEMORY");
    checkflag(flag,DDHAL_CB32_SETCOLORKEY,"DDHAL_CB32_SETCOLORKEY");
    checkflag(flag,DDHAL_CB32_SETMODE,"DDHAL_CB32_SETMODE");
    checkflag(flag,DDHAL_CB32_WAITFORVERTICALBLANK,"DDHAL_CB32_WAITFORVERTICALBLANK");
    endcheckflag(flag,"pCallBackFlags[0]");

    /* SURFACE callback */
    printf("pCallBackFlags[1] : ");
    flag = pCallBackFlags[1];
    count = 0;
    checkflag(flag,DDHAL_SURFCB32_ADDATTACHEDSURFACE,"DDHAL_SURFCB32_ADDATTACHEDSURFACE");
    checkflag(flag,DDHAL_SURFCB32_BLT,"DDHAL_SURFCB32_BLT");
    checkflag(flag,DDHAL_SURFCB32_DESTROYSURFACE,"DDHAL_SURFCB32_DESTROYSURFACE");
    checkflag(flag,DDHAL_SURFCB32_FLIP,"DDHAL_SURFCB32_FLIP");
    checkflag(flag,DDHAL_SURFCB32_GETBLTSTATUS,"DDHAL_SURFCB32_GETBLTSTATUS");
    checkflag(flag,DDHAL_SURFCB32_GETFLIPSTATUS,"DDHAL_SURFCB32_GETFLIPSTATUS");
    checkflag(flag,DDHAL_SURFCB32_LOCK,"DDHAL_SURFCB32_LOCK");
    checkflag(flag,DDHAL_SURFCB32_RESERVED4,"DDHAL_SURFCB32_RESERVED4");
    checkflag(flag,DDHAL_SURFCB32_SETCLIPLIST,"DDHAL_SURFCB32_SETCLIPLIST");
    checkflag(flag,DDHAL_SURFCB32_SETCOLORKEY,"DDHAL_SURFCB32_SETCOLORKEY");
    checkflag(flag,DDHAL_SURFCB32_SETOVERLAYPOSITION,"DDHAL_SURFCB32_SETOVERLAYPOSITION");
    checkflag(flag,DDHAL_SURFCB32_SETPALETTE,"DDHAL_SURFCB32_SETPALETTE");
    checkflag(flag,DDHAL_SURFCB32_UNLOCK,"DDHAL_SURFCB32_UNLOCK");
    checkflag(flag,DDHAL_SURFCB32_UPDATEOVERLAY,"DDHAL_SURFCB32_UPDATEOVERLAY");
    endcheckflag(flag,"pCallBackFlags[1]");


    /* palleted */
    printf("pCallBackFlags[2] : ");
    flag = pCallBackFlags[2];
    count = 0;
    checkflag(flag,DDHAL_PALCB32_DESTROYPALETTE,"DDHAL_PALCB32_DESTROYPALETTE");
    checkflag(flag,DDHAL_PALCB32_SETENTRIES,"DDHAL_PALCB32_SETENTRIES");
    endcheckflag(flag,"pCallBackFlags[2]");
}