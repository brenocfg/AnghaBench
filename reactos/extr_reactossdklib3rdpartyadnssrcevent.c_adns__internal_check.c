#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* adns_state ;
typedef  TYPE_5__* adns_query ;
typedef  int /*<<< orphan*/  adns_answer ;
struct TYPE_16__ {TYPE_5__* head; } ;
struct TYPE_13__ {void* ext; } ;
struct TYPE_15__ {scalar_t__ id; TYPE_3__ ctx; int /*<<< orphan*/ * answer; } ;
struct TYPE_12__ {scalar_t__ head; } ;
struct TYPE_11__ {scalar_t__ head; } ;
struct TYPE_14__ {TYPE_9__ output; TYPE_2__ tcpw; TYPE_1__ udpw; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ESRCH ; 
 int /*<<< orphan*/  LIST_UNLINK (TYPE_9__,TYPE_5__*) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 

int adns__internal_check(adns_state ads,
			 adns_query *query_io,
			 adns_answer **answer,
			 void **context_r) {
  adns_query qu;

  qu= *query_io;
  if (!qu) {
    if (ads->output.head) {
      qu= ads->output.head;
    } else if (ads->udpw.head || ads->tcpw.head) {
      return EAGAIN;
    } else {
      return ESRCH;
    }
  } else {
    if (qu->id>=0) return EAGAIN;
  }
  LIST_UNLINK(ads->output,qu);
  *answer= qu->answer;
  if (context_r) *context_r= qu->ctx.ext;
  *query_io= qu;
  free(qu);
  return 0;
}