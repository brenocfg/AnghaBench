#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _EXCEPTION_POINTERS {TYPE_1__* ExceptionRecord; scalar_t__ ContextRecord; } ;
typedef  int /*<<< orphan*/  argv ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_2__ {scalar_t__ ExceptionCode; scalar_t__ ExceptionFlags; scalar_t__ NumberParameters; int /*<<< orphan*/  ExceptionInformation; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int return_positive () ; 

__attribute__((used)) static
int verify_xpointers(struct _EXCEPTION_POINTERS * ep, DWORD code, DWORD flags, DWORD argc, const ULONG_PTR * argv, int * ret, int filter)
{
	*ret =
		ep &&
		ep->ExceptionRecord &&
		ep->ContextRecord &&
		ep->ExceptionRecord->ExceptionCode == code &&
		ep->ExceptionRecord->ExceptionFlags == flags &&
		ep->ExceptionRecord->NumberParameters == argc &&
		(argv || !argc) &&
		memcmp(ep->ExceptionRecord->ExceptionInformation, argv, sizeof(argv[0]) * argc) == 0;

	if(*ret)
		*ret = return_positive();

	return filter;
}