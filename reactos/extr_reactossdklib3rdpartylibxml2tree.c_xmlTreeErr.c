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
typedef  int /*<<< orphan*/  xmlNodePtr ;

/* Variables and functions */
 int /*<<< orphan*/  XML_FROM_TREE ; 
#define  XML_TREE_INVALID_DEC 131 
#define  XML_TREE_INVALID_HEX 130 
#define  XML_TREE_NOT_UTF8 129 
#define  XML_TREE_UNTERMINATED_ENTITY 128 
 int /*<<< orphan*/  __xmlSimpleError (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static void
xmlTreeErr(int code, xmlNodePtr node, const char *extra)
{
    const char *msg = NULL;

    switch(code) {
        case XML_TREE_INVALID_HEX:
	    msg = "invalid hexadecimal character value\n";
	    break;
	case XML_TREE_INVALID_DEC:
	    msg = "invalid decimal character value\n";
	    break;
	case XML_TREE_UNTERMINATED_ENTITY:
	    msg = "unterminated entity reference %15s\n";
	    break;
	case XML_TREE_NOT_UTF8:
	    msg = "string is not in UTF-8\n";
	    break;
	default:
	    msg = "unexpected error number\n";
    }
    __xmlSimpleError(XML_FROM_TREE, code, node, msg, extra);
}