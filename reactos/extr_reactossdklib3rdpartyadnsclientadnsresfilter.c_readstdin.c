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
typedef  int /*<<< orphan*/  readbuf ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int* addrtextbuf ; 
 scalar_t__ bracket ; 
 int* bytes ; 
 int cbyte ; 
 int /*<<< orphan*/  inbuf ; 
 int inbyte ; 
 int inputeof ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  procaddr () ; 
 int /*<<< orphan*/  queueoutchar (int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  restartbuf () ; 
 int /*<<< orphan*/  startaddr () ; 
 int /*<<< orphan*/  sysfail (char*) ; 

__attribute__((used)) static void readstdin(void) {
  char readbuf[512], *p;
  int r, c, nbyte;

  while ((r= read(0,readbuf,sizeof(readbuf))) <= 0) {
    if (r == 0) { inputeof= 1; return; }
    if (r == EAGAIN) return;
    if (r != EINTR) sysfail("read stdin");
  }
  for (p=readbuf; r>0; r--,p++) {
    c= *p;
    if (cbyte==-1 && bracket && c=='[') {
      addrtextbuf[inbuf++]= c;
      startaddr();
    } else if (cbyte==-1 && !bracket && !isalnum(c)) {
      queueoutchar(c);
      startaddr();
    } else if (cbyte>=0 && inbyte<3 && c>='0' && c<='9' &&
	       (nbyte= bytes[cbyte]*10 + (c-'0')) <= 255) {
      bytes[cbyte]= nbyte;
      addrtextbuf[inbuf++]= c;
      inbyte++;
    } else if (cbyte>=0 && cbyte<3 && inbyte>0 && c=='.') {
      bytes[++cbyte]= 0;
      addrtextbuf[inbuf++]= c;
      inbyte= 0;
    } else if (cbyte==3 && inbyte>0 && bracket && c==']') {
      addrtextbuf[inbuf++]= c;
      procaddr();
    } else if (cbyte==3 && inbyte>0 && !bracket && !isalnum(c)) {
      procaddr();
      queueoutchar(c);
      startaddr();
    } else {
      restartbuf();
      queueoutchar(c);
      cbyte= -1;
      if (!bracket && !isalnum(c)) startaddr();
    }
  }
}