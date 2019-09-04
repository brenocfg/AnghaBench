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
struct TYPE_10__ {int /*<<< orphan*/  rrsz; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ typeinfo ;
struct timeval {scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_queryflags ;
typedef  TYPE_4__* adns_query ;
struct TYPE_11__ {int id; TYPE_2__* answer; int /*<<< orphan*/  ctx; scalar_t__ expires; int /*<<< orphan*/  timeout; scalar_t__ udpsent; scalar_t__ udpnextserver; scalar_t__ retries; int /*<<< orphan*/  flags; scalar_t__ search_doneabs; scalar_t__ search_pos; scalar_t__ search_origlen; int /*<<< orphan*/  search_vb; scalar_t__ cname_begin; scalar_t__ cname_dglen; scalar_t__ cname_dgram; int /*<<< orphan*/  vb; scalar_t__ query_dglen; scalar_t__ query_dgram; TYPE_3__ const* typei; scalar_t__ final_allocspace; scalar_t__ preserved_allocd; scalar_t__ interim_allocd; int /*<<< orphan*/  allocations; int /*<<< orphan*/  siblings; int /*<<< orphan*/  children; scalar_t__ parent; scalar_t__ next; scalar_t__ back; int /*<<< orphan*/  state; int /*<<< orphan*/  ads; } ;
struct TYPE_8__ {scalar_t__ untyped; } ;
struct TYPE_9__ {int expires; int /*<<< orphan*/  rrsz; TYPE_1__ rrs; scalar_t__ nrrs; int /*<<< orphan*/  type; scalar_t__ owner; scalar_t__ cname; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ MAXTTLBELIEVE ; 
 int /*<<< orphan*/  adns__vbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adns_s_ok ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  query_tosend ; 
 int /*<<< orphan*/  timerclear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static adns_query query_alloc(adns_state ads, const typeinfo *typei,
			      adns_queryflags flags, struct timeval now) {
  /* Allocate a virgin query and return it. */
  adns_query qu;

  qu= malloc(sizeof(*qu));  if (!qu) return 0;
  qu->answer= malloc(sizeof(*qu->answer));  if (!qu->answer) { free(qu); return 0; }

  qu->ads= ads;
  qu->state= query_tosend;
  qu->back= qu->next= qu->parent= 0;
  LIST_INIT(qu->children);
  LINK_INIT(qu->siblings);
  LIST_INIT(qu->allocations);
  qu->interim_allocd= 0;
  qu->preserved_allocd= 0;
  qu->final_allocspace= 0;

  qu->typei= typei;
  qu->query_dgram= 0;
  qu->query_dglen= 0;
  adns__vbuf_init(&qu->vb);

  qu->cname_dgram= 0;
  qu->cname_dglen= qu->cname_begin= 0;

  adns__vbuf_init(&qu->search_vb);
  qu->search_origlen= qu->search_pos= qu->search_doneabs= 0;

  qu->id= -2; /* will be overwritten with real id before we leave adns */
  qu->flags= flags;
  qu->retries= 0;
  qu->udpnextserver= 0;
  qu->udpsent= 0;
  timerclear(&qu->timeout);
  qu->expires= now.tv_sec + MAXTTLBELIEVE;

  memset(&qu->ctx,0,sizeof(qu->ctx));

  qu->answer->status= adns_s_ok;
  qu->answer->cname= qu->answer->owner= 0;
  qu->answer->type= typei->type;
  qu->answer->expires= -1;
  qu->answer->nrrs= 0;
  qu->answer->rrs.untyped= 0;
  qu->answer->rrsz= typei->rrsz;

  return qu;
}