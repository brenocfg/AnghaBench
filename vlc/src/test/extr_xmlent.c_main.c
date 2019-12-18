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
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  decode (char*,char*) ; 
 int /*<<< orphan*/  encode (char*,char*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int main (void)
{
    (void)setvbuf (stdout, NULL, _IONBF, 0);
    decode ("This should not be modified 1234",
            "This should not be modified 1234");

    decode ("R&eacute;mi&nbsp;Fran&ccedil;ois&nbsp;&amp;&nbsp;&Eacute;mile",
            "Rémi François & Émile");
    decode ("R&#233;mi&nbsp;Fran&#231;ois&nbsp;&amp;&nbsp;&#201;mile",
            "Rémi François & Émile");
    decode ("R&#xe9;mi&nbsp;Fran&#xe7;ois&nbsp;&amp;&nbsp;&#xc9;mile",
            "Rémi François & Émile");
    decode ("R&#xE9;mi&nbsp;Fran&#xE7;ois&nbsp;&amp;&nbsp;&#xC9;mile",
            "Rémi François & Émile");

    decode ("", "");

    /* tests with invalid input */
    decode ("&<\"'", "&<\"'");
    decode ("&oelig", "&oelig");

    encode ("", "");
    encode ("a'àc\"çe&én<ño>ö1:", "a&#39;àc&quot;çe&amp;én&lt;ño&gt;ö1:");
    encode ("\xC2\x81\xC2\x85", "&#129;\xC2\x85");
    encode (" \t\r\n", " \t\r\n");

    return 0;
}