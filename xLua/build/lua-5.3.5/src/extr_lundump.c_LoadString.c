#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 size_t LUAI_MAXSHORTLEN ; 
 void* LoadByte (TYPE_1__*) ; 
 int /*<<< orphan*/  LoadVar (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  LoadVector (TYPE_1__*,char*,size_t) ; 
 char* getstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaS_createlngstrobj (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * luaS_newlstr (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static TString *LoadString (LoadState *S) {
#if LUAC_COMPATIBLE_FORMAT
  uint32_t size = LoadByte(S);
#else
  size_t size = LoadByte(S);
#endif
  if (size == 0xFF)
    LoadVar(S, size);
  if (size == 0)
    return NULL;
  else if (--size <= LUAI_MAXSHORTLEN) {  /* short string? */
    char buff[LUAI_MAXSHORTLEN];
    LoadVector(S, buff, size);
    return luaS_newlstr(S->L, buff, size);
  }
  else {  /* long string */
    TString *ts = luaS_createlngstrobj(S->L, size);
    LoadVector(S, getstr(ts), size);  /* load directly in final place */
    return ts;
  }
}