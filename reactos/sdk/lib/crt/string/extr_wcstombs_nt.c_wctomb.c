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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlUnicodeToMultiByteN (char*,int,scalar_t__*,int /*<<< orphan*/ *,int) ; 

int wctomb (char *mbchar, wchar_t wchar)
{
	NTSTATUS Status;
	ULONG Size;

	if (mbchar == NULL)
		return 0;

	Status = RtlUnicodeToMultiByteN (mbchar,
	                                 1,
	                                 &Size,
	                                 &wchar,
	                                 sizeof(WCHAR));
	if (!NT_SUCCESS(Status))
		return -1;

	return (int)Size;
}