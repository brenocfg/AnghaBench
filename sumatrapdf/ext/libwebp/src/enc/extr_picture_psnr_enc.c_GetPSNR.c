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

/* Variables and functions */
 double kMinDistortion_dB ; 
 double log (double) ; 

__attribute__((used)) static double GetPSNR(double v, double size) {
  return (v > 0. && size > 0.) ? -4.3429448 * log(v / (size * 255 * 255.))
                               : kMinDistortion_dB;
}