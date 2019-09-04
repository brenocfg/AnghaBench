#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char* sds ;
struct TYPE_5__ {scalar_t__ encoding; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 long long LLONG_MAX ; 
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  addReplyNull (int /*<<< orphan*/ *) ; 
 unsigned char* hashTypeGetFromHashTable (TYPE_1__*,unsigned char*) ; 
 int hashTypeGetFromZiplist (TYPE_1__*,unsigned char*,unsigned char**,unsigned int*,long long*) ; 
 unsigned int sdslen (unsigned char*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

__attribute__((used)) static void addHashFieldToReply(client *c, robj *o, sds field) {
    int ret;

    if (o == NULL) {
        addReplyNull(c);
        return;
    }

    if (o->encoding == OBJ_ENCODING_ZIPLIST) {
        unsigned char *vstr = NULL;
        unsigned int vlen = UINT_MAX;
        long long vll = LLONG_MAX;

        ret = hashTypeGetFromZiplist(o, field, &vstr, &vlen, &vll);
        if (ret < 0) {
            addReplyNull(c);
        } else {
            if (vstr) {
                addReplyBulkCBuffer(c, vstr, vlen);
            } else {
                addReplyBulkLongLong(c, vll);
            }
        }

    } else if (o->encoding == OBJ_ENCODING_HT) {
        sds value = hashTypeGetFromHashTable(o, field);
        if (value == NULL)
            addReplyNull(c);
        else
            addReplyBulkCBuffer(c, value, sdslen(value));
    } else {
        serverPanic("Unknown hash encoding");
    }
}