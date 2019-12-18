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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct smbios_table_type17 {void* xsize; void* arrayhand; } ;
struct smbios_structure {int dummy; } ;

/* Variables and functions */
 scalar_t__ guest_himem ; 
 scalar_t__ guest_lomem ; 
 int /*<<< orphan*/  smbios_generic_initializer (struct smbios_structure*,char const**,char*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* type16_handle ; 

__attribute__((used)) static int
smbios_type17_initializer(struct smbios_structure *template_entry,
    const char **template_strings, char *curaddr, char **endaddr,
    uint16_t *n, uint16_t *size)
{
	struct smbios_table_type17 *type17;

	smbios_generic_initializer(template_entry, template_strings,
	    curaddr, endaddr, n, size);
	type17 = (struct smbios_table_type17 *)curaddr;
	type17->arrayhand = type16_handle;
	type17->xsize = (uint32_t) guest_lomem;

	if (guest_himem > 0) {
		curaddr = *endaddr;
		smbios_generic_initializer(template_entry, template_strings,
		    curaddr, endaddr, n, size);
		type17 = (struct smbios_table_type17 *)curaddr;
		type17->arrayhand = type16_handle;
		type17->xsize = (uint32_t) guest_himem;
	}

	return (0);
}