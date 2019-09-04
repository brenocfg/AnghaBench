#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t size; int iscompr; scalar_t__ iskey; int /*<<< orphan*/  data; int /*<<< orphan*/  isnull; } ;
typedef  TYPE_1__ raxNode ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugf (char*,int,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,...) ; 
 void* raxGetData (TYPE_1__*) ; 
 TYPE_1__* raxNewNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** raxNodeLastChildPtr (TYPE_1__*) ; 
 int raxPadding (size_t) ; 
 int /*<<< orphan*/  raxSetData (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  rax_free (TYPE_1__*) ; 
 TYPE_1__* rax_realloc (TYPE_1__*,size_t) ; 

raxNode *raxCompressNode(raxNode *n, unsigned char *s, size_t len, raxNode **child) {
    assert(n->size == 0 && n->iscompr == 0);
    void *data = NULL; /* Initialized only to avoid warnings. */
    size_t newsize;

    debugf("Compress node: %.*s\n", (int)len,s);

    /* Allocate the child to link to this node. */
    *child = raxNewNode(0,0);
    if (*child == NULL) return NULL;

    /* Make space in the parent node. */
    newsize = sizeof(raxNode)+len+raxPadding(len)+sizeof(raxNode*);
    if (n->iskey) {
        data = raxGetData(n); /* To restore it later. */
        if (!n->isnull) newsize += sizeof(void*);
    }
    raxNode *newn = rax_realloc(n,newsize);
    if (newn == NULL) {
        rax_free(*child);
        return NULL;
    }
    n = newn;

    n->iscompr = 1;
    n->size = len;
    memcpy(n->data,s,len);
    if (n->iskey) raxSetData(n,data);
    raxNode **childfield = raxNodeLastChildPtr(n);
    memcpy(childfield,child,sizeof(*child));
    return n;
}