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
typedef  char* LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
#define  DPSYS_ADDGROUPTOGROUP 143 
#define  DPSYS_ADDPLAYERTOGROUP 142 
#define  DPSYS_CHAT 141 
#define  DPSYS_CREATEPLAYERORGROUP 140 
#define  DPSYS_DELETEGROUPFROMGROUP 139 
#define  DPSYS_DELETEPLAYERFROMGROUP 138 
#define  DPSYS_DESTROYPLAYERORGROUP 137 
#define  DPSYS_HOST 136 
#define  DPSYS_SECUREMESSAGE 135 
#define  DPSYS_SENDCOMPLETE 134 
#define  DPSYS_SESSIONLOST 133 
#define  DPSYS_SETGROUPOWNER 132 
#define  DPSYS_SETPLAYERORGROUPDATA 131 
#define  DPSYS_SETPLAYERORGROUPNAME 130 
#define  DPSYS_SETSESSIONDESC 129 
#define  DPSYS_STARTSESSION 128 

__attribute__((used)) static LPCSTR dpMsgType2str(DWORD dwType)
{
    switch(dwType)
    {
    case DPSYS_CREATEPLAYERORGROUP:      return "DPSYS_CREATEPLAYERORGROUP";
    case DPSYS_DESTROYPLAYERORGROUP:     return "DPSYS_DESTROYPLAYERORGROUP";
    case DPSYS_ADDPLAYERTOGROUP:         return "DPSYS_ADDPLAYERTOGROUP";
    case DPSYS_DELETEPLAYERFROMGROUP:    return "DPSYS_DELETEPLAYERFROMGROUP";
    case DPSYS_SESSIONLOST:              return "DPSYS_SESSIONLOST";
    case DPSYS_HOST:                     return "DPSYS_HOST";
    case DPSYS_SETPLAYERORGROUPDATA:     return "DPSYS_SETPLAYERORGROUPDATA";
    case DPSYS_SETPLAYERORGROUPNAME:     return "DPSYS_SETPLAYERORGROUPNAME";
    case DPSYS_SETSESSIONDESC:           return "DPSYS_SETSESSIONDESC";
    case DPSYS_ADDGROUPTOGROUP:          return "DPSYS_ADDGROUPTOGROUP";
    case DPSYS_DELETEGROUPFROMGROUP:     return "DPSYS_DELETEGROUPFROMGROUP";
    case DPSYS_SECUREMESSAGE:            return "DPSYS_SECUREMESSAGE";
    case DPSYS_STARTSESSION:             return "DPSYS_STARTSESSION";
    case DPSYS_CHAT:                     return "DPSYS_DPSYS_CHAT";
    case DPSYS_SETGROUPOWNER:            return "DPSYS_SETGROUPOWNER";
    case DPSYS_SENDCOMPLETE:             return "DPSYS_SENDCOMPLETE";

    default:                             return "UNKNOWN";
    }
}