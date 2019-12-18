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
typedef  int /*<<< orphan*/  sqliterk_cipher_conf ;
typedef  int /*<<< orphan*/  sqliterk ;

/* Variables and functions */
 int sqliterkOpen (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 

int sqliterk_open(const char *path,
                  const sqliterk_cipher_conf *cipher,
                  sqliterk **rk)
{
    return sqliterkOpen(path, cipher, rk);
}