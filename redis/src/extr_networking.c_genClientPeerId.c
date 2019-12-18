#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ client ;
struct TYPE_5__ {char* unixsocket; } ;

/* Variables and functions */
 int CLIENT_UNIX_SOCKET ; 
 int /*<<< orphan*/  connFormatPeer (int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

void genClientPeerId(client *client, char *peerid,
                            size_t peerid_len) {
    if (client->flags & CLIENT_UNIX_SOCKET) {
        /* Unix socket client. */
        snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
    } else {
        /* TCP client. */
        connFormatPeer(client->conn,peerid,peerid_len);
    }
}