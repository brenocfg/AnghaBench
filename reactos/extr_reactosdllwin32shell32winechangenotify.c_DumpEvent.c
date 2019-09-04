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
typedef  int LONG ;

/* Variables and functions */
 int SHCNE_ALLEVENTS ; 
 int SHCNE_ASSOCCHANGED ; 
 int SHCNE_ATTRIBUTES ; 
 int SHCNE_CREATE ; 
 int SHCNE_DELETE ; 
 int SHCNE_DRIVEADD ; 
 int SHCNE_DRIVEADDGUI ; 
 int SHCNE_DRIVEREMOVED ; 
 int SHCNE_EXTENDED_EVENT ; 
 int SHCNE_FREESPACE ; 
 int SHCNE_INTERRUPT ; 
 int SHCNE_MEDIAINSERTED ; 
 int SHCNE_MEDIAREMOVED ; 
 int SHCNE_MKDIR ; 
 int SHCNE_NETSHARE ; 
 int SHCNE_NETUNSHARE ; 
 int SHCNE_RENAMEFOLDER ; 
 int SHCNE_RENAMEITEM ; 
 int SHCNE_RMDIR ; 
 int SHCNE_SERVERDISCONNECT ; 
 int SHCNE_UPDATEDIR ; 
 int SHCNE_UPDATEIMAGE ; 
 int SHCNE_UPDATEITEM ; 
 char const* wine_dbg_sprintf (char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static const char * DumpEvent( LONG event )
{
    if( event == SHCNE_ALLEVENTS )
        return "SHCNE_ALLEVENTS";
#define DUMPEV(x)  ,( event & SHCNE_##x )? #x " " : ""
    return wine_dbg_sprintf( "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
    DUMPEV(RENAMEITEM)
    DUMPEV(CREATE)
    DUMPEV(DELETE)
    DUMPEV(MKDIR)
    DUMPEV(RMDIR)
    DUMPEV(MEDIAINSERTED)
    DUMPEV(MEDIAREMOVED)
    DUMPEV(DRIVEREMOVED)
    DUMPEV(DRIVEADD)
    DUMPEV(NETSHARE)
    DUMPEV(NETUNSHARE)
    DUMPEV(ATTRIBUTES)
    DUMPEV(UPDATEDIR)
    DUMPEV(UPDATEITEM)
    DUMPEV(SERVERDISCONNECT)
    DUMPEV(UPDATEIMAGE)
    DUMPEV(DRIVEADDGUI)
    DUMPEV(RENAMEFOLDER)
    DUMPEV(FREESPACE)
    DUMPEV(EXTENDED_EVENT)
    DUMPEV(ASSOCCHANGED)
    DUMPEV(INTERRUPT)
    );
#undef DUMPEV
}