#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int idReserved; int idType; } ;
struct TYPE_3__ {int bWidth; int bHeight; int dwDIBOffset; int dwDIBSize; } ;
struct test_ico {TYPE_2__ header; TYPE_1__ direntry; } ;
typedef  int /*<<< orphan*/  ico ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WINCODEC_ERR_BADIMAGE ; 
 int /*<<< orphan*/  WINCODEC_ERR_STREAMREAD ; 
 struct test_ico ico_1 ; 
 int /*<<< orphan*/  test_ico_data (struct test_ico*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ico_data_todo (struct test_ico*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_decoder(void)
{
    struct test_ico ico;

    /* Icon size specified in ICONDIRENTRY does not match bitmap header. */
    ico = ico_1;
    ico.direntry.bWidth = 2;
    ico.direntry.bHeight = 2;
    test_ico_data(&ico, sizeof(ico), S_OK);

    /* Invalid DIRENTRY data size/offset. */
    ico = ico_1;
    ico.direntry.dwDIBOffset = sizeof(ico);
    test_ico_data(&ico, sizeof(ico), WINCODEC_ERR_BADIMAGE);

    ico = ico_1;
    ico.direntry.dwDIBSize = sizeof(ico);
    test_ico_data(&ico, sizeof(ico), WINCODEC_ERR_BADIMAGE);

    /* Header fields validation. */
    ico = ico_1;
    ico.header.idReserved = 1;
    test_ico_data_todo(&ico, sizeof(ico), S_OK);
    ico.header.idReserved = 0;
    ico.header.idType = 100;
    test_ico_data_todo(&ico, sizeof(ico), S_OK);

    /* Premature end of data. */
    ico = ico_1;
    test_ico_data(&ico, sizeof(ico.header) - 1, WINCODEC_ERR_STREAMREAD);
    test_ico_data(&ico, sizeof(ico.header) + sizeof(ico.direntry) - 1, WINCODEC_ERR_BADIMAGE);
}