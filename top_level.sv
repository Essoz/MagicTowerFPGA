
/* TOP_LEVEL module for the final project */

module top_level(
                input               CLOCK_50,
                input        [3:0]  KEY,          //bit 0 is set up as Reset
                output logic [6:0]  HEX0, HEX1, HEX2, HEX3,
                                    HEX4, HEX5, HEX6, HEX7,
                output logic [3:0]  LEDG,	      //direction indication
                // VGA Interface 
                output logic [7:0]  VGA_R,        //VGA Red
                                    VGA_G,        //VGA Green
                                    VGA_B,        //VGA Blue
                output logic        VGA_CLK,      //VGA Clock
                                    VGA_SYNC_N,   //VGA Sync signal
                                    VGA_BLANK_N,  //VGA Blank signal
                                    VGA_VS,       //VGA virtical sync signal
                                    VGA_HS,       //VGA horizontal sync signal
                // CY7C67200 Interface
                inout  wire  [15:0] OTG_DATA,     //CY7C67200 Data bus 16 Bits
                output logic [1:0]  OTG_ADDR,     //CY7C67200 Address 2 Bits
                output logic        OTG_CS_N,     //CY7C67200 Chip Select
                                    OTG_RD_N,     //CY7C67200 Write
                                    OTG_WR_N,     //CY7C67200 Read
                                    OTG_RST_N,    //CY7C67200 Reset
                input               OTG_INT,      //CY7C67200 Interrupt
                // SDRAM Interface for Nios II Software
                output logic [12:0] DRAM_ADDR,    //SDRAM Address 13 Bits
                inout  wire  [31:0] DRAM_DQ,      //SDRAM Data 32 Bits
                output logic [1:0]  DRAM_BA,      //SDRAM Bank Address 2 Bits
                output logic [3:0]  DRAM_DQM,     //SDRAM Data Mast 4 Bits
                output logic        DRAM_RAS_N,   //SDRAM Row Address Strobe
                                    DRAM_CAS_N,   //SDRAM Column Address Strobe
                                    DRAM_CKE,     //SDRAM Clock Enable
                                    DRAM_WE_N,    //SDRAM Write Enable
                                    DRAM_CS_N,    //SDRAM Chip Select
                                    DRAM_CLK,      //SDRAM Clock


                output logic [19:0] SRAM_ADDR,
	            output logic        SRAM_CE_N,
	            inout logic  [15:0] SRAM_DQ,
	            output logic        SRAM_LB_N,
	            output logic        SRAM_OE_N,
	            output logic        SRAM_UB_N,
	            output logic        SRAM_WE_N
            );
    
    logic Reset_h, Clk;
    logic [7:0] keycode;
    
    assign Clk = CLOCK_50;
    always_ff @ (posedge Clk) begin
        Reset_h <= ~(KEY[0]);        // The push buttons are active low
    end
    
    logic [1:0]  hpi_addr;
    logic [15:0] hpi_data_in, hpi_data_out;
    logic hpi_r, hpi_w, hpi_cs, hpi_reset;
    
