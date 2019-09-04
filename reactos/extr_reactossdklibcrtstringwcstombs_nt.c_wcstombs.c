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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlUnicodeToMultiByteN (char*,int,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlUnicodeToMultiByteSize (int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wcslen (int /*<<< orphan*/  const*) ; 

size_t wcstombs (char *mbstr, const wchar_t *wcstr, size_t count)
{
	NTSTATUS Status;
	ULONG Size;
	ULONG Length;

	Length = (ULONG)wcslen (wcstr);

	if (mbstr == NULL)
	{
		RtlUnicodeToMultiByteSize (&Size,
		                           (wchar_t*)((size_t)wcstr),
		                           Length * sizeof(WCHAR));

		return (size_t)(Size / sizeof(char));
	}

	Status = RtlUnicodeToMultiByteN (mbstr,
	                                 (ULONG)count,
	                                 &Size,
	                                 (wchar_t*)((size_t)wcstr),
	                                 Length * sizeof(WCHAR));
	if (!NT_SUCCESS(Status))
		return -1;

	return (size_t)(Size / sizeof(char));
}