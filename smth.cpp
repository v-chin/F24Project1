//////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    tb_comparator_vchin.v
// Author:      Victoria Chin
// Created:     31 January 2025
// Version:     1
//
// Description: This file contains a test bench for a magnitude comparator circuit that iterates
//              through every valid input combination.
//
//              There are no inputs or outputs to this module.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

// Time Unit = 1 ns (#1 = 1 ns)
// Simulation Precision = 1 ns
`timescale 1ns/1ns

module tb_comparator_vchin();

   reg [2:0] valA_in, valB_in;		// THREE-BIT INPUTS FOR DUT
   wire      aGTb_out, aGEb_out,
             aLTb_out, aLEb_out,
             aEQb_out, aNEb_out;	// OUTPUT BITS FOR DUT

   reg [3:0] valA_count, valB_count;	// FOR ITERATING THROUGH ALL POSSIBLE INPUTS

   // Instantiate the comparator module (the identifier is dut, or "device under test").
   comparator_structural_vchin dut(valA_in, valB_in, aGTb_out, aGEb_out, aLTb_out, aLEb_out, aEQb_out, aNEb_out);

   initial begin

      valA_in = 3'b000;	// At time t = 0, valA_in = 3'b000
      valB_in = 3'b000;	// At time t = 0, valB_in = 3'b000

      // Iterate through each valid input for the comparator.
      for (valA_count = 0; valA_count < 4'd8; valA_count = valA_count + 1) begin
         valA_in = valA_count[2:0];
         for (valB_count = 0; valB_count < 4'd8; valB_count = valB_count + 1) begin
            valB_in = valB_count[2:0];
            #50;	// Wait for 50 ns.
         end
      end

   end

endmodule
