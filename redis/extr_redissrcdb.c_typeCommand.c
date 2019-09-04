#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; TYPE_3__* ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_10__ {TYPE_1__* type; } ;
typedef  TYPE_3__ moduleValue ;
struct TYPE_11__ {int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_4__ client ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOOKUP_NOTOUCH ; 
#define  OBJ_HASH 134 
#define  OBJ_LIST 133 
#define  OBJ_MODULE 132 
#define  OBJ_SET 131 
#define  OBJ_STREAM 130 
#define  OBJ_STRING 129 
#define  OBJ_ZSET 128 
 int /*<<< orphan*/  addReplyStatus (TYPE_4__*,char*) ; 
 TYPE_2__* lookupKeyReadWithFlags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void typeCommand(client *c) {
    robj *o;
    char *type;

    o = lookupKeyReadWithFlags(c->db,c->argv[1],LOOKUP_NOTOUCH);
    if (o == NULL) {
        type = "none";
    } else {
        switch(o->type) {
        case OBJ_STRING: type = "string"; break;
        case OBJ_LIST: type = "list"; break;
        case OBJ_SET: type = "set"; break;
        case OBJ_ZSET: type = "zset"; break;
        case OBJ_HASH: type = "hash"; break;
        case OBJ_STREAM: type = "stream"; break;
        case OBJ_MODULE: {
            moduleValue *mv = o->ptr;
            type = mv->type->name;
        }; break;
        default: type = "unknown"; break;
        }
    }
    addReplyStatus(c,type);
}