#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  streamID ;
struct TYPE_7__ {int /*<<< orphan*/  last_id; void* consumers; void* pel; } ;
typedef  TYPE_1__ streamCG ;
struct TYPE_8__ {int /*<<< orphan*/ * cgroups; } ;
typedef  TYPE_2__ stream ;

/* Variables and functions */
 scalar_t__ raxFind (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ *,unsigned char*,size_t,TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* raxNew () ; 
 scalar_t__ raxNotFound ; 
 TYPE_1__* zmalloc (int) ; 

streamCG *streamCreateCG(stream *s, char *name, size_t namelen, streamID *id) {
    if (s->cgroups == NULL) s->cgroups = raxNew();
    if (raxFind(s->cgroups,(unsigned char*)name,namelen) != raxNotFound)
        return NULL;

    streamCG *cg = zmalloc(sizeof(*cg));
    cg->pel = raxNew();
    cg->consumers = raxNew();
    cg->last_id = *id;
    raxInsert(s->cgroups,(unsigned char*)name,namelen,cg,NULL);
    return cg;
}