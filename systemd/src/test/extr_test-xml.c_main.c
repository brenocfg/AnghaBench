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
 int /*<<< orphan*/  XML_ATTRIBUTE_NAME ; 
 int /*<<< orphan*/  XML_ATTRIBUTE_VALUE ; 
 int /*<<< orphan*/  XML_END ; 
 int /*<<< orphan*/  XML_TAG_CLOSE ; 
 int /*<<< orphan*/  XML_TAG_CLOSE_EMPTY ; 
 int /*<<< orphan*/  XML_TAG_OPEN ; 
 int /*<<< orphan*/  XML_TEXT ; 
 int /*<<< orphan*/  test_one (char*,int /*<<< orphan*/ ,...) ; 

int main(int argc, char *argv[]) {

        test_one("", XML_END);

        test_one("<foo></foo>",
                 XML_TAG_OPEN, "foo",
                 XML_TAG_CLOSE, "foo",
                 XML_END);

        test_one("<foo waldo=piep meh=\"huhu\"/>",
                 XML_TAG_OPEN, "foo",
                 XML_ATTRIBUTE_NAME, "waldo",
                 XML_ATTRIBUTE_VALUE, "piep",
                 XML_ATTRIBUTE_NAME, "meh",
                 XML_ATTRIBUTE_VALUE, "huhu",
                 XML_TAG_CLOSE_EMPTY, NULL,
                 XML_END);

        test_one("xxxx\n"
                 "<foo><?xml foo?>     <!-- zzzz -->  </foo>",
                 XML_TEXT, "xxxx\n",
                 XML_TAG_OPEN, "foo",
                 XML_TEXT, "     ",
                 XML_TEXT, "  ",
                 XML_TAG_CLOSE, "foo",
                 XML_END);

        return 0;
}