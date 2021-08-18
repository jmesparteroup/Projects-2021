module alu(input  logic [31:0] a, b,
           input  logic [4:0]  c,
           input  logic [3:0]  alucontrol,
           output logic [31:0] result,
           output logic        zero);
  
  logic [31:0] condinvb, sum;

  assign condinvb = alucontrol[2] ? ~b : b;
  assign sum = a + condinvb + alucontrol[2];

  always_comb
    case(alucontrol)
    4'b1011: result = b*2**16; //LUI
    4'b0101: result = sum[31] ? 0 : 1;  //blt
    4'b1000: result = b*(2**c); // sll
    4'b1001: result = {4'h0000, b[15:0]};  //li
    4'b1100: result = ~a & ~b; //nor ~(A OR B)
    4'b1110: result = {a[31:16], b[15:0]}; // mix
    default: case (alucontrol[1:0])
                2'b00: result = a & b;
                2'b01: result = a | b;
                2'b10: result = sum;
                2'b11: result = sum[31];
              endcase
    endcase

  assign zero = (result == 32'b0);
endmodule
