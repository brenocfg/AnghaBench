#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct query_node {int dummy; } ;
typedef  scalar_t__ adns_status ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ adns_answer ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ adns_rr_info (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ adns_s_nodata ; 
 scalar_t__ adns_s_nxdomain ; 
 char* adns_strerror (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fmt_inline ; 
 scalar_t__ fmt_simple ; 
 int fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outerr () ; 
 scalar_t__ ov_format ; 
 char* owner_show (struct query_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  print_status (scalar_t__,struct query_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sysfail (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_dnsfail(adns_status st, struct query_node *qun, adns_answer *answer) {
  int r;
  const char *typename, *statusstring;
  adns_status ist;

  if (ov_format == fmt_inline) {
    if (fputs("; failed ",stdout) == EOF) outerr();
    print_status(st,qun,answer);
    return;
  }
  assert(ov_format == fmt_simple);
  if (st == adns_s_nxdomain) {
    r= fprintf(stderr,"%s does not exist\n", owner_show(qun,answer));
  } else {
    ist= adns_rr_info(answer->type, &typename, 0,0,0,0);
    if (st == adns_s_nodata) {
      r= fprintf(stderr,"%s has no %s record\n", owner_show(qun,answer), typename);
    } else {
      statusstring= adns_strerror(st);
      r= fprintf(stderr,"Error during DNS %s lookup for %s: %s\n",
		 typename, owner_show(qun,answer), statusstring);
    }
  }
  if (r == EOF) sysfail("write error message to stderr",errno);
}