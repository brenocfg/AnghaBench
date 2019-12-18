#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_8__ {char* s; int siz; } ;
struct TYPE_7__ {TYPE_3__* cap; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 scalar_t__ addonestring (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 char* closeaddr (TYPE_3__*) ; 
 int /*<<< orphan*/  isclosecap (TYPE_3__*) ; 
 scalar_t__ isfullcap (TYPE_3__*) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void substcap (luaL_Buffer *b, CapState *cs) {
  const char *curr = cs->cap->s;
  if (isfullcap(cs->cap))  /* no nested captures? */
    luaL_addlstring(b, curr, cs->cap->siz - 1);  /* keep original text */
  else {
    cs->cap++;  /* skip open entry */
    while (!isclosecap(cs->cap)) {  /* traverse nested captures */
      const char *next = cs->cap->s;
      luaL_addlstring(b, curr, next - curr);  /* add text up to capture */
      if (addonestring(b, cs, "replacement"))
        curr = closeaddr(cs->cap - 1);  /* continue after match */
      else  /* no capture value */
        curr = next;  /* keep original text in final result */
    }
    luaL_addlstring(b, curr, cs->cap->s - curr);  /* add last piece of text */
  }
  cs->cap++;  /* go to next capture */
}