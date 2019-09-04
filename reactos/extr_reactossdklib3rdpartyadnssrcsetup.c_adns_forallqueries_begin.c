#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* adns_state ;
struct TYPE_11__ {scalar_t__ head; } ;
struct TYPE_10__ {scalar_t__ head; } ;
struct TYPE_9__ {scalar_t__ head; } ;
struct TYPE_8__ {scalar_t__ head; } ;
struct TYPE_12__ {TYPE_4__ output; TYPE_3__ childw; TYPE_2__ tcpw; TYPE_1__ udpw; scalar_t__ forallnext; } ;

/* Variables and functions */
 int /*<<< orphan*/  adns__consistency (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_entex ; 

void adns_forallqueries_begin(adns_state ads) {
  adns__consistency(ads,0,cc_entex);
  ads->forallnext=
    ads->udpw.head ? ads->udpw.head :
    ads->tcpw.head ? ads->tcpw.head :
    ads->childw.head ? ads->childw.head :
    ads->output.head;
}