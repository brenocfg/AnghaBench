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
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int check_CFE_LINK_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,char const*) ; 

__attribute__((used)) static void check_CFE_LINK_rcvd(HWND hwnd, BOOL is_url, const char * url)
{
  BOOL link_present = FALSE;

  link_present = check_CFE_LINK_selection(hwnd, 0, 1);
  if (is_url) 
  { /* control text is url; should get CFE_LINK */
    ok(link_present, "URL Case: CFE_LINK not set for [%s].\n", url);
  }
  else 
  {
    ok(!link_present, "Non-URL Case: CFE_LINK set for [%s].\n", url);
  }
}