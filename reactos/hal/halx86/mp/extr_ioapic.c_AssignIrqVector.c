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
typedef  size_t ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t FIRST_DEVICE_VECTOR ; 
 size_t FIRST_SYSTEM_VECTOR ; 
 size_t IRQ2VECTOR (size_t) ; 
 size_t* IRQVectorMap ; 

__attribute__((used)) static ULONG 
AssignIrqVector(ULONG irq)
{
#if 0
   static ULONG current_vector = FIRST_DEVICE_VECTOR, vector_offset = 0;
#endif
   ULONG vector;
   /* There may already have been assigned a vector for this IRQ */
   vector = IRQVectorMap[irq];
   if (vector > 0)
   {
      return vector;
   }
#if 0
   if (current_vector > FIRST_SYSTEM_VECTOR) 
   {
      vector_offset++;
      current_vector = FIRST_DEVICE_VECTOR + vector_offset;
   } 
   else if (current_vector == FIRST_SYSTEM_VECTOR) 
   {
      DPRINT1("Ran out of interrupt sources!");
      ASSERT(FALSE);
   }

   vector = current_vector;
   IRQVectorMap[irq] = vector;
   current_vector += 8;
   return vector;
#else
   vector = IRQ2VECTOR(irq);
   IRQVectorMap[irq] = vector;
   return vector;
#endif
}