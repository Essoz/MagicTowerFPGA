module BackgroundController (
    input logic CLK,
    input logic [9:0] DrawX, DrawY,
    output logic [7:0] COLOR_ID
);
    // How to get access to display memory?

/*
    Tile size = 32 x 32
    total size = 352 * 352
    Give coordinate of the point, the module access memory, tries to calculate the specific tile this pixel belongs to
 */ 
    logic [7:0] TILE_COLOR_ID;
    logic IsDigit;

    logic [9:0] relPos;
    assign relPos = DrawX % 32 + (DrawY % 32) * 32;

    assign COLOR_ID = IsDigit ? 8'd15 : TILE_COLOR_ID;
    
    BackgroundTile backgroundTile(.*, .COLOR_ID(TILE_COLOR_ID));
//    DigitSprite #(.COOR_Y =({10'd10  }, .COOR_X = {10'd400 }) digitSprite(.DrawX, .DrawY, .Value(FloorNum), .IsDigit);
endmodule


module BackgroundTile (
    input  logic       CLK,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [1024 - 1 : 0];

    initial
    begin
	 $readmemh("resource/background.txt", tiles);
    end

    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[relPos];
    end 
endmodule