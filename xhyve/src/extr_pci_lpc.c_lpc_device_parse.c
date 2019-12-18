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
struct TYPE_2__ {char* opts; char* name; } ;

/* Variables and functions */
 int LPC_UART_NUM ; 
 int /*<<< orphan*/  free (char*) ; 
 char** lpc_uart_names ; 
 TYPE_1__* lpc_uart_softc ; 
 char* romfile ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 

int
lpc_device_parse(const char *opts)
{
	int unit, error;
	char *str, *cpy, *lpcdev;

	error = -1;
	str = cpy = strdup(opts);
	lpcdev = strsep(&str, ",");
	if (lpcdev != NULL) {
        if (strcasecmp(lpcdev, "bootrom") == 0) {
            romfile = str;
            error = 0;
            goto done;
        }
		for (unit = 0; unit < LPC_UART_NUM; unit++) {
			if (strcasecmp(lpcdev, lpc_uart_names[unit]) == 0) {
				lpc_uart_softc[unit].opts = str;
				lpc_uart_softc[unit].name = lpc_uart_names[unit];
				error = 0;
				goto done;
			}
		}
	}

done:
	if (error)
		free(cpy);

	return (error);
}