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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  GCproto ;
typedef  int /*<<< orphan*/  BCReg ;
typedef  scalar_t__ BCPos ;

/* Variables and functions */
 char* VARNAMEDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARNAMESTR ; 
 scalar_t__ VARNAME_END ; 
 scalar_t__ VARNAME__MAX ; 
 scalar_t__ lj_buf_ruleb128 (char const**) ; 
 scalar_t__ proto_varinfo (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *debug_varname(const GCproto *pt, BCPos pc, BCReg slot)
{
  const char *p = (const char *)proto_varinfo(pt);
  if (p) {
    BCPos lastpc = 0;
    for (;;) {
      const char *name = p;
      uint32_t vn = *(const uint8_t *)p;
      BCPos startpc, endpc;
      if (vn < VARNAME__MAX) {
	if (vn == VARNAME_END) break;  /* End of varinfo. */
      } else {
	do { p++; } while (*(const uint8_t *)p);  /* Skip over variable name. */
      }
      p++;
      lastpc = startpc = lastpc + lj_buf_ruleb128(&p);
      if (startpc > pc) break;
      endpc = startpc + lj_buf_ruleb128(&p);
      if (pc < endpc && slot-- == 0) {
	if (vn < VARNAME__MAX) {
#define VARNAMESTR(name, str)	str "\0"
	  name = VARNAMEDEF(VARNAMESTR);
#undef VARNAMESTR
	  if (--vn) while (*name++ || --vn) ;
	}
	return name;
      }
    }
  }
  return NULL;
}