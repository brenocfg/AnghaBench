#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ptrdiff_t ;
struct TYPE_5__ {int level; int src_init; TYPE_1__* capture; int /*<<< orphan*/  L; } ;
struct TYPE_4__ {char const* init; scalar_t__ len; } ;
typedef  TYPE_2__ MatchState ;

/* Variables and functions */
 scalar_t__ CAP_POSITION ; 
 scalar_t__ CAP_UNFINISHED ; 
 int /*<<< orphan*/  LJ_ERR_STRCAPI ; 
 int /*<<< orphan*/  LJ_ERR_STRCAPU ; 
 int /*<<< orphan*/  lj_err_caller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static void push_onecapture(MatchState *ms, int i, const char *s, const char *e)
{
  if (i >= ms->level) {
    if (i == 0)  /* ms->level == 0, too */
      lua_pushlstring(ms->L, s, (size_t)(e - s));  /* add whole match */
    else
      lj_err_caller(ms->L, LJ_ERR_STRCAPI);
  } else {
    ptrdiff_t l = ms->capture[i].len;
    if (l == CAP_UNFINISHED) lj_err_caller(ms->L, LJ_ERR_STRCAPU);
    if (l == CAP_POSITION)
      lua_pushinteger(ms->L, ms->capture[i].init - ms->src_init + 1);
    else
      lua_pushlstring(ms->L, ms->capture[i].init, (size_t)l);
  }
}