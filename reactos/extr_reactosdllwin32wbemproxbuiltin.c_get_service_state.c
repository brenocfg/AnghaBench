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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  SERVICE_RUNNING 131 
#define  SERVICE_START_PENDING 130 
#define  SERVICE_STOPPED 129 
#define  SERVICE_STOP_PENDING 128 

__attribute__((used)) static const WCHAR *get_service_state( DWORD state )
{
    static const WCHAR runningW[] =
        {'R','u','n','n','i','n','g',0};
    static const WCHAR start_pendingW[] =
        {'S','t','a','r','t',' ','P','e','n','d','i','n','g',0};
    static const WCHAR stop_pendingW[] =
        {'S','t','o','p',' ','P','e','n','d','i','n','g',0};
    static const WCHAR stoppedW[] =
        {'S','t','o','p','p','e','d',0};
    static const WCHAR unknownW[] =
        {'U','n','k','n','o','w','n',0};

    switch (state)
    {
    case SERVICE_STOPPED:       return stoppedW;
    case SERVICE_START_PENDING: return start_pendingW;
    case SERVICE_STOP_PENDING:  return stop_pendingW;
    case SERVICE_RUNNING:       return runningW;
    default:
        ERR("unknown state %u\n", state);
        return unknownW;
    }
}