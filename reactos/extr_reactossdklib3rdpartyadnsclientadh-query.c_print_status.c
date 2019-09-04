#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ show_cname; } ;
struct query_node {TYPE_1__ pqfr; } ;
typedef  int adns_status ;
struct TYPE_6__ {char* cname; } ;
typedef  TYPE_2__ adns_answer ;

/* Variables and functions */
 scalar_t__ EOF ; 
 char* adns_errabbrev (int) ; 
 char* adns_errtypeabbrev (int) ; 
 char* adns_strerror (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  outerr () ; 
 int /*<<< orphan*/  print_owner_ttl (struct query_node*,TYPE_2__*) ; 
 int /*<<< orphan*/  print_withspace (char*) ; 
 scalar_t__ printf (char*,char const*,...) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 

__attribute__((used)) static void print_status(adns_status st, struct query_node *qun, adns_answer *answer) {
  const char *statustypeabbrev, *statusabbrev, *statusstring;

  statustypeabbrev= adns_errtypeabbrev(st);
  statusabbrev= adns_errabbrev(st);
  statusstring= adns_strerror(st);
  assert(!strchr(statusstring,'"'));

  if (printf("%s %d %s ", statustypeabbrev, st, statusabbrev)
      == EOF) outerr();
  print_owner_ttl(qun,answer);
  if (qun->pqfr.show_cname)
    print_withspace(answer->cname ? answer->cname : "$");
  if (printf("\"%s\"\n", statusstring) == EOF) outerr();
}