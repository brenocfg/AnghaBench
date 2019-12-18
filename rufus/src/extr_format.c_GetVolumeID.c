#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_3__ {int wDay; int wMonth; int wMilliseconds; int wSecond; int wMinute; int wHour; scalar_t__ wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 

__attribute__((used)) static DWORD GetVolumeID(void)
{
	SYSTEMTIME s;
	DWORD d;
	WORD lo,hi,tmp;

	GetLocalTime(&s);

	lo = s.wDay + (s.wMonth << 8);
	tmp = (s.wMilliseconds/10) + (s.wSecond << 8);
	lo += tmp;

	hi = s.wMinute + (s.wHour << 8);
	hi += s.wYear;

	d = lo + (hi << 16);
	return d;
}