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
typedef  unsigned char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  RegCreateKeyW (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyW (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT OpenURLSubkey(HKEY rootkey, HKEY *key, BOOL create)
{
    UINT rc;
    static const WCHAR URL[] = {'U','R','L',0};

    if (create)
        rc = RegCreateKeyW(rootkey, URL, key);
    else
        rc = RegOpenKeyW(rootkey, URL, key); 

    return rc;
}