// A register file module. 32 registers, each of it has 32 bit
// Supports 2 reading ports, 1 writing port
// ADDA: reading address of A, ADDB: reading addr of B
// ADDC:  writing address of C
// clk: clock signal
// clr: clear signal
// WE:  Write Enable

module registerfile(ADDA, DATAA, ADDB, DATAB, ADDC, DATAC, clk, clr, WE);
    input [4:0]  ADDA,ADDB, ADDC;
    input [31:0] DATAC;
    input clk, clr, WE;
    output [31:0] DATAA, DATAB;
    
    reg [31:0] DATAA, DATAB;

    reg [31:0] register [31:0];
    integer i;

    //clear all the registers in the register file
    initial begin
       for (i=0; i<32; i=i+1)
          register[i] = 0;
       $readmemh("reg.dat", register);
    end
    
    //only when a positive(rising) edge occurs
    always @(posedge clk or posedge clr) 
    begin
    // clear signal will reset all register as well
    if (clr)
       for (i=0; i<32; i=i+1)
          register[i] = 0;
    else
       // only when WE is 1, we write the register file 
       if (WE == 1)
       begin
          register[ADDC] = DATAC;
          register[0] = 0;
       end
    end
    
    // we read content of A and B only when a negative edge occurs 
    always @ (negedge clk )
    begin
           DATAA = register[ADDA];
           DATAB = register[ADDB];
    end
       
endmodule

module RegFileTestbench;
   reg [31:0] data; 
   reg [4:0] addrA, addrB, addrC;
   wire [31:0] outA;
   wire [31:0] outB;
   reg clks, clr, WE;
   
   integer ctr;

   registerfile UUT(addrA, outA, addrB, outB, addrC, data, clks, clr, WE);
   initial begin
       clks = 0;
       
       #10 clr = 0;
       WE = 0;
       
       for (ctr=0; ctr<31; ctr = ctr+1)
       begin
           #25 addrA <= ctr;
               addrB = ctr+1;
       end
       
       addrA = 2;
       addrB = 3;
       addrC = 3;
       WE = 1;
       
       for (ctr=0; ctr<10; ctr = ctr+1)
       begin
           #25 data <= ctr;
       end
       
       WE = 0;
   end

   initial 
       forever #20 clks = ~clks; 
   
   initial
      #1100 $stop;

endmodule
