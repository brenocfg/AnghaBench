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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */

__attribute__((used)) static VOID PrintEvents( ULONG Events ) {
#if DBG
    char *events_list[] = { "AFD_EVENT_RECEIVE",
                            "AFD_EVENT_OOB_RECEIVE",
                            "AFD_EVENT_SEND",
                            "AFD_EVENT_DISCONNECT",
                            "AFD_EVENT_ABORT",
                            "AFD_EVENT_CLOSE",
                            "AFD_EVENT_CONNECT",
                            "AFD_EVENT_ACCEPT",
                            "AFD_EVENT_CONNECT_FAIL",
                            "AFD_EVENT_QOS",
                            "AFD_EVENT_GROUP_QOS",
                            NULL };
    int i;

    for( i = 0; events_list[i]; i++ )
        if( Events & (1 << i) ) AFD_DbgPrint(MID_TRACE,("%s ", events_list[i] ));
#endif
}