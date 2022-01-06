module attribute_table_drawer
#(
    parameter [1:0][9:0] COOR = {10'd32 , 10'd32 },
    parameter [1:0][9:0] SIZE = {10'd192, 10'd160},
    parameter TILE_WIDTH = 32
)
(
    input  logic CLK, RESET_H,
    input  logic FRAME_CLK,
    input  logic [9:0] DrawX, DrawY,
    input  logic [4:0][13:0] ValueArr,
    input  logic [4:0] EnergyDone,      // one-hot 
    input  logic [3:0] EnergyProgress,
    output logic [7:0] COLOR_ID
);
    logic [1:0][7:0] TILE_COLOR_IDs;
    logic [7:0] TILE_COLOR_ID; 

    logic [9:0] posX;
    logic [9:0] posY; 
    logic [3:0] tileX;   
    logic [3:0] tileY;   
    logic [9:0] relPos;
    PostitionCalc #(.COOR(COOR), .TILE_WIDTH(TILE_WIDTH)) posCalc(.*);

    logic [7:0] TileID;
    always_comb begin
        TileID = 8'd3;
        if (tileY == 0) begin
            if (tileX == 3'd0) 
                TileID = 8'd0;
            else if (tileX == 3'd3)
                TileID = 8'd1;
            else if (tileX == 3'd4)  
                TileID = 8'd2;
        end
    end


    logic isEnergyBar;
    AttributeTableTile attributeTable(.*, .COLOR_ID(TILE_COLOR_IDs[0]));
    EnergyBar energyBar(.*, .DrawX(posX), .DrawY(posY), .COLOR_ID(TILE_COLOR_IDs[1]));

    assign TILE_COLOR_ID = TILE_COLOR_IDs[isEnergyBar];

    logic [4:0] IsDigitArr;
    genvar i;
    generate
        for (i = 0; i < 5; i = i + 1)
        begin : GenerateAttributeDigit 
            DigitLineSprite #(.COOR({10'd37 + 25 * i , 10'd102}), .NUM_DIGIT(4)) AttributeDigit (.DrawX(posX), .DrawY(posY), .Value(ValueArr[i]), .IsDigit(IsDigitArr[i]));
        end
    endgenerate
    assign COLOR_ID = (IsDigitArr[0] || IsDigitArr[1] || IsDigitArr[2] || IsDigitArr[3] || IsDigitArr[4]) ? 8'd15 : TILE_COLOR_ID;

endmodule

module AttributeTableTile (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [4 * 1024 - 1 : 0];

    initial
    begin
	 $readmemh("resource/attributeTable.txt", tiles);
    end

    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*1024 + relPos];
    end 
endmodule



