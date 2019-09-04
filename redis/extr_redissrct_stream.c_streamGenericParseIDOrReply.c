#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_5__ {unsigned long long ms; unsigned long long seq; } ;
typedef  TYPE_1__ streamID ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ robj ;
typedef  int /*<<< orphan*/  client ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 void* UINT64_MAX ; 
 int /*<<< orphan*/  addReplyError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int sdslen (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ string2ull (char*,unsigned long long*) ; 

int streamGenericParseIDOrReply(client *c, robj *o, streamID *id, uint64_t missing_seq, int strict) {
    char buf[128];
    if (sdslen(o->ptr) > sizeof(buf)-1) goto invalid;
    memcpy(buf,o->ptr,sdslen(o->ptr)+1);

    if (strict && (buf[0] == '-' || buf[0] == '+') && buf[1] == '\0')
        goto invalid;

    /* Handle the "-" and "+" special cases. */
    if (buf[0] == '-' && buf[1] == '\0') {
        id->ms = 0;
        id->seq = 0;
        return C_OK;
    } else if (buf[0] == '+' && buf[1] == '\0') {
        id->ms = UINT64_MAX;
        id->seq = UINT64_MAX;
        return C_OK;
    }

    /* Parse <ms>-<seq> form. */
    char *dot = strchr(buf,'-');
    if (dot) *dot = '\0';
    unsigned long long ms, seq;
    if (string2ull(buf,&ms) == 0) goto invalid;
    if (dot && string2ull(dot+1,&seq) == 0) goto invalid;
    if (!dot) seq = missing_seq;
    id->ms = ms;
    id->seq = seq;
    return C_OK;

invalid:
    if (c) addReplyError(c,"Invalid stream ID specified as stream "
                           "command argument");
    return C_ERR;
}