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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AML_LOGICAL_EQUAL_OP ; 
 int /*<<< orphan*/  AML_LOGICAL_GREATER_OP ; 
 int /*<<< orphan*/  AML_LOGICAL_LESS_OP ; 
 int /*<<< orphan*/  AcpiExDoLogicalOp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
#define  MATCH_MEQ 133 
#define  MATCH_MGE 132 
#define  MATCH_MGT 131 
#define  MATCH_MLE 130 
#define  MATCH_MLT 129 
#define  MATCH_MTR 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AcpiExDoMatch (
    UINT32                  MatchOp,
    ACPI_OPERAND_OBJECT     *PackageObj,
    ACPI_OPERAND_OBJECT     *MatchObj)
{
    BOOLEAN                 LogicalResult = TRUE;
    ACPI_STATUS             Status;


    /*
     * Note: Since the PackageObj/MatchObj ordering is opposite to that of
     * the standard logical operators, we have to reverse them when we call
     * DoLogicalOp in order to make the implicit conversion rules work
     * correctly. However, this means we have to flip the entire equation
     * also. A bit ugly perhaps, but overall, better than fussing the
     * parameters around at runtime, over and over again.
     *
     * Below, P[i] refers to the package element, M refers to the Match object.
     */
    switch (MatchOp)
    {
    case MATCH_MTR:

        /* Always true */

        break;

    case MATCH_MEQ:
        /*
         * True if equal: (P[i] == M)
         * Change to:     (M == P[i])
         */
        Status = AcpiExDoLogicalOp (
            AML_LOGICAL_EQUAL_OP, MatchObj, PackageObj, &LogicalResult);
        if (ACPI_FAILURE (Status))
        {
            return (FALSE);
        }
        break;

    case MATCH_MLE:
        /*
         * True if less than or equal: (P[i] <= M) (P[i] NotGreater than M)
         * Change to:                  (M >= P[i]) (M NotLess than P[i])
         */
        Status = AcpiExDoLogicalOp (
            AML_LOGICAL_LESS_OP, MatchObj, PackageObj, &LogicalResult);
        if (ACPI_FAILURE (Status))
        {
            return (FALSE);
        }
        LogicalResult = (BOOLEAN) !LogicalResult;
        break;

    case MATCH_MLT:
        /*
         * True if less than: (P[i] < M)
         * Change to:         (M > P[i])
         */
        Status = AcpiExDoLogicalOp (
            AML_LOGICAL_GREATER_OP, MatchObj, PackageObj, &LogicalResult);
        if (ACPI_FAILURE (Status))
        {
            return (FALSE);
        }
        break;

    case MATCH_MGE:
        /*
         * True if greater than or equal: (P[i] >= M) (P[i] NotLess than M)
         * Change to:                     (M <= P[i]) (M NotGreater than P[i])
         */
        Status = AcpiExDoLogicalOp (
            AML_LOGICAL_GREATER_OP, MatchObj, PackageObj, &LogicalResult);
        if (ACPI_FAILURE (Status))
        {
            return (FALSE);
        }
        LogicalResult = (BOOLEAN)!LogicalResult;
        break;

    case MATCH_MGT:
        /*
         * True if greater than: (P[i] > M)
         * Change to:            (M < P[i])
         */
        Status = AcpiExDoLogicalOp (
            AML_LOGICAL_LESS_OP, MatchObj, PackageObj, &LogicalResult);
        if (ACPI_FAILURE (Status))
        {
            return (FALSE);
        }
        break;

    default:

        /* Undefined */

        return (FALSE);
    }

    return (LogicalResult);
}