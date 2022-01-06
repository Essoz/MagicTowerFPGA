//-------------------------------------------------------------------------
//      lab8.sv                                                          --
//      Christine Chen                                                   --
//      Fall 2014                                                        --
//                                                                       --
//      Modified by Po-Han Huang                                         --
//      10/06/2017                                                       --
//                                                                       --
//      Fall 2017 Distribution                                           --
//                                                                       --
//      For use with ECE 385 Lab 8                                       --
//      UIUC ECE Department                                              --
//-------------------------------------------------------------------------


module draw_toplevel( 
            input               CLOCK_50,
            input        [3:0]  KEY,          //bit 0 is set up as Reset
            // output logic [3:0]  LEDG,			  // direction indication
             // VGA Interface 
            output logic [7:0]  VGA_R,        // VGA Red
                                VGA_G,        // VGA Green
                                VGA_B,        // VGA Blue
            output logic        VGA_CLK,      // VGA Clock
                                VGA_SYNC_N,   // VGA Sync signal
                                VGA_BLANK_N,  // VGA Blank signal
                                VGA_VS,       // VGA virtical sync signal
                                VGA_HS,       // VGA horizontal sync signal
            input  logic [3:0]  KnightX, KnightY,
            input  logic [10:0][10:0][12:0] MapConfig,
            input  logic [4:0][13:0] AttributeTableValueArr,
            input  logic [3:0][8:0] KeyTableValueArr,
            
            input  logic [7:0]  FB_DIN,
            output logic [20:0] FB_ADDR
            );
    
    logic RESET_H, CLK;
    parameter [20:0] FRAME_BUFFER_ADDR = 21'b0;         // Starting Address of Frame Buffer on 
    
    parameter [1:0][9:0] Sect0Coor = {10'd32 , 10'd224};
    parameter [1:0][9:0] Sect1Coor = {10'd32 , 10'd32 };
    parameter [1:0][9:0] Sect2Coor = {10'd254, 10'd32 }; 
    parameter [1:0][9:0] Sect0Size = {10'd352, 10'd352};
    parameter [1:0][9:0] Sect1Size = {10'd192, 10'd160};
    parameter [1:0][9:0] Sect2Size = {10'd128, 10'd160};

    parameter TILE_WIDTH = 32;
    
    assign CLK = CLOCK_50;
    always_ff @ (posedge CLK) begin
        RESET_H <= ~(KEY[0]);        // The push buttons are active low
    end
    
    // Use PLL to generate the 25MHZ VGA_CLK.
    // You will have to generate it on your own in simulation.
    vga_clk vga_clk_instance(.inclk0(CLK), .c0(VGA_CLK));
    
    logic [9:0] DrawX, DrawY;
    VGA_controller vga_controller_instance(.*, .Reset(RESET_H));
    
    logic [7:0] Sect0Color;
    logic [7:0] Sect1Color;
    logic [7:0] Sect2Color;
    logic [7:0] FBColor;
    logic [7:0] BackgroundColor;


    logic IsFBTransparent = 1;
    always_ff @ (posedge VGA_VS) begin
        IsFBTransparent <= KEY[2];
    end

    color_mapper #(
        .Sect0Coor(Sect0Coor),
        .Sect1Coor(Sect1Coor),
        .Sect2Coor(Sect2Coor),
        .Sect0Size(Sect0Size),
        .Sect1Size(Sect1Size),
        .Sect2Size(Sect2Size)
    ) color_instance (.*); 
    
    game_interface_drawer #(
        .COOR(Sect0Coor),
        .SIZE(Sect0Size),
        .TILE_WIDTH(TILE_WIDTH)
    ) game_instance (    
    .CLK,                   // 50MHz clock signal
    .RESET_H,               // Active-high reset signal
    .FRAME_CLK(VGA_VS),     // VGA interface, added for animation
    .DrawX, .DrawY,         // VGA interface
    .KnightX, .KnightY,     // coordinate of the knight
    .MapConfig,             // MapConfig for current frame 
    .COLOR_ID(Sect0Color));


    // TODO: Add more port here
    attribute_table_drawer #(   
        .COOR(Sect1Coor),
        .SIZE(Sect1Size),    
        .TILE_WIDTH(TILE_WIDTH)
    ) attribute_instance(
        .CLK, 
        .RESET_H,
        .FRAME_CLK(VGA_VS),
        .DrawX, .DrawY,
        .ValueArr(AttributeTableValueArr),
        // .ValueArr({14'd0, 14'd1000, 14'd0, 14'd0, 14'd0}),
        .EnergyDone,      // one-hot 
        .EnergyProgress,
        .COLOR_ID(Sect1Color)
    );

    key_table_drawer #(.COOR(Sect2Coor), .SIZE(Sect2Size), .TILE_WIDTH(TILE_WIDTH)) 
    key_instance (.*, 
        .ValueArr(KeyTableValueArr), 
        .COLOR_ID(Sect2Color));
    
    frame_buffer_drawer frame_instance (.DrawX, .DrawY, .FB_DIN, .FB_ADDR, .COLOR_ID(FBColor));
        
    BackgroundController background_instance(.*, .COLOR_ID(BackgroundColor));


    
    logic [4:0] EnergyDone = 5'b00111;      // one-hot 
    logic [3:0] EnergyProgress = 4'd12;
    
    
endmodule
