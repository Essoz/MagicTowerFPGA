module SRAM_Multiplexer(
	// Avalon Clock Input
	input logic CLK, CLK2,
	
	// Avalon Reset Input
	input logic RESET,
	
	// Avalon-MM Slave Signals
	input  logic AVL_READ,					// Avalon-MM Read
	input  logic AVL_WRITE,					// Avalon-MM Write
	input  logic [20:0] AVL_ADDR,			// Avalon-MM Address
	input  logic [7:0] AVL_WRITEDATA,	// Avalon-MM Write Data
	output logic [7:0] AVL_READDATA,	// Avalon-MM Read Data
	
	// Hardware Access Interface
	input logic [20:0] HW_ADDR,
	output logic [7:0] HW_READDATA,
	
	// SRAM Signals
	output logic    [19:0]		SRAM_ADDR,
	output logic          		SRAM_CE_N,
	inout logic     [15:0]		SRAM_DQ,
	output logic          		SRAM_LB_N,
	output logic          		SRAM_OE_N,
	output logic          		SRAM_UB_N,
	output logic          		SRAM_WE_N
);

assign SRAM_CE_N = 1'b0;
// assign SRAM_LB_N = 1'b0;
// assign SRAM_UB_N = 1'b0;

logic CYCLE_EVEN;
logic BITGROUP_SEL;
always_ff @ (posedge CLK2) begin
	if(RESET) begin
		CYCLE_EVEN <= 1'b1;
	end else begin
		CYCLE_EVEN <= ~CYCLE_EVEN;
	end
end

logic[19:0] SRAM_ADDR_IN;
logic SRAM_WE_N_IN, SRAM_OE_N_IN;
logic[15:0] SRAM_DQ_IN;
logic SRAM_LB_N_IN, SRAM_UB_N_IN;
always_comb begin
	SRAM_ADDR_IN = CYCLE_EVEN ? AVL_ADDR[20:1] : HW_ADDR[20:1];
	SRAM_WE_N_IN = CYCLE_EVEN ? ~AVL_WRITE : 1'b1;
	SRAM_OE_N_IN = CYCLE_EVEN ? ~AVL_READ : 1'b0;
	SRAM_LB_N_IN = CYCLE_EVEN ? AVL_ADDR[0] : HW_ADDR[0];
	SRAM_UB_N_IN = CYCLE_EVEN ? ~AVL_ADDR[0] : HW_ADDR[0];
end
always_ff @ (posedge CLK2) begin
	SRAM_ADDR <= SRAM_ADDR_IN;
	SRAM_WE_N <= SRAM_WE_N_IN;
	SRAM_OE_N <= SRAM_OE_N_IN;
	SRAM_LB_N <= SRAM_LB_N_IN;
	SRAM_UB_N <= SRAM_UB_N_IN;
	BITGROUP_SEL <= SRAM_LB_N;
end

always_ff @ (posedge CLK2) begin
	if(CYCLE_EVEN) begin
		// AVL_READDATA <= SRAM_DQ[7 + 8 * SRAM_LB_N -: 8];
		AVL_READDATA <= SRAM_DQ[7 + 8 * BITGROUP_SEL -: 8];
	end else begin
		HW_READDATA <= SRAM_DQ[7 + 8 * BITGROUP_SEL -: 8];
	end
end

always_comb begin
	if (SRAM_WE_N) begin
		SRAM_DQ = 16'bZ;
	end
	else begin
		unique case (SRAM_LB_N)
			1'b0 : // lower 8 bit
			    SRAM_DQ = {8'b0, AVL_WRITEDATA};
			1'b1 : 
				SRAM_DQ = {AVL_WRITEDATA, 8'b0};
		endcase
	end
end
			
endmodule
