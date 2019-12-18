#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int byte ;
struct TYPE_30__ {char const* s; int ptop; TYPE_4__* ocap; int /*<<< orphan*/ * L; } ;
struct TYPE_29__ {char const* s; int siz; int /*<<< orphan*/  kind; int /*<<< orphan*/  idx; } ;
struct TYPE_26__ {int aux; int /*<<< orphan*/  key; int /*<<< orphan*/  code; } ;
struct TYPE_28__ {TYPE_1__ i; int /*<<< orphan*/  buff; } ;
struct TYPE_27__ {char const* s; int caplevel; TYPE_3__ const* p; } ;
typedef  TYPE_2__ Stack ;
typedef  int /*<<< orphan*/  Opcode ;
typedef  TYPE_3__ const Instruction ;
typedef  TYPE_4__ Capture ;
typedef  TYPE_5__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  CHARSETINSTSIZE ; 
 int /*<<< orphan*/  Cclose ; 
#define  IAny 150 
#define  IBackCommit 149 
#define  IBehind 148 
#define  ICall 147 
#define  IChar 146 
#define  IChoice 145 
#define  ICloseCapture 144 
#define  ICloseRunTime 143 
#define  ICommit 142 
#define  IEnd 141 
#define  IFail 140 
#define  IFailTwice 139 
#define  IFullCapture 138 
#define  IGiveup 137 
#define  IJmp 136 
 int INITBACK ; 
 int INITCAPSIZE ; 
