#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t ridx; void* reply; TYPE_1__* fn; TYPE_3__* rstack; } ;
typedef  TYPE_2__ redisReader ;
struct TYPE_16__ {scalar_t__ type; } ;
typedef  TYPE_3__ redisReadTask ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_14__ {void* (* createString ) (TYPE_3__*,char*,int) ;void* (* createBool ) (TYPE_3__*,int) ;void* (* createNil ) (TYPE_3__*) ;void* (* createDouble ) (TYPE_3__*,double,char*,int) ;void* (* createInteger ) (TYPE_3__*,long long) ;} ;

/* Variables and functions */
 double INFINITY ; 
 scalar_t__ REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_PROTOCOL ; 
 int REDIS_OK ; 
 scalar_t__ REDIS_REPLY_BOOL ; 
 scalar_t__ REDIS_REPLY_DOUBLE ; 
 scalar_t__ REDIS_REPLY_INTEGER ; 
 scalar_t__ REDIS_REPLY_NIL ; 
 int /*<<< orphan*/  __redisReaderSetError (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  __redisReaderSetErrorOOM (TYPE_2__*) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  moveToNextTask (TYPE_2__*) ; 
 char* readLine (TYPE_2__*,int*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ string2ll (char*,int,long long*) ; 
 double strtod (char*,char**) ; 
 void* stub1 (TYPE_3__*,long long) ; 
 void* stub2 (TYPE_3__*,double,char*,int) ; 
 void* stub3 (TYPE_3__*) ; 
 void* stub4 (TYPE_3__*,int) ; 
 void* stub5 (TYPE_3__*,char*,int) ; 

__attribute__((used)) static int processLineItem(redisReader *r) {
    redisReadTask *cur = &(r->rstack[r->ridx]);
    void *obj;
    char *p;
    int len;

    if ((p = readLine(r,&len)) != NULL) {
        if (cur->type == REDIS_REPLY_INTEGER) {
            if (r->fn && r->fn->createInteger) {
                long long v;
                if (string2ll(p, len, &v) == REDIS_ERR) {
                    __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
                            "Bad integer value");
                    return REDIS_ERR;
                }
                obj = r->fn->createInteger(cur,v);
            } else {
                obj = (void*)REDIS_REPLY_INTEGER;
            }
        } else if (cur->type == REDIS_REPLY_DOUBLE) {
            if (r->fn && r->fn->createDouble) {
                char buf[326], *eptr;
                double d;

                if ((size_t)len >= sizeof(buf)) {
                    __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
                            "Double value is too large");
                    return REDIS_ERR;
                }

                memcpy(buf,p,len);
                buf[len] = '\0';

                if (strcasecmp(buf,",inf") == 0) {
                    d = INFINITY; /* Positive infinite. */
                } else if (strcasecmp(buf,",-inf") == 0) {
                    d = -INFINITY; /* Nevative infinite. */
                } else {
                    d = strtod((char*)buf,&eptr);
                    if (buf[0] == '\0' || eptr[0] != '\0' || isnan(d)) {
                        __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
                                "Bad double value");
                        return REDIS_ERR;
                    }
                }
                obj = r->fn->createDouble(cur,d,buf,len);
            } else {
                obj = (void*)REDIS_REPLY_DOUBLE;
            }
        } else if (cur->type == REDIS_REPLY_NIL) {
            if (r->fn && r->fn->createNil)
                obj = r->fn->createNil(cur);
            else
                obj = (void*)REDIS_REPLY_NIL;
        } else if (cur->type == REDIS_REPLY_BOOL) {
            int bval = p[0] == 't' || p[0] == 'T';
            if (r->fn && r->fn->createBool)
                obj = r->fn->createBool(cur,bval);
            else
                obj = (void*)REDIS_REPLY_BOOL;
        } else {
            /* Type will be error or status. */
            if (r->fn && r->fn->createString)
                obj = r->fn->createString(cur,p,len);
            else
                obj = (void*)(size_t)(cur->type);
        }

        if (obj == NULL) {
            __redisReaderSetErrorOOM(r);
            return REDIS_ERR;
        }

        /* Set reply if this is the root object. */
        if (r->ridx == 0) r->reply = obj;
        moveToNextTask(r);
        return REDIS_OK;
    }

    return REDIS_ERR;
}