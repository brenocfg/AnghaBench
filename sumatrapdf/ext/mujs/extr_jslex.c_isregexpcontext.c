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
#define  TK_FALSE 134 
#define  TK_IDENTIFIER 133 
#define  TK_NULL 132 
#define  TK_NUMBER 131 
#define  TK_STRING 130 
#define  TK_THIS 129 
#define  TK_TRUE 128 

__attribute__((used)) static int isregexpcontext(int last)
{
	switch (last) {
	case ']':
	case ')':
	case '}':
	case TK_IDENTIFIER:
	case TK_NUMBER:
	case TK_STRING:
	case TK_FALSE:
	case TK_NULL:
	case TK_THIS:
	case TK_TRUE:
		return 0;
	default:
		return 1;
	}
}