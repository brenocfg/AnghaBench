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
struct in_ev {int in_buf_pos; char* in_buf; int error; struct bufferevent* bev; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bufferevent_read (struct bufferevent*,char*,int) ; 
 int /*<<< orphan*/  interpreter_ex (char*,struct in_ev*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  vlogprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void read_incoming (struct bufferevent *bev, void *_arg) {
  vlogprintf (E_WARNING, "Read from incoming connection\n");
  struct in_ev *ev = _arg;
  assert (ev->bev == bev);
  ev->in_buf_pos += bufferevent_read (bev, ev->in_buf + ev->in_buf_pos, 4096 - ev->in_buf_pos);

  while (1) {
    int pos = 0;
    int ok = 0;
    while (pos < ev->in_buf_pos) {
      if (ev->in_buf[pos] == '\n') {
        if (!ev->error) {
          ev->in_buf[pos] = 0;
          interpreter_ex (ev->in_buf, ev);
        } else {
          ev->error = 0;
        }
        ok = 1;
        ev->in_buf_pos -= (pos + 1);
        memmove (ev->in_buf, ev->in_buf + pos + 1, ev->in_buf_pos);
        pos = 0;
      } else {
        pos ++;
      }
    }
    if (ok) {
      ev->in_buf_pos += bufferevent_read (bev, ev->in_buf + ev->in_buf_pos, 4096 - ev->in_buf_pos);
    } else {
      if (ev->in_buf_pos == 4096) {
        ev->error = 1;
      }
      break;
    }
  }
}