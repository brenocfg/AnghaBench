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
typedef  int /*<<< orphan*/  pdfapp_t ;

/* Variables and functions */

char *pdfapp_usage(pdfapp_t *app)
{
	return
		"[\t\t-- rotate left\n"
		"]\t\t-- rotate right\n"
		"h left\t\t-- scroll left\n"
		"j down\t\t-- scroll down\n"
		"k up\t\t-- scroll up\n"
		"l right\t\t-- scroll right\n"
		"+\t\t-- zoom in\n"
		"-\t\t-- zoom out\n"
		"W\t\t-- zoom to fit window width\n"
		"H\t\t-- zoom to fit window height\n"
		"Z\t\t-- zoom to fit page\n"
		"z\t\t-- reset zoom\n"
		"<\t\t-- decrease font size (EPUB only)\n"
		">\t\t-- increase font size (EPUB only)\n"
		"w\t\t-- shrinkwrap\n"
		"f\t\t-- fullscreen\n"
		"r\t\t-- reload file\n"
		". pgdn space\t-- next page\n"
		", pgup b\t-- previous page\n"
		"m\t\t-- mark page for snap back\n"
		"t\t\t-- pop back to latest mark\n"
		"1m\t\t-- mark page in register 1\n"
		"1t\t\t-- go to page in register 1\n"
		"G\t\t-- go to last page\n"
		"123g\t\t-- go to page 123\n"
		"/\t\t-- search forwards for text\n"
		"?\t\t-- search backwards for text\n"
		"n\t\t-- find next search result\n"
		"N\t\t-- find previous search result\n"
		"c\t\t-- toggle between color and grayscale\n"
		"I\t\t-- toggle inverted color mode\n"
		"C\t\t-- toggle tinted color mode\n"
		"E\t\t-- enable/disable ICC color mode\n"
		"e\t\t-- enable/disable spot color mode\n"
		"q\t\t-- quit\n"
	;
}