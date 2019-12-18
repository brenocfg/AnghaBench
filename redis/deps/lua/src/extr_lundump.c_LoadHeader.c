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

/* Variables and functions */
 int /*<<< orphan*/  IF (int,char*) ; 
 int LUAC_HEADERSIZE ; 
 int /*<<< orphan*/  LoadBlock (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaU_header (char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void LoadHeader(LoadState* S)
{
 char h[LUAC_HEADERSIZE];
 char s[LUAC_HEADERSIZE];
 luaU_header(h);
 LoadBlock(S,s,LUAC_HEADERSIZE);
 IF (memcmp(h,s,LUAC_HEADERSIZE)!=0, "bad header");
}