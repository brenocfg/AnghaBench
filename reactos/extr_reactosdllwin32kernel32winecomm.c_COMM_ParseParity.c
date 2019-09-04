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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  EVENPARITY ; 
 int /*<<< orphan*/  MARKPARITY ; 
 int /*<<< orphan*/  NOPARITY ; 
 int /*<<< orphan*/  ODDPARITY ; 
 int /*<<< orphan*/  SPACEPARITY ; 
 int toupperW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPCWSTR COMM_ParseParity(LPCWSTR ptr, LPBYTE lpparity)
{
	/* Contrary to what you might expect, Windows only sets the Parity
	   member of DCB and not fParity even when parity is specified in the
	   device control string */

	switch(toupperW(*ptr++))
	{
	case 'E':
		*lpparity = EVENPARITY;
		break;
	case 'M':
		*lpparity = MARKPARITY;
		break;
	case 'N':
		*lpparity = NOPARITY;
		break;
	case 'O':
		*lpparity = ODDPARITY;
		break;
	case 'S':
		*lpparity = SPACEPARITY;
		break;
	default:
		return NULL;
	}

	return ptr;
}