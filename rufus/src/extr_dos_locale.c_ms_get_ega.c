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
typedef  int ULONG ;

/* Variables and functions */

__attribute__((used)) static const char* ms_get_ega(ULONG cp)
{
	switch(cp) {
	case   437: // United States
	case   850: // Latin-1 (Western European)
	case   852: // Latin-2 (Central European)
	case   860: // Portuguese
	case   863: // French Canadian
	case   865: // Nordic
		return "ega.cpi";

//	case   850: // Latin-1 (Western European)
//	case   852: // Latin-2 (Central European)
	case   857: // Turkish
	case   861: // Icelandic
	case   869: // Greek
	case   737: // Greek II
		return "ega2.cpi";

//	case   437: // United States
	case   775: // Baltic
//	case   850: // Latin-1 (Western European)
//	case   852: // Latin-2 (Central European)
	case   855: // Cyrillic I
	case   866: // Cyrillic II
		return "ega3.cpi";

	default:
		return NULL;
	}
}