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
struct termios {int dummy; } ;
struct TYPE_7__ {TYPE_1__* rdpdr_device; } ;
struct TYPE_6__ {struct termios* pold_termios; struct termios* ptermios; } ;
struct TYPE_5__ {char* name; char* local_path; void* pdevice_data; int /*<<< orphan*/  device_type; } ;
typedef  TYPE_2__ SERIAL_DEVICE ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_TYPE_SERIAL ; 
 size_t RDPDR_MAX_DEVICES ; 
 int /*<<< orphan*/  memset (struct termios*,int /*<<< orphan*/ ,int) ; 
 char* next_arg (char*,char) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  toupper_str (char*) ; 
 char* xmalloc (int) ; 

int
serial_enum_devices(RDPCLIENT * This, uint32 * id, char *optarg)
{
	SERIAL_DEVICE *pser_inf;

	char *pos = optarg;
	char *pos2;
	int count = 0;

	/* skip the first colon */
	optarg++;
	while ((pos = next_arg(optarg, ',')) && *id < RDPDR_MAX_DEVICES)
	{
		/* Init data structures for device */
		pser_inf = (SERIAL_DEVICE *) xmalloc(sizeof(SERIAL_DEVICE));
		pser_inf->ptermios = (struct termios *) xmalloc(sizeof(struct termios));
		memset(pser_inf->ptermios, 0, sizeof(struct termios));
		pser_inf->pold_termios = (struct termios *) xmalloc(sizeof(struct termios));
		memset(pser_inf->pold_termios, 0, sizeof(struct termios));

		pos2 = next_arg(optarg, '=');
		strcpy(This->rdpdr_device[*id].name, optarg);

		toupper_str(This->rdpdr_device[*id].name);

		This->rdpdr_device[*id].local_path = xmalloc(strlen(pos2) + 1);
		strcpy(This->rdpdr_device[*id].local_path, pos2);
		printf("SERIAL %s to %s\n", This->rdpdr_device[*id].name,
		       This->rdpdr_device[*id].local_path);
		/* set device type */
		This->rdpdr_device[*id].device_type = DEVICE_TYPE_SERIAL;
		This->rdpdr_device[*id].pdevice_data = (void *) pser_inf;
		count++;
		(*id)++;

		optarg = pos;
	}
	return count;
}