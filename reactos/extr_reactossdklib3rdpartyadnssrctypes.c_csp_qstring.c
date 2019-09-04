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
typedef  int /*<<< orphan*/  adns_status ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_ADDSTR (char*) ; 
 int /*<<< orphan*/  R_NOMEM ; 
 int /*<<< orphan*/  adns__vbuf_append (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  adns_s_ok ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

__attribute__((used)) static adns_status csp_qstring(vbuf *vb, const char *dp, int len) {
  unsigned char ch;
  char buf[10];
  int cn;

  CSP_ADDSTR("\"");
  for (cn=0; cn<len; cn++) {
    ch= *dp++;
    if (ch == '\\') {
      CSP_ADDSTR("\\\\");
    } else if (ch == '"') {
      CSP_ADDSTR("\\\"");
    } else if (ch >= 32 && ch <= 126) {
      if (!adns__vbuf_append(vb,&ch,1)) R_NOMEM;
    } else {
      sprintf(buf,"\\x%02x",ch);
      CSP_ADDSTR(buf);
    }
  }
  CSP_ADDSTR("\"");

  return adns_s_ok;
}