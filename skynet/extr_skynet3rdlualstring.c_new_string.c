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
typedef  int /*<<< orphan*/  lu_byte ;
struct TYPE_6__ {unsigned int hash; int /*<<< orphan*/  shrlen; int /*<<< orphan*/  tt; } ;
typedef  TYPE_1__ TString ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TSHRSTR ; 
 TYPE_1__* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 size_t sizelstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TString *
new_string(unsigned int h, const char *str, lu_byte l) {
	size_t sz = sizelstring(l);
	TString *ts = malloc(sz);
	memset(ts, 0, sz);
	ts->tt = LUA_TSHRSTR;
	ts->hash = h;
	ts->shrlen = l;
	memcpy(ts+1, str, l);
	return ts;
}