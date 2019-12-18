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
typedef  int /*<<< orphan*/  LoadState ;
typedef  int /*<<< orphan*/  LUA_SIGNATURE ;
typedef  int /*<<< orphan*/  LUAC_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  LoadVector (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ memcmp (char const*,char*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void checkliteral (LoadState *S, const char *s, const char *msg) {
  char buff[sizeof(LUA_SIGNATURE) + sizeof(LUAC_DATA)]; /* larger than both */
  size_t len = strlen(s);
  LoadVector(S, buff, len);
  if (memcmp(s, buff, len) != 0)
    error(S, msg);
}