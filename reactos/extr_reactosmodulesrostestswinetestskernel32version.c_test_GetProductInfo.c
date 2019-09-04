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
typedef  int DWORD ;

/* Variables and functions */
 int GetLastError () ; 
 int PRODUCT_ENTERPRISE_S_N_EVALUATION ; 
 int PRODUCT_UNDEFINED ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,...) ; 
 int pGetProductInfo (int,int,int,int,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetProductInfo(void)
{
    DWORD product;
    DWORD res;
    DWORD table[] = {9,8,7,6,
                     7,0,0,0,
                     6,2,0,0,
                     6,1,2,0,
                     6,1,1,0,
                     6,1,0,2,
                     6,1,0,0,
                     6,0,3,0,
                     6,0,2,0,
                     6,0,1,5,
                     6,0,1,0,
                     6,0,0,0,
                     5,3,0,0,
                     5,2,0,0,
                     5,1,0,0,
                     5,0,0,0,
                     0};

    DWORD *entry = table;

    if (!pGetProductInfo)
    {
        /* Not present before Vista */
        win_skip("GetProductInfo() not available\n");
        return;
    }

    while (*entry)
    {
        /* SetLastError() / GetLastError(): value is untouched */
        product = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pGetProductInfo(entry[0], entry[1], entry[2], entry[3], &product);

        if (entry[0] >= 6)
            ok(res && (product > PRODUCT_UNDEFINED) && (product <= PRODUCT_ENTERPRISE_S_N_EVALUATION),
               "got %d and 0x%x (expected TRUE and a valid PRODUCT_* value)\n", res, product);
        else
            ok(!res && !product && (GetLastError() == 0xdeadbeef),
               "got %d and 0x%x with 0x%x (expected FALSE and PRODUCT_UNDEFINED with LastError untouched)\n",
               res, product, GetLastError());

        entry+= 4;
    }

    /* NULL pointer is not a problem */
    SetLastError(0xdeadbeef);
    res = pGetProductInfo(6, 1, 0, 0, NULL);
    ok( (!res) && (GetLastError() == 0xdeadbeef),
        "got %d with 0x%x (expected FALSE with LastError untouched\n", res, GetLastError());
}