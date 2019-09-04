#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int argc; long long duration; void* cname; void* peerid; scalar_t__ id; int /*<<< orphan*/  time; TYPE_3__** argv; } ;
typedef  TYPE_2__ slowlogEntry ;
typedef  void* sds ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ refcount; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ robj ;
struct TYPE_16__ {TYPE_1__* name; } ;
typedef  TYPE_4__ client ;
struct TYPE_17__ {int /*<<< orphan*/  slowlog_entry_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ OBJ_SHARED_REFCOUNT ; 
 scalar_t__ OBJ_STRING ; 
 int SLOWLOG_ENTRY_MAX_ARGC ; 
 unsigned long SLOWLOG_ENTRY_MAX_STRING ; 
 void* createObject (scalar_t__,void*) ; 
 TYPE_3__* dupStringObject (TYPE_3__*) ; 
 int /*<<< orphan*/  getClientPeerId (TYPE_4__*) ; 
 scalar_t__ sdsEncodedObject (TYPE_3__*) ; 
 void* sdscatprintf (void*,char*,unsigned long) ; 
 void* sdsempty () ; 
 unsigned long sdslen (int /*<<< orphan*/ ) ; 
 void* sdsnew (int /*<<< orphan*/ ) ; 
 void* sdsnewlen (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 void* zmalloc (int) ; 

slowlogEntry *slowlogCreateEntry(client *c, robj **argv, int argc, long long duration) {
    slowlogEntry *se = zmalloc(sizeof(*se));
    int j, slargc = argc;

    if (slargc > SLOWLOG_ENTRY_MAX_ARGC) slargc = SLOWLOG_ENTRY_MAX_ARGC;
    se->argc = slargc;
    se->argv = zmalloc(sizeof(robj*)*slargc);
    for (j = 0; j < slargc; j++) {
        /* Logging too many arguments is a useless memory waste, so we stop
         * at SLOWLOG_ENTRY_MAX_ARGC, but use the last argument to specify
         * how many remaining arguments there were in the original command. */
        if (slargc != argc && j == slargc-1) {
            se->argv[j] = createObject(OBJ_STRING,
                sdscatprintf(sdsempty(),"... (%d more arguments)",
                argc-slargc+1));
        } else {
            /* Trim too long strings as well... */
            if (argv[j]->type == OBJ_STRING &&
                sdsEncodedObject(argv[j]) &&
                sdslen(argv[j]->ptr) > SLOWLOG_ENTRY_MAX_STRING)
            {
                sds s = sdsnewlen(argv[j]->ptr, SLOWLOG_ENTRY_MAX_STRING);

                s = sdscatprintf(s,"... (%lu more bytes)",
                    (unsigned long)
                    sdslen(argv[j]->ptr) - SLOWLOG_ENTRY_MAX_STRING);
                se->argv[j] = createObject(OBJ_STRING,s);
            } else if (argv[j]->refcount == OBJ_SHARED_REFCOUNT) {
                se->argv[j] = argv[j];
            } else {
                /* Here we need to dupliacate the string objects composing the
                 * argument vector of the command, because those may otherwise
                 * end shared with string objects stored into keys. Having
                 * shared objects between any part of Redis, and the data
                 * structure holding the data, is a problem: FLUSHALL ASYNC
                 * may release the shared string object and create a race. */
                se->argv[j] = dupStringObject(argv[j]);
            }
        }
    }
    se->time = time(NULL);
    se->duration = duration;
    se->id = server.slowlog_entry_id++;
    se->peerid = sdsnew(getClientPeerId(c));
    se->cname = c->name ? sdsnew(c->name->ptr) : sdsempty();
    return se;
}