//    Interface between NIOS II and EZ-OTG chip
    hpi_io_intf hpi_io_inst(
                            .Clk(Clk),
                            .Reset(Reset_h),
                            // signals connected to NIOS II
                            .from_sw_address(hpi_addr),
                            .from_sw_data_in(hpi_data_in),
                            .from_sw_data_out(hpi_data_out),
                            .from_sw_r(hpi_r),
                            .from_sw_w(hpi_w),
                            .from_sw_cs(hpi_cs),
                            .from_sw_reset(hpi_reset),
                            // signals connected to EZ-OTG chip
                            .OTG_DATA(OTG_DATA),    
                            .OTG_ADDR(OTG_ADDR),    
                            .OTG_RD_N(OTG_RD_N),    
                            .OTG_WR_N(OTG_WR_N),    
                            .OTG_CS_N(OTG_CS_N),
                            .OTG_RST_N(OTG_RST_N)
    );


    logic [7:0]  FB_DIN;
    logic [20:0] FB_ADDR;

    logic [31:0] KnightX, KnightY;
    logic [10:0][10:0][31:0] MapConfig_32;
    logic [10:0][10:0][12:0] MapConfig_13;
    logic [9:0][31:0] Status;

    always_comb begin
        integer  i,j;
        for(i = 0; i < 11; i = i + 1)
            begin: traverse_y
            for (j = 0; j < 11; j = j + 1)
                begin : traverse_x
                    MapConfig_13[i][j] = MapConfig_32[i][j][12:0];
                end
            end
    end
    // Combinational Logic to calculate the correct address in OCM
    draw_toplevel draw_instance(.*,
                            .KnightX(KnightX[3:0]), .KnightY(KnightY[3:0]),
                            .MapConfig(MapConfig_13),
                            .AttributeTableValueArr({Status[4][13:0], Status[3][13:0], Status[2][13:0], Status[1][13:0]
                            , 14'b1}),
                            .KeyTableValueArr({Status[8][8:0], Status[7][8:0], Status[6][8:0], Status[5][8:0]})
    );


    // draw_toplevel draw_instance(.*);

    // You need to make sure that the port names here match the ports in Qsys-generated codes.
    final_soc nios_system(
                            .clk_clk(Clk),
                            .frame_clk_clk(VGA_VS),
                            // .reset_reset_n(1'b1),               // Never reset NIOS
                            .reset_reset_n(KEY[0]),               // Never reset NIOS
                            .keycode_export(keycode),

                            .export_data_export_config(MapConfig_32),
                            .export_data_export_status(Status),
                            .export_data_knightx(KnightX),
                            .export_data_knighty(KnightY),

                            .otg_hpi_address_export(hpi_addr),
                            .otg_hpi_data_in_port(hpi_data_in),
                            .otg_hpi_data_out_port(hpi_data_out),
                            .otg_hpi_cs_export(hpi_cs),
                            .otg_hpi_r_export(hpi_r),
                            .otg_hpi_w_export(hpi_w),
                            .otg_hpi_reset_export(hpi_reset),
                            .hex_hex0(HEX0),
                            .hex_hex1(HEX1),
                            .hex_hex2(HEX2),
                            .hex_hex3(HEX3),
                            .hex_hex4(HEX4),
                            .hex_hex5(HEX5),
                            .hex_hex6(HEX6),
                            .hex_hex7(HEX7),
                            .sdram_wire_addr(DRAM_ADDR),
                            .sdram_wire_ba(DRAM_BA),
                            .sdram_wire_cas_n(DRAM_CAS_N),
                            .sdram_wire_cke(DRAM_CKE),
                            .sdram_wire_cs_n(DRAM_CS_N),
                            .sdram_wire_dq(DRAM_DQ),
                            .sdram_wire_dqm(DRAM_DQM),
                            .sdram_wire_ras_n(DRAM_RAS_N),
                            .sdram_wire_we_n(DRAM_WE_N),
                            .sdram_clk_clk(DRAM_CLK),
                            .hardware_hw_addr(FB_ADDR),              //           hardware.hw_addr
		                    .hardware_hw_readdata(FB_DIN),
                            .sram_sram_oe_n(SRAM_OE_N),                //               sram.sram_oe_n
		                    .sram_sram_addr(SRAM_ADDR),                //                   .sram_addr
		                    .sram_sram_ce_n(SRAM_CE_N),                //                   .sram_ce_n
		                    .sram_sram_dq(SRAM_DQ),                  //                   .sram_dq
		                    .sram_sram_lb_n(SRAM_LB_N),                //                   .sram_lb_n
		                    .sram_sram_ub_n(SRAM_UB_N),                //                   .sram_ub_n
		                    .sram_sram_we_n(SRAM_WE_N)     
    );


	always_comb begin : DirectionLEDG
		localparam W = 10'd26;
		localparam A = 10'd04;
		localparam S = 10'd22;
		localparam D = 10'd07;
		LEDG = 4'b0;
		case (keycode)
			W: LEDG[3] = 1'b1;
			A: LEDG[2] = 1'b1;
			S: LEDG[1] = 1'b1;
			D: LEDG[0] = 1'b1;
		endcase
    end

endmodule