#define  IOpenCapture 135 
#define  IPartialCommit 134 
#define  IRet 133 
#define  ISet 132 
#define  ISpan 131 
#define  ITestAny 130 
#define  ITestChar 129 
#define  ITestSet 128 
 int SHRT_MAX ; 
 char const* UCHAR_MAX ; 
 int /*<<< orphan*/  adddyncaptures (char const*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* doublecap (int /*<<< orphan*/ *,TYPE_4__*,int,int,int) ; 
 TYPE_2__* doublestack (int /*<<< orphan*/ *,TYPE_2__**,int) ; 
 int /*<<< orphan*/  getkind (TYPE_3__ const*) ; 
 int /*<<< orphan*/  getoff (TYPE_3__ const*) ; 
 int /*<<< orphan*/  getoffset (TYPE_3__ const*) ; 
 TYPE_2__* getstackbase (int /*<<< orphan*/ *,int) ; 
 TYPE_3__ const giveup ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  printcaplist (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printinst (TYPE_3__ const*,TYPE_3__ const*) ; 
 int removedyncap (int /*<<< orphan*/ *,TYPE_4__*,int,int) ; 
 int resdyncaptures (int /*<<< orphan*/ *,int,int,int) ; 
 int runtimecap (TYPE_5__*,TYPE_4__*,char const*,int*) ; 
 scalar_t__ stackidx (int) ; 
 int /*<<< orphan*/  testchar (int /*<<< orphan*/ ,int) ; 

const char *match (lua_State *L, const char *o, const char *s, const char *e,
                   Instruction *op, Capture *capture, int ptop) {
  Stack stackbase[INITBACK];
  Stack *stacklimit = stackbase + INITBACK;
  Stack *stack = stackbase;  /* point to first empty slot in stack */
  int capsize = INITCAPSIZE;
  int captop = 0;  /* point to first empty slot in captures */
  int ndyncap = 0;  /* number of dynamic captures (in Lua stack) */
  const Instruction *p = op;  /* current instruction */
  stack->p = &giveup; stack->s = s; stack->caplevel = 0; stack++;
  lua_pushlightuserdata(L, stackbase);
  for (;;) {
#if defined(DEBUG)
      printf("-------------------------------------\n");
      printcaplist(capture, capture + captop);
      printf("s: |%s| stck:%d, dyncaps:%d, caps:%d  ",
             s, (int)(stack - getstackbase(L, ptop)), ndyncap, captop);
      printinst(op, p);
#endif
    assert(stackidx(ptop) + ndyncap == lua_gettop(L) && ndyncap <= captop);
    switch ((Opcode)p->i.code) {
      case IEnd: {
        assert(stack == getstackbase(L, ptop) + 1);
        capture[captop].kind = Cclose;
        capture[captop].s = NULL;
        return s;
      }
      case IGiveup: {
        assert(stack == getstackbase(L, ptop));
        return NULL;
      }
      case IRet: {
        assert(stack > getstackbase(L, ptop) && (stack - 1)->s == NULL);
        p = (--stack)->p;
        continue;
      }
      case IAny: {
        if (s < e) { p++; s++; }
        else goto fail;
        continue;
      }
      case ITestAny: {
        if (s < e) p += 2;
        else p += getoffset(p);
        continue;
      }
      case IChar: {
        if ((byte)*s == p->i.aux && s < e) { p++; s++; }
        else goto fail;
        continue;
      }
      case ITestChar: {
        if ((byte)*s == p->i.aux && s < e) p += 2;
        else p += getoffset(p);
        continue;
      }
      case ISet: {
        int c = (byte)*s;
        if (testchar((p+1)->buff, c) && s < e)
          { p += CHARSETINSTSIZE; s++; }
        else goto fail;
        continue;
      }
      case ITestSet: {
        int c = (byte)*s;
        if (testchar((p + 2)->buff, c) && s < e)
          p += 1 + CHARSETINSTSIZE;
        else p += getoffset(p);
        continue;
      }
      case IBehind: {
        int n = p->i.aux;
        if (n > s - o) goto fail;
        s -= n; p++;
        continue;
      }
      case ISpan: {
        for (; s < e; s++) {
          int c = (byte)*s;
          if (!testchar((p+1)->buff, c)) break;
        }
        p += CHARSETINSTSIZE;
        continue;
      }
      case IJmp: {
        p += getoffset(p);
        continue;
      }
      case IChoice: {
        if (stack == stacklimit)
          stack = doublestack(L, &stacklimit, ptop);
        stack->p = p + getoffset(p);
        stack->s = s;
        stack->caplevel = captop;
        stack++;
        p += 2;
        continue;
      }
      case ICall: {
        if (stack == stacklimit)
          stack = doublestack(L, &stacklimit, ptop);
        stack->s = NULL;
        stack->p = p + 2;  /* save return address */
        stack++;
        p += getoffset(p);
        continue;
      }
      case ICommit: {
        assert(stack > getstackbase(L, ptop) && (stack - 1)->s != NULL);
        stack--;
        p += getoffset(p);
        continue;
      }
      case IPartialCommit: {
        assert(stack > getstackbase(L, ptop) && (stack - 1)->s != NULL);
        (stack - 1)->s = s;
        (stack - 1)->caplevel = captop;
        p += getoffset(p);
        continue;
      }
      case IBackCommit: {
        assert(stack > getstackbase(L, ptop) && (stack - 1)->s != NULL);
        s = (--stack)->s;
        captop = stack->caplevel;
        p += getoffset(p);
        continue;
      }
      case IFailTwice:
        assert(stack > getstackbase(L, ptop));
        stack--;
        /* go through */
      case IFail:
      fail: { /* pattern failed: try to backtrack */
        do {  /* remove pending calls */
          assert(stack > getstackbase(L, ptop));
          s = (--stack)->s;
        } while (s == NULL);
        if (ndyncap > 0)  /* is there matchtime captures? */
          ndyncap -= removedyncap(L, capture, stack->caplevel, captop);
        captop = stack->caplevel;
        p = stack->p;
#if defined(DEBUG)
        printf("**FAIL**\n");
#endif
        continue;
      }
      case ICloseRunTime: {
        CapState cs;
        int rem, res, n;
        int fr = lua_gettop(L) + 1;  /* stack index of first result */
        cs.s = o; cs.L = L; cs.ocap = capture; cs.ptop = ptop;
        n = runtimecap(&cs, capture + captop, s, &rem);  /* call function */
        captop -= n;  /* remove nested captures */
        ndyncap -= rem;  /* update number of dynamic captures */
        fr -= rem;  /* 'rem' items were popped from Lua stack */
        res = resdyncaptures(L, fr, s - o, e - o);  /* get result */
        if (res == -1)  /* fail? */
          goto fail;
        s = o + res;  /* else update current position */
        n = lua_gettop(L) - fr + 1;  /* number of new captures */
        ndyncap += n;  /* update number of dynamic captures */
        if (n > 0) {  /* any new capture? */
          if (fr + n >= SHRT_MAX)
            luaL_error(L, "too many results in match-time capture");
          if ((captop += n + 2) >= capsize) {
            capture = doublecap(L, capture, captop, n + 2, ptop);
            capsize = 2 * captop;
          }
          /* add new captures to 'capture' list */
          adddyncaptures(s, capture + captop - n - 2, n, fr); 
        }
        p++;
        continue;
      }
      case ICloseCapture: {
        const char *s1 = s;
        assert(captop > 0);
        /* if possible, turn capture into a full capture */
        if (capture[captop - 1].siz == 0 &&
            s1 - capture[captop - 1].s < UCHAR_MAX) {
          capture[captop - 1].siz = s1 - capture[captop - 1].s + 1;
          p++;
          continue;
        }
        else {
          capture[captop].siz = 1;  /* mark entry as closed */
          capture[captop].s = s;
          goto pushcapture;
        }
      }
      case IOpenCapture:
        capture[captop].siz = 0;  /* mark entry as open */
        capture[captop].s = s;
        goto pushcapture;
      case IFullCapture:
        capture[captop].siz = getoff(p) + 1;  /* save capture size */
        capture[captop].s = s - getoff(p);
        /* goto pushcapture; */
      pushcapture: {
        capture[captop].idx = p->i.key;
        capture[captop].kind = getkind(p);
        if (++captop >= capsize) {
          capture = doublecap(L, capture, captop, 0, ptop);
          capsize = 2 * captop;
        }
        p++;
        continue;
      }
      default: assert(0); return NULL;
    }
  }
}