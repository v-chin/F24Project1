//////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    comparator_structural_vchin.v
// Author:      Victoria Chin
// Created:     31 January 2025
// Version:     1
//
// Description: This file contains the digital logic for a magnitude comparator circuit.
//
//              The module uses the following inputs:
//              - valA, valB: The three-bit unsigned binary numbers to be compared.
//
//              The module uses the following outputs:
//              - aGTb: 1 if A is greater than B, 0 otherwise.
//              - aGEb: 1 if A is greater than or equal to B, 0 otherwise.
//              - aLTb: 1 if A is less than B, 0 otherwise.
//              - aLEb: 1 if A is less than or equal to B, 0 otherwise.
//              - aEQb: 1 if A is equal to B, 0 otherwise.
//              - aNEb: 1 if A is not equal to B, 0 otherwise.
//////////////////////////////////////////////////////////////////////////////////////////////////

module comparator_structural_vchin(valA, valB, aGTb, aGEb, aLTb, aLEb, aEQb, aNEb);
   input  [2:0] valA, valB;
   output       aGTb, aGEb, aLTb, aLEb, aEQb, aNEb;

   // Your module MUST consist solely of primitive logic gates.
   // Declare additional wires as needed.

   // WIRES FOR INVERTED BITS
   wire A2_n, A1_n, A0_n, B2_n, B1_n, B0_n;

   // WIRES FOR HELPER LOGICS
   wire [6:0]  GT, LT;
   wire [10:0] GE, LE;
   wire [7:0]  EQ;
   wire [5:0]  NE;

   not not1(A2_n, valA[2]), not2(A1_n, valA[1]), not3(A0_n, valA[0]),
       not4(B2_n, valB[2]), not5(B1_n, valB[1]), not6(B0_n, valB[0]);

   // HELPER LOGIC TO DETERMINE A > B
   and and1(GT[0], valA[2], B2_n),                   and2(GT[1], valA[1], B2_n,    B1_n),
       and3(GT[2], valA[2], valA[1], B1_n),          and4(GT[3], valA[0], B2_n,    B1_n, B0_n),
       and5(GT[4], valA[1], valA[0], B2_n,    B0_n), and6(GT[5], valA[2], valA[0], B1_n, B0_n),
       and7(GT[6], valA[2], valA[1], valA[0], B0_n);

   // HELPER LOGIC TO DETERMINE A >= B
   and  and8(GE[0], valA[2], B2_n),           and9(GE[1], B2_n, B1_n, B0_n),
       and10(GE[2], valA[0], B2_n, B1_n),    and11(GE[3], valA[1], B2_n, B1_n),
       and12(GE[4], valA[1], B2_n, B0_n),    and13(GE[5], valA[1], valA[0], B2_n),
       and14(GE[6], valA[2], B1_n, B0_n),    and15(GE[7], valA[2], valA[0], B1_n),
       and16(GE[8], valA[2], valA[1], B1_n), and17(GE[9], valA[2], valA[1], B0_n),
       and18(GE[10], valA[2], valA[1], valA[0]);

   // HELPER LOGIC TO DETERMINE A < B
   and and19(LT[0], A2_n, valB[2]),                and20(LT[1], A2_n, A1_n, valB[1]),
       and21(LT[2], A1_n, valB[2], valB[1]),       and22(LT[3], A2_n, A1_n, A0_n, valB[0]),
       and23(LT[4], A2_n, A0_n, valB[1], valB[0]), and24(LT[5], A1_n, A0_n, valB[2], valB[0]),
       and25(LT[6], A0_n, valB[2], valB[1], valB[0]);

   // HELPER LOGIC TO DETERMINE A <= B
   and and26(LE[0], A2_n, valB[2]),          and27(LE[1], A2_n, A1_n, A0_n),
       and28(LE[2], A2_n, A1_n, valB[0]),    and29(LE[3], A2_n, A1_n, valB[1]),
       and30(LE[4], A2_n, A0_n, valB[1]),    and31(LE[5], A2_n, valB[1], valB[0]),
       and32(LE[6], A1_n, A0_n, valB[2]),    and33(LE[7], A1_n, valB[2], valB[0]),
       and34(LE[8], A1_n, valB[2], valB[1]), and35(LE[9], A0_n, valB[2], valB[1]),
       and36(LE[10], valB[2], valB[1], valB[0]);

   // HELPER LOGIC TO DETERMINE A == B
   and and37(EQ[0], A2_n, A1_n, A0_n, B2_n, B1_n, B0_n),             and38(EQ[1], A2_n, A1_n, valA[0], B2_n, B1_n, valB[0]),
       and39(EQ[2], A2_n, valA[1], A0_n, B2_n, valB[1], B0_n),       and40(EQ[3], A2_n, valA[1], valA[0], B2_n, valB[1], valB[0]),
       and41(EQ[4], valA[2], A1_n, A0_n, valB[2], B1_n, B0_n),       and42(EQ[5], valA[2], A1_n, valA[0], valB[2], B1_n, valB[0]),
       and43(EQ[6], valA[2], valA[1], A0_n, valB[2], valB[1], B0_n), and44(EQ[7], valA[2], valA[1], valA[0], valB[2], valB[1], valB[0]);

   // HELPER LOGIC TO DETERMINE A != B
   and and45(NE[0], A0_n, valB[0]),  and46(NE[1], A1_n, valB[1]), and47(NE[2], A2_n, valB[2]),
       and48(NE[3], valA[0], B0_n),  and49(NE[4], valA[1], B1_n), and50(NE[5], valA[2], B2_n);

   // LOGIC TO DETERMINE A > B, A >= B, A < B, A <= B, A == B, A != B
   or or1(aGTb, GT[0], GT[1], GT[2], GT[3], GT[4], GT[5], GT[6]);
   or or2(aGEb, GE[0], GE[1], GE[2], GE[3], GE[4], GE[5], GE[6], GE[7], GE[8], GE[9], GE[10]);
   or or3(aLTb, LT[0], LT[1], LT[2], LT[3], LT[4], LT[5], LT[6]);
   or or4(aLEb, LE[0], LE[1], LE[2], LE[3], LE[4], LE[5], LE[6], LE[7], LE[8], LE[9], LE[10]);
   or or5(aEQb, EQ[0], EQ[1], EQ[2], EQ[3], EQ[4], EQ[5], EQ[6], EQ[7]);
   or or6(aNEb, NE[0], NE[1], NE[2], NE[3], NE[4], NE[5]);

endmodule
