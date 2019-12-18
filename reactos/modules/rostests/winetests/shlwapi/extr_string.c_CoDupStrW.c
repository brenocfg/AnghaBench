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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/ * CoTaskMemAlloc (int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static WCHAR *CoDupStrW(const char* src)
{
  INT len = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
  WCHAR* szTemp = CoTaskMemAlloc(len * sizeof(WCHAR));
  MultiByteToWideChar(CP_ACP, 0, src, -1, szTemp, len);
  return szTemp;
}