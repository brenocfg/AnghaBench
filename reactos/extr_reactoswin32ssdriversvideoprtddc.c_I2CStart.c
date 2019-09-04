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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PI2C_CALLBACKS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_HALF () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  I2CStop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2CWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO_ (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LOW ; 
 scalar_t__ READ_SCL () ; 
 scalar_t__ READ_SDA () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VIDEOPRT ; 
 int /*<<< orphan*/  WARN_ (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  WRITE_SDA (scalar_t__) ; 

__attribute__((used)) static BOOL
I2CStart(PVOID HwDeviceExtension, PI2C_CALLBACKS i2c, UCHAR Address)
{
   /* make sure the bus is free */
   if (READ_SDA() == LOW || READ_SCL() == LOW)
     {
        WARN_(VIDEOPRT, "I2CStart: Bus is not free!\n");
        return FALSE;
     }

   /* send address */
   WRITE_SDA(LOW);
   DELAY_HALF();
   if (!I2CWrite(HwDeviceExtension, i2c, Address))
     {
        /* ??release the bus?? */
        I2CStop(HwDeviceExtension, i2c);
        WARN_(VIDEOPRT, "I2CStart: Device not found (Address = 0x%x)\n", Address);
        return FALSE;
     }

   INFO_(VIDEOPRT, "I2CStart: SUCCESS!\n");
   return TRUE;
}