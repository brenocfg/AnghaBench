#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_11__ {int /*<<< orphan*/  f; int /*<<< orphan*/  ffid; } ;
struct TYPE_13__ {TYPE_1__ c; } ;
struct TYPE_12__ {int /*<<< orphan*/  firstline; } ;
typedef  int /*<<< orphan*/  SBuf ;
typedef  int MSize ;
typedef  TYPE_2__ GCproto ;
typedef  TYPE_3__ GCfunc ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  debug_frameline (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_putchunkname (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 TYPE_3__* frame_func (int /*<<< orphan*/ *) ; 
 TYPE_2__* funcproto (TYPE_3__*) ; 
 int /*<<< orphan*/  isffunc (TYPE_3__*) ; 
 int /*<<< orphan*/  isluafunc (TYPE_3__*) ; 
 int /*<<< orphan*/  lj_buf_putb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_buf_putmem (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * lj_debug_frame (int /*<<< orphan*/ *,int,int*) ; 
 char* lj_debug_funcname (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  lj_strfmt_putint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_strfmt_putptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sbufB (int /*<<< orphan*/ *) ; 
 int sbuflen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void lj_debug_dumpstack(lua_State *L, SBuf *sb, const char *fmt, int depth)
{
  int level = 0, dir = 1, pathstrip = 1;
  MSize lastlen = 0;
  if (depth < 0) { level = ~depth; depth = dir = -1; }  /* Reverse frames. */
  while (level != depth) {  /* Loop through all frame. */
    int size;
    cTValue *frame = lj_debug_frame(L, level, &size);
    if (frame) {
      cTValue *nextframe = size ? frame+size : NULL;
      GCfunc *fn = frame_func(frame);
      const uint8_t *p = (const uint8_t *)fmt;
      int c;
      while ((c = *p++)) {
	switch (c) {
	case 'p':  /* Preserve full path. */
	  pathstrip = 0;
	  break;
	case 'F': case 'f': {  /* Dump function name. */
	  const char *name;
	  const char *what = lj_debug_funcname(L, frame, &name);
	  if (what) {
	    if (c == 'F' && isluafunc(fn)) {  /* Dump module:name for 'F'. */
	      GCproto *pt = funcproto(fn);
	      if (pt->firstline != ~(BCLine)0) {  /* Not a bytecode builtin. */
		debug_putchunkname(sb, pt, pathstrip);
		lj_buf_putb(sb, ':');
	      }
	    }
	    lj_buf_putmem(sb, name, (MSize)strlen(name));
	    break;
	  }  /* else: can't derive a name, dump module:line. */
	  }
	  /* fallthrough */
	case 'l':  /* Dump module:line. */
	  if (isluafunc(fn)) {
	    GCproto *pt = funcproto(fn);
	    if (debug_putchunkname(sb, pt, pathstrip)) {
	      /* Regular Lua function. */
	      BCLine line = c == 'l' ? debug_frameline(L, fn, nextframe) :
				       pt->firstline;
	      lj_buf_putb(sb, ':');
	      lj_strfmt_putint(sb, line >= 0 ? line : pt->firstline);
	    }
	  } else if (isffunc(fn)) {  /* Dump numbered builtins. */
	    lj_buf_putmem(sb, "[builtin#", 9);
	    lj_strfmt_putint(sb, fn->c.ffid);
	    lj_buf_putb(sb, ']');
	  } else {  /* Dump C function address. */
	    lj_buf_putb(sb, '@');
	    lj_strfmt_putptr(sb, fn->c.f);
	  }
	  break;
	case 'Z':  /* Zap trailing separator. */
	  lastlen = sbuflen(sb);
	  break;
	default:
	  lj_buf_putb(sb, c);
	  break;
	}
      }
    } else if (dir == 1) {
      break;
    } else {
      level -= size;  /* Reverse frame order: quickly skip missing level. */
    }
    level += dir;
  }
  if (lastlen)
    setsbufP(sb, sbufB(sb) + lastlen);  /* Zap trailing separator. */
}