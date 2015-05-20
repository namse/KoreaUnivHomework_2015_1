/* 2 to 1 MUX, select from two 32-bit input*/
module mux2to1(datain0,datain1, dataout, select);
input [31:0] datain0, datain1;
input select;
output [31:0] dataout; 
reg [31:0] dataout;

/*whenever datain0 or datain1 or select signals is changed*/
always @(datain0 or datain1 or select)
begin 
if (select == 0)
   dataout = datain0;
else
   dataout = datain1;
end 
endmodule

module muxTestbench;
   reg [31:0] datain0,datain1;  
   reg select;
   wire [31:0] dataout;

   mux2to1 UUT(datain0, datain1, dataout,select);

   initial begin
       #20 datain0 = 8;
           datain1 = 13;
           select = 0;
       #20 datain0 = 8;
           datain1 = 13;
           select = 1;
       #20 datain0 = 20;
           datain1 = 21;
           select = 1;
       #20 datain0 = 55;
           datain1 = 66;
           select = 1;
       #20 datain0 = 55;
           datain1 = 66;
           select = 0;
   end

   initial
      #120 $stop;

endmodule
