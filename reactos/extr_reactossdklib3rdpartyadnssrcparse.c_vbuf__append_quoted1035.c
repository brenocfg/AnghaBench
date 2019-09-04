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
typedef  int /*<<< orphan*/  vbuf ;
typedef  int const byte ;

/* Variables and functions */
 int /*<<< orphan*/  adns__vbuf_append (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  ctype_domainunquoted (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

int vbuf__append_quoted1035(vbuf *vb, const byte *buf, int len) {
  char qbuf[10];
  int i, ch;

  while (len) {
    qbuf[0]= 0;
    for (i=0; i<len; i++) {
      ch= buf[i];
      if (ch <= ' ' || ch >= 127) {
	sprintf(qbuf,"\\%03o",ch);
	break;
      } else if (!ctype_domainunquoted(ch)) {
	sprintf(qbuf,"\\%c",ch);
	break;
      }
    }
    if (!adns__vbuf_append(vb,buf,i) || !adns__vbuf_append(vb,(byte*)qbuf,(int)  strlen(qbuf)))
      return 0;
    if (i<len) i++;
    buf+= i;
    len-= i;
  }
  return 1;
}