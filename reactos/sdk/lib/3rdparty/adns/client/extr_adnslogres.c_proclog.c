#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ ** str; } ;
struct TYPE_10__ {scalar_t__ status; struct TYPE_10__* next; TYPE_1__ rrs; scalar_t__ rest; scalar_t__ addr; int /*<<< orphan*/  start; int /*<<< orphan*/  query; } ;
typedef  TYPE_2__ logline ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_initflags ;
typedef  TYPE_2__ adns_answer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EAGAIN ; 
 int EWOULDBLOCK ; 
 int OPT_DEBUG ; 
 int OPT_POLL ; 
 int /*<<< orphan*/  aargh (char*) ; 
 int adns_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adns_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns_if_debug ; 
 scalar_t__ adns_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ adns_init_strcfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ adns_s_ok ; 
 int adns_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int adns_wait_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ config_text ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  guard_null (scalar_t__) ; 
 int /*<<< orphan*/  msg (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 char* progname ; 
 TYPE_2__* readline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static void proclog(FILE *inf, FILE *outf, int maxpending, int opts) {
  int eof, err, len;
  adns_state adns;
  adns_answer *answer;
  logline *head, *tail, *line;
  adns_initflags initflags;

  initflags= (opts & OPT_DEBUG) ? adns_if_debug : 0;
  if (config_text) {
    errno= adns_init_strcfg(&adns, initflags, stderr, config_text);
  } else {
    errno= adns_init(&adns, initflags, 0);
  }
  if (errno) aargh("adns_init");
  head= tail= readline(inf, adns, opts);
  len= 1; eof= 0;
  while (head) {
    while (head) {
      if (opts & OPT_DEBUG)
	msg("%d in queue; checking %.*s", len,
	    head->rest-head->addr, guard_null(head->addr));
      if (eof || len >= maxpending) {
#ifdef HAVE_POLL
	if (opts & OPT_POLL)
	  err= adns_wait_poll(adns, &head->query, &answer, NULL);
	else
#endif
	  err= adns_wait(adns, &head->query, &answer, NULL);
      } else {
	err= adns_check(adns, &head->query, &answer, NULL);
      }
      if ((err == EAGAIN) || (EWOULDBLOCK == err)) break;
      if (err) {
	fprintf(stderr, "%s: adns_wait/check: %s", progname, strerror(err));
	exit(1);
      }
      printline(outf, head->start, head->addr, head->rest,
		answer->status == adns_s_ok ? *answer->rrs.str : NULL);
      line= head; head= head->next;
      free(line);
      free(answer);
      len--;
    }
    if (!eof) {
      line= readline(inf, adns, opts);
      if (line) {
        if (!head) head= line;
        else tail->next= line;
        tail= line; len++;
      } else {
	eof= 1;
      }
    }
  }
  adns_finish(adns);
}