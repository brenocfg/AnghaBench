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
 int NOTIFY_ALL ; 
 int NOTIFY_EVICTED ; 
 int NOTIFY_EXPIRED ; 
 int NOTIFY_GENERIC ; 
 int NOTIFY_HASH ; 
 int NOTIFY_KEYEVENT ; 
 int NOTIFY_KEYSPACE ; 
 int NOTIFY_KEY_MISS ; 
 int NOTIFY_LIST ; 
 int NOTIFY_SET ; 
 int NOTIFY_STREAM ; 
 int NOTIFY_STRING ; 
 int NOTIFY_ZSET ; 

int keyspaceEventsStringToFlags(char *classes) {
    char *p = classes;
    int c, flags = 0;

    while((c = *p++) != '\0') {
        switch(c) {
        case 'A': flags |= NOTIFY_ALL; break;
        case 'g': flags |= NOTIFY_GENERIC; break;
        case '$': flags |= NOTIFY_STRING; break;
        case 'l': flags |= NOTIFY_LIST; break;
        case 's': flags |= NOTIFY_SET; break;
        case 'h': flags |= NOTIFY_HASH; break;
        case 'z': flags |= NOTIFY_ZSET; break;
        case 'x': flags |= NOTIFY_EXPIRED; break;
        case 'e': flags |= NOTIFY_EVICTED; break;
        case 'K': flags |= NOTIFY_KEYSPACE; break;
        case 'E': flags |= NOTIFY_KEYEVENT; break;
        case 't': flags |= NOTIFY_STREAM; break;
        case 'm': flags |= NOTIFY_KEY_MISS; break;
        default: return -1;
        }
    }
    return flags;
}