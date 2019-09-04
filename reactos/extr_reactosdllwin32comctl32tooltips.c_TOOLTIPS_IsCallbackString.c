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
typedef  scalar_t__ LPCWSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ LPSTR_TEXTCALLBACKA ; 
 scalar_t__ LPSTR_TEXTCALLBACKW ; 

__attribute__((used)) static inline BOOL TOOLTIPS_IsCallbackString(LPCWSTR str, BOOL isW)
{
    if (isW)
      return str == LPSTR_TEXTCALLBACKW;
    else
      return (LPCSTR)str == LPSTR_TEXTCALLBACKA;
}