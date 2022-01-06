module PostitionCalc 
#(
    parameter [1:0][9:0] COOR = {10'd254, 10'd32 },
    parameter TILE_WIDTH = 32
)
(
    input  logic [9:0] DrawX, DrawY,
    output logic [9:0] posX,
    output logic [9:0] posY,
    output logic [3:0] tileX,
    output logic [3:0] tileY,
    output logic [9:0] relPos
);
    assign posX = DrawX - COOR[0];
    assign posY = DrawY - COOR[1];
    assign tileX = posX / TILE_WIDTH;
    assign tileY = posY / TILE_WIDTH;
    assign relPos = (posX - tileX * TILE_WIDTH) + (posY - tileY * TILE_WIDTH) * TILE_WIDTH;
endmodule    
    