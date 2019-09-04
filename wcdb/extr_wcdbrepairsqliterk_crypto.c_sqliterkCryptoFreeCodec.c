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
struct TYPE_3__ {int /*<<< orphan*/  codec; } ;
typedef  TYPE_1__ sqliterk_pager ;

/* Variables and functions */
 int /*<<< orphan*/  sqlcipher_codec_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlcipher_deactivate () ; 

void sqliterkCryptoFreeCodec(sqliterk_pager *pager)
{
    if (!pager->codec)
        return;
    sqlcipher_codec_ctx_free(&pager->codec);
    sqlcipher_deactivate();
}