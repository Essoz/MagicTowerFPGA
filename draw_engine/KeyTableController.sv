module key_table_drawer
#(
    parameter [1:0][9:0] COOR = {10'd254, 10'd32 },
    parameter [1:0][9:0] SIZE = {10'd128, 10'd160},
    parameter TILE_WIDTH = 32
)
(
    input  logic CLK,
    input  logic [9:0] DrawX, DrawY,
    input  logic [3:0][8:0] ValueArr, 
    output logic [7:0] COLOR_ID
);
    logic [9:0] posX;
    logic [9:0] posY; 
    logic [3:0] tileX;   
    logic [3:0] tileY;   
    logic [9:0] relPos;
    PostitionCalc #(.COOR(COOR), .TILE_WIDTH(TILE_WIDTH)) posCalc(.*);

    logic [7:0] TileID;
    always_comb begin
        case (tileX)
            7'd0:
                TileID = tileY;
            7'd1:
                TileID = 7'd5;
            default:
                TileID = 7'd4;
        endcase
    end

    logic [7:0] TILE_COLOR_ID;
    KeyTableTile keytabletile(.*, .COLOR_ID(TILE_COLOR_ID));

    logic [3:0] IsDigitArr;
    DigitLineSprite #(.COOR({10'd8  , 10'd102})) Key1  (.DrawX(posX), .DrawY(posY), .Value(ValueArr[0]), .IsDigit(IsDigitArr[0]));
    DigitLineSprite #(.COOR({10'd40 , 10'd102})) Key2  (.DrawX(posX), .DrawY(posY), .Value(ValueArr[1]), .IsDigit(IsDigitArr[1]));
    DigitLineSprite #(.COOR({10'd72 , 10'd102})) Key3  (.DrawX(posX), .DrawY(posY), .Value(ValueArr[2]), .IsDigit(IsDigitArr[2]));
    DigitLineSprite #(.COOR({10'd104, 10'd102})) Money (.DrawX(posX), .DrawY(posY), .Value(ValueArr[3]), .IsDigit(IsDigitArr[3]));
    
    assign COLOR_ID = (IsDigitArr[0] || IsDigitArr[1] || IsDigitArr[2] || IsDigitArr[3]) ? 8'd15 : TILE_COLOR_ID;
endmodule


module KeyTableTile (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [6 * 1024 - 1 : 0];

    initial
    begin
	 $readmemh("resource/keyTable.txt", tiles);
    end

    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*1024 + relPos];
    end 
endmodule
    