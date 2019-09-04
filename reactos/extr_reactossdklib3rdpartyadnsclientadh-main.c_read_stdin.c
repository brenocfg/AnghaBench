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

/* Variables and functions */
 scalar_t__ EINTR ; 
 int avail ; 
 char* buf ; 
 scalar_t__ errno ; 
 char* memchr (char*,char,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ ov_pipe ; 
 int /*<<< orphan*/  process_optarg (char*,int /*<<< orphan*/ ,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 char* realloc (char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  sysfail (char*,scalar_t__) ; 
 int used ; 

__attribute__((used)) static void read_stdin(void) {
  int anydone, r;
  char *newline, *space;

  anydone= 0;
  while (!anydone || used) {
    while (!(newline= memchr(buf,'\n',used))) {
      if (used == avail) {
	avail += 20; avail <<= 1;
	buf= realloc(buf,avail);
	if (!buf) sysfail("realloc stdin buffer",errno);
      }
      do {
	r= read(0,buf+used,avail-used);
      } while (r < 0 && errno == EINTR);
      if (r == 0) {
	if (used) {
	  /* fake up final newline */
	  buf[used++]= '\n';
	  r= 1;
	} else {
	  ov_pipe= 0;
	  return;
	}
      }
      if (r < 0) sysfail("read stdin",errno);
      used += r;
    }
    *newline++= 0;
    space= strchr(buf,' ');
    if (space) *space++= 0;
    process_optarg(buf,0,space);
    used -= (newline-buf);
    memmove(buf,newline,used);
    anydone= 1;
  }
}