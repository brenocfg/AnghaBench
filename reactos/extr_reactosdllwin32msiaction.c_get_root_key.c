#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 int /*<<< orphan*/  msi_get_property_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szAllUsers ; 
 int /*<<< orphan*/ * szHCR ; 
 int /*<<< orphan*/ * szHCU ; 
 int /*<<< orphan*/ * szHLM ; 
 int /*<<< orphan*/ * szHU ; 

__attribute__((used)) static const WCHAR *get_root_key( MSIPACKAGE *package, INT root, HKEY *root_key )
{
    const WCHAR *ret;

    switch (root)
    {
    case -1:
        if (msi_get_property_int( package->db, szAllUsers, 0 ))
        {
            *root_key = HKEY_LOCAL_MACHINE;
            ret = szHLM;
        }
        else
        {
            *root_key = HKEY_CURRENT_USER;
            ret = szHCU;
        }
        break;
    case 0:
        *root_key = HKEY_CLASSES_ROOT;
        ret = szHCR;
        break;
    case 1:
        *root_key = HKEY_CURRENT_USER;
        ret = szHCU;
        break;
    case 2:
        *root_key = HKEY_LOCAL_MACHINE;
        ret = szHLM;
        break;
    case 3:
        *root_key = HKEY_USERS;
        ret = szHU;
        break;
    default:
        ERR("Unknown root %i\n", root);
        return NULL;
    }

    return ret;
}