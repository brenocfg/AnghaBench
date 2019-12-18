#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_7__ {char* printer; void* printer_fp; } ;
struct TYPE_6__ {TYPE_1__* rdpdr_device; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle; scalar_t__ pdevice_data; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  TYPE_3__ PRINTER ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  fileno (void*) ; 
 void* popen (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static NTSTATUS
printer_create(RDPCLIENT * This, uint32 device_id, uint32 access, uint32 share_mode, uint32 disposition, uint32 flags,
	       char *filename, NTHANDLE * handle)
{
	char cmd[256];
	PRINTER *pprinter_data;

	pprinter_data = (PRINTER *) This->rdpdr_device[device_id].pdevice_data;

	/* default printer name use default printer queue as well in unix */
	if (pprinter_data->printer == "mydeskjet")
	{
		pprinter_data->printer_fp = popen("lpr", "w");
	}
	else
	{
		sprintf(cmd, "lpr -P %s", pprinter_data->printer);
		pprinter_data->printer_fp = popen(cmd, "w");
	}

	This->rdpdr_device[device_id].handle = fileno(pprinter_data->printer_fp);
	*handle = This->rdpdr_device[device_id].handle;
	return STATUS_SUCCESS;
}