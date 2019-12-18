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
struct configcommandinfo {int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,char const*,int,char*) ;scalar_t__ name; } ;
typedef  int /*<<< orphan*/  linebuf ;
typedef  int /*<<< orphan*/  getline_ctx ;
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 int /*<<< orphan*/  adns__diag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char const*,int,int,char*) ; 
 struct configcommandinfo* configcommandinfos ; 
 scalar_t__ ctype_whitespace (char) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int,char*) ; 

__attribute__((used)) static void readconfiggeneric(adns_state ads, const char *filename,
			      int (*getline)(adns_state ads, getline_ctx*,
					     const char *filename, int lno,
					     char *buf, int buflen),
			      /* Returns >=0 for success, -1 for EOF or error
			       * (error will have been reported), or -2 for
			       * bad line was encountered, try again.
			       */
			      getline_ctx gl_ctx) {
  char linebuf[2000], *p, *q;
  int lno, l, dirl;
  const struct configcommandinfo *ccip;

  for (lno=1;
       (l= getline(ads,&gl_ctx, filename,lno, linebuf,sizeof(linebuf))) != -1;
       lno++) {
    if (l == -2) continue;
    while (l>0 && ctype_whitespace(linebuf[l-1])) l--;
    linebuf[l]= 0;
    p= linebuf;
    while (ctype_whitespace(*p)) p++;
    if (*p == '#' || !*p) continue;
    q= p;
    while (*q && !ctype_whitespace(*q)) q++;
    dirl= q-p;
    for (ccip=configcommandinfos;
	 ccip->name && !((int)strlen(ccip->name)==dirl && !memcmp(ccip->name,p,q-p));
	 ccip++);
    if (!ccip->name) {
      adns__diag(ads,-1,0,"%s:%d: unknown configuration directive `%.*s'",
		 filename,lno,q-p,p);
      continue;
    }
    while (ctype_whitespace(*q)) q++;
    ccip->fn(ads,filename,lno,q);
  }
}