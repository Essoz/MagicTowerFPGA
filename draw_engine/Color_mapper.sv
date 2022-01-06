// no clock is necessary for this module
module color_mapper 
#(
    parameter [1:0][9:0] Sect0Coor = {10'd32 , 10'd194},
    parameter [1:0][9:0] Sect1Coor = {10'd32 , 10'd32 },
    parameter [1:0][9:0] Sect2Coor = {10'd254, 10'd32 },
    parameter [1:0][9:0] Sect0Size = {10'd352, 10'd352},
    parameter [1:0][9:0] Sect1Size = {10'd192, 10'd130},
    parameter [1:0][9:0] Sect2Size = {10'd130, 10'd130}
)
(
    input  logic       VGA_CLK,
    input  logic [9:0] DrawX, DrawY,
    output logic [7:0] VGA_R, VGA_G, VGA_B,

    input  logic [7:0] Sect0Color,         // Game Interface
    input  logic [7:0] Sect1Color,         // Attribute Table
    input  logic [7:0] Sect2Color,         // Key Table

    input  logic [7:0] BackgroundColor,
    // input  logic []
    input  logic       IsFBTransparent,
    input  logic [7:0] FBColor    // input from framebuffer controller
);

logic [7:0] Red, Green, Blue;
logic [4:0][7:0] COLOR_IDs;
logic [2:0][7:0] COLORs;
logic [2:0] SectionSelect; 

assign VGA_R = Red;
assign VGA_G = Green;
assign VGA_B = Blue;


assign COLOR_IDs[0] = Sect0Color;
assign COLOR_IDs[1] = Sect1Color;
assign COLOR_IDs[2] = Sect2Color;    
assign COLOR_IDs[3] = BackgroundColor;
assign COLOR_IDs[4] = FBColor;
/*TODO: 1. Later Parametrize those configurations
        2. Finalize the numbers
 */


// TODO: Add transparency support
always_comb begin : assignColor

    if (COLOR_IDs[4] != 1'b0 && IsFBTransparent) 
        SectionSelect = 3'd4;
    else if (Sect0Coor[0] <= DrawX && DrawX < Sect0Coor[0] + Sect0Size[0]
      && Sect0Coor[1] <= DrawY && DrawY < Sect0Coor[1] + Sect0Size[1]) 
        // in section0 (Game Interface)
        SectionSelect = 3'd0;
    else if (Sect1Coor[0] <= DrawX && DrawX < Sect1Coor[0] + Sect1Size[0] 
      && Sect1Coor[1] <= DrawY && DrawY < Sect1Coor[1] + Sect1Size[1])
        // in section1 (Attribute Table)
        SectionSelect = 3'd1;
    else if (Sect2Coor[0] <= DrawX && DrawX < Sect2Coor[0] + Sect2Size[0] 
      && Sect2Coor[1] <= DrawY && DrawY < Sect2Coor[1] + Sect2Size[1])
        // in section2 (Keys Table)
        SectionSelect = 3'd2;
    else 
        // in background
        SectionSelect = 3'd3;
    

    Red = COLORs[2];
    Green = COLORs[1];
    Blue = COLORs[0];
end

system_palette palette1(.CLK(VGA_CLK), .COLOR_ID(COLOR_IDs[SectionSelect]), .RGB888(COLORs));

endmodule

module system_palette(
    input  logic CLK,
    input  logic [7:0] COLOR_ID,
    output logic [2:0][7:0] RGB888

    // use on-chip memory
);

    logic [0:23] palette [255:0];

    initial
    begin
        $readmemh("resource/palette.txt", palette);
    end

    always_ff @(posedge CLK) begin
        RGB888 <= palette[COLOR_ID];
    end

endmodule
