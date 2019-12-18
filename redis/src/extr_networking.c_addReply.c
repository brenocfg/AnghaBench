#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* ptr; scalar_t__ encoding; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  client ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ OBJ_ENCODING_INT ; 
 int /*<<< orphan*/  _addReplyProtoToList (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ _addReplyToBuffer (int /*<<< orphan*/ *,char*,size_t) ; 
 size_t ll2string (char*,int,long) ; 
 scalar_t__ prepareClientToWrite (int /*<<< orphan*/ *) ; 
 scalar_t__ sdsEncodedObject (TYPE_1__*) ; 
 size_t sdslen (char*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

void addReply(client *c, robj *obj) {
    if (prepareClientToWrite(c) != C_OK) return;

    if (sdsEncodedObject(obj)) {
        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != C_OK)
            _addReplyProtoToList(c,obj->ptr,sdslen(obj->ptr));
    } else if (obj->encoding == OBJ_ENCODING_INT) {
        /* For integer encoded strings we just convert it into a string
         * using our optimized function, and attach the resulting string
         * to the output buffer. */
        char buf[32];
        size_t len = ll2string(buf,sizeof(buf),(long)obj->ptr);
        if (_addReplyToBuffer(c,buf,len) != C_OK)
            _addReplyProtoToList(c,buf,len);
    } else {
        serverPanic("Wrong obj->encoding in addReply()");
    }
}