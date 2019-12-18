#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  last_id; } ;
typedef  TYPE_2__ streamCG ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_9__ {TYPE_1__* db; } ;
typedef  TYPE_3__ client ;
struct TYPE_10__ {int /*<<< orphan*/  xgroupCommand; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int /*<<< orphan*/ * createObjectFromStreamID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * createStringObject (char*,int) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  propagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ; 
 TYPE_6__ server ; 

void streamPropagateGroupID(client *c, robj *key, streamCG *group, robj *groupname) {
    robj *argv[5];
    argv[0] = createStringObject("XGROUP",6);
    argv[1] = createStringObject("SETID",5);
    argv[2] = key;
    argv[3] = groupname;
    argv[4] = createObjectFromStreamID(&group->last_id);
    propagate(server.xgroupCommand,c->db->id,argv,5,PROPAGATE_AOF|PROPAGATE_REPL);
    decrRefCount(argv[0]);
    decrRefCount(argv[1]);
    decrRefCount(argv[4]);
}