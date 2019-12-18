#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ sds ;
typedef  int /*<<< orphan*/  rax ;

/* Variables and functions */
 int USER_COMMAND_BITS_COUNT ; 
 void* raxFind (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * raxNew () ; 
 void* raxNotFound ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 scalar_t__ sdsnew (char const*) ; 
 int /*<<< orphan*/  sdstolower (scalar_t__) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

unsigned long ACLGetCommandID(const char *cmdname) {
    static rax *map = NULL;
    static unsigned long nextid = 0;

    sds lowername = sdsnew(cmdname);
    sdstolower(lowername);
    if (map == NULL) map = raxNew();
    void *id = raxFind(map,(unsigned char*)lowername,sdslen(lowername));
    if (id != raxNotFound) {
        sdsfree(lowername);
        return (unsigned long)id;
    }
    raxInsert(map,(unsigned char*)lowername,strlen(lowername),
              (void*)nextid,NULL);
    sdsfree(lowername);
    unsigned long thisid = nextid;
    nextid++;

    /* We never assign the last bit in the user commands bitmap structure,
     * this way we can later check if this bit is set, understanding if the
     * current ACL for the user was created starting with a +@all to add all
     * the possible commands and just subtracting other single commands or
     * categories, or if, instead, the ACL was created just adding commands
     * and command categories from scratch, not allowing future commands by
     * default (loaded via modules). This is useful when rewriting the ACLs
     * with ACL SAVE. */
    if (nextid == USER_COMMAND_BITS_COUNT-1) nextid++;
    return thisid;
}