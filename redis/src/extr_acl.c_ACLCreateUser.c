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
struct TYPE_5__ {int /*<<< orphan*/  allowed_commands; void* patterns; void* passwords; int /*<<< orphan*/ * allowed_subcommands; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  ACLListDupSds ; 
 int /*<<< orphan*/  ACLListFreeSds ; 
 int /*<<< orphan*/  ACLListMatchSds ; 
 int /*<<< orphan*/  USER_FLAG_DISABLED ; 
 int /*<<< orphan*/  Users ; 
 void* listCreate () ; 
 int /*<<< orphan*/  listSetDupMethod (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listSetFreeMethod (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listSetMatchMethod (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ raxFind (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,size_t,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ raxNotFound ; 
 int /*<<< orphan*/  sdsnewlen (char const*,size_t) ; 
 TYPE_1__* zmalloc (int) ; 

user *ACLCreateUser(const char *name, size_t namelen) {
    if (raxFind(Users,(unsigned char*)name,namelen) != raxNotFound) return NULL;
    user *u = zmalloc(sizeof(*u));
    u->name = sdsnewlen(name,namelen);
    u->flags = USER_FLAG_DISABLED;
    u->allowed_subcommands = NULL;
    u->passwords = listCreate();
    u->patterns = listCreate();
    listSetMatchMethod(u->passwords,ACLListMatchSds);
    listSetFreeMethod(u->passwords,ACLListFreeSds);
    listSetDupMethod(u->passwords,ACLListDupSds);
    listSetMatchMethod(u->patterns,ACLListMatchSds);
    listSetFreeMethod(u->patterns,ACLListFreeSds);
    listSetDupMethod(u->patterns,ACLListDupSds);
    memset(u->allowed_commands,0,sizeof(u->allowed_commands));
    raxInsert(Users,(unsigned char*)name,namelen,u,NULL);
    return u;
}