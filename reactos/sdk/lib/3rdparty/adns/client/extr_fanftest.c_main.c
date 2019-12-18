#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_query ;
struct TYPE_4__ {char** str; } ;
struct TYPE_5__ {scalar_t__ status; TYPE_1__ rrs; } ;
typedef  TYPE_2__ adns_answer ;

/* Variables and functions */
 int /*<<< orphan*/  aargh (char*) ; 
 int /*<<< orphan*/  adns_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns_if_debug ; 
 scalar_t__ adns_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adns_qf_cname_loose ; 
 int adns_qf_quoteok_cname ; 
 int /*<<< orphan*/  adns_r_ptr ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ adns_submit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ adns_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchr (char*,char) ; 

int main(int argc, char *argv[]) {
  adns_state adns;
  adns_query query;
  adns_answer *answer;

  progname= strrchr(*argv, '/');
  if (progname)
    progname++;
  else
    progname= *argv;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <domain>\n", progname);
    exit(1);
  }

  errno= adns_init(&adns, adns_if_debug, 0);
  if (errno) aargh("adns_init");

  errno= adns_submit(adns, argv[1], adns_r_ptr,
		     adns_qf_quoteok_cname|adns_qf_cname_loose,
		     NULL, &query);
  if (errno) aargh("adns_submit");

  errno= adns_wait(adns, &query, &answer, NULL);
  if (errno) aargh("adns_init");

  printf("%s\n", answer->status == adns_s_ok ? *answer->rrs.str : "dunno");

  adns_finish(adns);

  return 0;
}