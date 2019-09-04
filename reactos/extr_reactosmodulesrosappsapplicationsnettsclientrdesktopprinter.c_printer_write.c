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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  printer_fp; } ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  TYPE_1__ PRINTER ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_INVALID_HANDLE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_printer_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS
printer_write(RDPCLIENT * This, NTHANDLE handle, uint8 * data, uint32 length, uint32 offset, uint32 * result)
{
	PRINTER *pprinter_data;

	pprinter_data = get_printer_data(This, handle);
	*result = length * fwrite(data, length, 1, pprinter_data->printer_fp);

	if (ferror(pprinter_data->printer_fp))
	{
		*result = 0;
		return STATUS_INVALID_HANDLE;
	}
	return STATUS_SUCCESS;
}