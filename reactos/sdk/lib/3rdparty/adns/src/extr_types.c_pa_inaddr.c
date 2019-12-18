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
struct in_addr {int dummy; } ;
struct TYPE_3__ {scalar_t__ dgram; } ;
typedef  TYPE_1__ parseinfo ;
typedef  int /*<<< orphan*/  adns_status ;

/* Variables and functions */
 int /*<<< orphan*/  adns_s_invaliddata ; 
 int /*<<< orphan*/  adns_s_ok ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,scalar_t__,int) ; 

__attribute__((used)) static adns_status pa_inaddr(const parseinfo *pai, int cbyte, int max, void *datap) {
  struct in_addr *storeto= datap;

  if (max-cbyte != 4) return adns_s_invaliddata;
  memcpy(storeto, pai->dgram + cbyte, 4);
  return adns_s_ok;
}