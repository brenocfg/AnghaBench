#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * dgram; } ;
typedef  TYPE_2__ parseinfo ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  adns_status ;
struct TYPE_6__ {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_9__ {TYPE_1__ inet; } ;
struct TYPE_8__ {int len; TYPE_5__ addr; } ;
typedef  TYPE_3__ adns_rr_addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  adns_s_invaliddata ; 
 int /*<<< orphan*/  adns_s_ok ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static adns_status pa_addr(const parseinfo *pai, int cbyte, int max, void *datap) {
  adns_rr_addr *storeto= datap;
  const byte *dgram= pai->dgram;

  if (max-cbyte != 4) return adns_s_invaliddata;
  storeto->len= sizeof(storeto->addr.inet);
  memset(&storeto->addr,0,sizeof(storeto->addr.inet));
  storeto->addr.inet.sin_family= AF_INET;
  memcpy(&storeto->addr.inet.sin_addr,dgram+cbyte,4);
  return adns_s_ok;
}