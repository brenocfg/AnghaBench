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
struct in_ev {int dummy; } ;
struct command {int dummy; } ;
struct arg {int /*<<< orphan*/  peer_id; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  COLOR_BLUE 131 
#define  COLOR_CYAN 130 
#define  COLOR_GREEN 129 
#define  COLOR_GREY 128 
 char* COLOR_INVERSE ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disable_colors ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,char*) ; 
 int /*<<< orphan*/  tgl_do_visualize_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 

void do_visualize_key (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 1);
  static char *colors[4] = {COLOR_GREY, COLOR_CYAN, COLOR_BLUE, COLOR_GREEN};
  static unsigned char buf[16];
  memset (buf, 0, sizeof (buf));
  tgl_do_visualize_key (TLS, args[0].peer_id, buf);
  mprint_start (ev);
  int i;
  for (i = 0; i < 16; i++) {
    int x = buf[i];
    int j;
    for (j = 0; j < 4; j ++) {    
      if (!ev) {
        mpush_color (ev, colors[x & 3]);
        mpush_color (ev, COLOR_INVERSE);
      }
      if (!disable_colors && !ev) {
        mprintf (ev, "  ");
      } else {
        switch (x & 3) {
        case 0:
          mprintf (ev, "  ");
          break;
        case 1:
          mprintf (ev, "--");
          break;
        case 2:
          mprintf (ev, "==");
          break;
        case 3:
          mprintf (ev, "||");
          break;
        }
      }
      if (!ev) {
        mpop_color (ev);
        mpop_color (ev);
      }
      x = x >> 2;
    }
    if (i & 1) { 
      mprintf (ev, "\n"); 
    }
  }
  mprint_end (ev);
}