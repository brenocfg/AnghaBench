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
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_STRING_BASE64 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  decodeBase64WithLenFmt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decodeBase64WithLenBroken(LPCSTR str, int len, LPCSTR expected, int le)
{
    decodeBase64WithLenFmt(str, len, CRYPT_STRING_BASE64, expected, le, TRUE);
}