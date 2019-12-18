#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; } ;
typedef  TYPE_1__ robj ;
struct TYPE_12__ {scalar_t__ argc; int /*<<< orphan*/  db; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;

/* Variables and functions */
 scalar_t__ OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  addReplyGopherItem (TYPE_2__*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* createStringObject (char*,int) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 TYPE_1__* lookupKeyRead (int /*<<< orphan*/ ,TYPE_1__*) ; 

void processGopherRequest(client *c) {
    robj *keyname = c->argc == 0 ? createStringObject("/",1) : c->argv[0];
    robj *o = lookupKeyRead(c->db,keyname);

    /* If there is no such key, return with a Gopher error. */
    if (o == NULL || o->type != OBJ_STRING) {
        char *errstr;
        if (o == NULL)
            errstr = "Error: no content at the specified key";
        else
            errstr = "Error: selected key type is invalid "
                     "for Gopher output";
        addReplyGopherItem(c,"i",errstr,NULL,NULL,0);
        addReplyGopherItem(c,"i","Redis Gopher server",NULL,NULL,0);
    } else {
        addReply(c,o);
    }

    /* Cleanup, also make sure to emit the final ".CRLF" line. Note that
     * the connection will be closed immediately after this because the client
     * will be flagged with CLIENT_CLOSE_AFTER_REPLY, in accordance with the
     * Gopher protocol. */
    if (c->argc == 0) decrRefCount(keyname);

    /* Note that in theory we should terminate the Gopher request with
     * ".<CR><LF>" (called Lastline in the RFC) like that:
     *
     * addReplyProto(c,".\r\n",3);
     *
     * However after examining the current clients landscape, it's probably
     * going to do more harm than good for several reasons:
     *
     * 1. Clients should not have any issue with missing .<CR><LF> as for
     *    specification, and in the real world indeed certain servers
     *    implementations never used to send the terminator.
     *
     * 2. Redis does not know if it's serving a text file or a binary file:
     *    at the same time clients will not remove the ".<CR><LF>" bytes at
     *    tne end when downloading a binary file from the server, so adding
     *    the "Lastline" terminator without knowing the content is just
     *    dangerous.
     *
     * 3. The utility gopher2redis.rb that we provide for Redis, and any
     *    other similar tool you may use as Gopher authoring system for
     *    Redis, can just add the "Lastline" when needed.
     */
}