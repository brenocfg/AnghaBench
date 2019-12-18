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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  SFormat ;
typedef  int /*<<< orphan*/  SBuf ;

/* Variables and functions */
 int /*<<< orphan*/  lj_strfmt_wfnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SBuf *lj_strfmt_putfnum(SBuf *sb, SFormat sf, lua_Number n)
{
  setsbufP(sb, lj_strfmt_wfnum(sb, sf, n, NULL));
  return sb;
}