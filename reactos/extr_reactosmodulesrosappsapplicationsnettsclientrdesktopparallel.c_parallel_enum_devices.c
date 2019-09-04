#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_5__ {TYPE_1__* rdpdr_device; } ;
struct TYPE_4__ {scalar_t__ handle; void* pdevice_data; int /*<<< orphan*/  device_type; scalar_t__ local_path; scalar_t__ name; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  PARALLEL_DEVICE ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_TYPE_PARALLEL ; 
 size_t RDPDR_MAX_DEVICES ; 
 char* next_arg (char*,char) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  toupper_str (scalar_t__) ; 
 scalar_t__ xmalloc (int) ; 

int
parallel_enum_devices(RDPCLIENT * This, uint32 * id, char *optarg)
{
	PARALLEL_DEVICE *ppar_info;

	char *pos = optarg;
	char *pos2;
	int count = 0;

	/* skip the first colon */
	optarg++;
	while ((pos = next_arg(optarg, ',')) && *id < RDPDR_MAX_DEVICES)
	{
		ppar_info = (PARALLEL_DEVICE *) xmalloc(sizeof(PARALLEL_DEVICE));

		pos2 = next_arg(optarg, '=');
		strcpy(This->rdpdr_device[*id].name, optarg);

		toupper_str(This->rdpdr_device[*id].name);

		This->rdpdr_device[*id].local_path = xmalloc(strlen(pos2) + 1);
		strcpy(This->rdpdr_device[*id].local_path, pos2);
		printf("PARALLEL %s to %s\n", optarg, pos2);

		/* set device type */
		This->rdpdr_device[*id].device_type = DEVICE_TYPE_PARALLEL;
		This->rdpdr_device[*id].pdevice_data = (void *) ppar_info;
		This->rdpdr_device[*id].handle = 0;
		count++;
		(*id)++;

		optarg = pos;
	}
	return count;
}