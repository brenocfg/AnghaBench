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
typedef  int /*<<< orphan*/  statuspoints ;
typedef  scalar_t__ const adns_status ;

/* Variables and functions */
#define  adns_s_max_localfail 133 
#define  adns_s_max_misconfig 132 
#define  adns_s_max_misquery 131 
#define  adns_s_max_remotefail 130 
#define  adns_s_max_tempfail 129 
#define  adns_s_ok 128 
 int rcode ; 

__attribute__((used)) static void check_status(adns_status st) {
  static const adns_status statuspoints[]= {
    adns_s_ok,
    adns_s_max_localfail, adns_s_max_remotefail, adns_s_max_tempfail,
    adns_s_max_misconfig, adns_s_max_misquery
  };

  const adns_status *spp;
  int minrcode;

  for (minrcode=0, spp=statuspoints;
       spp < statuspoints + (sizeof(statuspoints)/sizeof(statuspoints[0]));
       spp++)
    if (st > *spp) minrcode++;
  if (rcode < minrcode) rcode= minrcode;
}