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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PI2C_CALLBACKS ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_HALF () ; 
 int /*<<< orphan*/  HIGH ; 
 int /*<<< orphan*/  LOW ; 
 int /*<<< orphan*/  WRITE_SCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_SDA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
I2CStop(PVOID HwDeviceExtension, PI2C_CALLBACKS i2c)
{
   WRITE_SCL(LOW);
   WRITE_SDA(LOW);
   DELAY_HALF();
   WRITE_SCL(HIGH);
   DELAY_HALF();
   WRITE_SDA(HIGH);
}