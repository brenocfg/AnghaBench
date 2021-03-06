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
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {char* str; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_user_gw ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tgl_do_import_card (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_import_card (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 1);
  char *s = args[0].str;
  int l = strlen (s);
  if (l > 0) {
    int i;
    static int p[10];
    int pp = 0;
    int cur = 0;
    int ok = 1;
    for (i = 0; i < l; i ++) {
      if (s[i] >= '0' && s[i] <= '9') {
        cur = cur * 16 + s[i] - '0';
      } else if (s[i] >= 'a' && s[i] <= 'f') {
        cur = cur * 16 + s[i] - 'a' + 10;
      } else if (s[i] == ':') {
        if (pp >= 9) { 
          ok = 0;
          break;
        }
        p[pp ++] = cur;
        cur = 0;
      }
    }
    if (ok) {
      p[pp ++] = cur;
      if (ev) { ev->refcnt ++; }
      tgl_do_import_card (TLS, pp, p, print_user_gw, ev);
    }
  }
}