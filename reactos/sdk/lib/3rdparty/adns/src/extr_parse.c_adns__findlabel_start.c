#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int serv; int dglen; int max; int cbyte; int* dmend_r; scalar_t__ namelen; int /*<<< orphan*/  const* dgram; int /*<<< orphan*/  qu; int /*<<< orphan*/  ads; } ;
typedef  TYPE_1__ findlabel_state ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */

void adns__findlabel_start(findlabel_state *fls, adns_state ads,
			   int serv, adns_query qu,
			   const byte *dgram, int dglen, int max,
			   int dmbegin, int *dmend_rlater) {
  fls->ads= ads;
  fls->qu= qu;
  fls->serv= serv;
  fls->dgram= dgram;
  fls->dglen= dglen;
  fls->max= max;
  fls->cbyte= dmbegin;
  fls->namelen= 0;
  fls->dmend_r= dmend_rlater;
}