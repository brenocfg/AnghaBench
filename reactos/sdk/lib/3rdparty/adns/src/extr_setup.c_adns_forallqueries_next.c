#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_6__* adns_state ;
typedef  TYPE_7__* adns_query ;
struct TYPE_15__ {void* ext; } ;
struct TYPE_17__ {TYPE_5__ ctx; int /*<<< orphan*/  parent; struct TYPE_17__* next; } ;
struct TYPE_14__ {TYPE_7__* head; } ;
struct TYPE_13__ {TYPE_7__* tail; TYPE_7__* head; } ;
struct TYPE_12__ {TYPE_7__* tail; TYPE_7__* head; } ;
struct TYPE_11__ {TYPE_7__* tail; } ;
struct TYPE_16__ {TYPE_7__* forallnext; TYPE_4__ output; TYPE_3__ childw; TYPE_2__ tcpw; TYPE_1__ udpw; } ;

/* Variables and functions */
 int /*<<< orphan*/  adns__consistency (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_entex ; 

adns_query adns_forallqueries_next(adns_state ads, void **context_r) {
  adns_query qu, nqu;

  adns__consistency(ads,0,cc_entex);
  nqu= ads->forallnext;
  for (;;) {
    qu= nqu;
    if (!qu) return 0;
    if (qu->next) {
      nqu= qu->next;
    } else if (qu == ads->udpw.tail) {
      nqu=
	ads->tcpw.head ? ads->tcpw.head :
	ads->childw.head ? ads->childw.head :
	ads->output.head;
    } else if (qu == ads->tcpw.tail) {
      nqu=
	ads->childw.head ? ads->childw.head :
	ads->output.head;
    } else if (qu == ads->childw.tail) {
      nqu= ads->output.head;
    } else {
      nqu= 0;
    }
    if (!qu->parent) break;
  }
  ads->forallnext= nqu;
  if (context_r) *context_r= qu->ctx.ext;
  return qu;
}