#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* text; } ;
typedef  TYPE_1__ getline_ctx ;
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  adns__diag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  saveerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcspn (char const*,char*) ; 

__attribute__((used)) static int gl_text(adns_state ads, getline_ctx *src_io, const char *filename,
		   int lno, char *buf, int buflen) {
  const char *cp= src_io->text;
  int l;

  if (!cp || !*cp) return -1;

  if (*cp == ';' || *cp == '\n') cp++;
  l= strcspn(cp,";\n");
  src_io->text = cp+l;

  if (l >= buflen) {
    adns__diag(ads,-1,0,"%s:%d: line too long, ignored",filename,lno);
    saveerr(ads,EINVAL);
    return -2;
  }

  memcpy(buf,cp,l);
  buf[l]= 0;
  return l;
}