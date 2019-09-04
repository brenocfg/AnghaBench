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

/* Variables and functions */

__attribute__((used)) static const char *enc_name(unsigned char enc)
{
	switch(enc)
	{
		case 0:  return "Latin 1";
		case 1:  return "UTF-16 BOM";
		case 2:  return "UTF-16 BE";
		case 3:  return "UTF-8";
		default: return "unknown!";
	}
}