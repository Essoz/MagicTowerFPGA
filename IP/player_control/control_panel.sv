module control_panel (
                        // Avalon Clock Input
                        input  logic Clk,                   // Main clock (50MHz)
                        input  logic frame_clk,             // The clock indicating a new frame (~60Hz)

                        // Avalon Reset Input
                        input  logic Reset,
                        
                        // Avalon-MM Slave Signals
                        input  logic AVL_READ,				// Avalon-MM Read
                        input  logic AVL_WRITE,				// Avalon-MM Write
                        input  logic AVL_CS,				// Avalon-MM Chip Select
                        input  logic [3:0] AVL_BYTE_EN,		// Avalon-MM Byte Enable
                        input  logic [7:0] AVL_ADDR,		// Avalon-MM Address
                        input  logic [31:0] AVL_WRITEDATA,	// Avalon-MM Write Data
                        output logic [31:0] AVL_READDATA,	// Avalon-MM Read Data
                        
                        // Exported Conduit
                        /* STATUS: {Status, Health, Attack, Defense, EXP, 
                                    Yellow_Key, Blue_Key, Red_Key, Coin, Special_Items} */
                        output logic [319:0]   EXPORT_STATUS,
                        output logic [3871:0]  EXPORT_CONFIG,
                        output logic [31:0]    KnightX, KnightY,
                        output logic [6:0]  HEX0, HEX1, HEX2, HEX3,
                                            HEX4, HEX5, HEX6, HEX7
                    );

    // Detect rising edge of frame_clk
    logic frame_clk_delayed, frame_clk_rising_edge;
    always_ff @ (posedge Clk) begin
        frame_clk_delayed <= frame_clk;
        frame_clk_rising_edge <= (frame_clk == 1'b1) && (frame_clk_delayed == 1'b0);
    end

    // Internal Logics
    logic [132:0][31:0] reg_file;

    // Read Operations
    always_comb begin
        EXPORT_STATUS = reg_file[9:0];
        EXPORT_CONFIG = reg_file[130:10];
        KnightX       = reg_file[131];
        KnightY       = reg_file[132];
    end

    // Read Operations to the MM BUS
	always_comb	begin
        AVL_READDATA = 32'h0;
		if (AVL_CS && AVL_READ)
			AVL_READDATA = reg_file[AVL_ADDR];			
	end

    // Write Operation
    always_ff @ (posedge Clk)
    begin
	 	if (Reset) begin
		    reg_file[132:0] <= 4256'd0;
		end
		else if (AVL_CS && AVL_WRITE) begin
			case(AVL_BYTE_EN)
				4'b1111: reg_file[AVL_ADDR]         <= AVL_WRITEDATA;
				4'b1100: reg_file[AVL_ADDR] [31:16] <= AVL_WRITEDATA[31:16];
				4'b0011: reg_file[AVL_ADDR] [15:0]  <= AVL_WRITEDATA[15:0];
				4'b1000: reg_file[AVL_ADDR] [31:24] <= AVL_WRITEDATA[31:24];
				4'b0100: reg_file[AVL_ADDR] [23:16] <= AVL_WRITEDATA[23:16];
				4'b0010: reg_file[AVL_ADDR] [15:8]  <= AVL_WRITEDATA[15:8];
				4'b0001: reg_file[AVL_ADDR] [7:0]   <= AVL_WRITEDATA[7:0];
				default: ;
			endcase
        end
    end

// HexDriver hex1 (.In0(encounter_signal[3:0]), .Out0(HEX0));
// HexDriver hex2 (.In0(encounter_signal[7:4]), .Out0(HEX1));
// HexDriver hex3 (.In0(MapConfig[3][3:0]), .Out0(HEX2));
// HexDriver hex4 (.In0(MapConfig[3][7:4]), .Out0(HEX3));
// HexDriver hex5 (.In0({3'b000, START}), .Out0(HEX4));
// HexDriver hex6 (.In0({3'b000, DONE}), .Out0(HEX5));
HexDriver hex7 (.In0(KnightX[3:0]), .Out0(HEX6));
HexDriver hex8 (.In0(KnightY[3:0]), .Out0(HEX7));

endmodule
