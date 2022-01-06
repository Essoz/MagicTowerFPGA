
module game_interface_drawer 
#(
    parameter [1:0][9:0] COOR = {10'd32 , 10'd194},
    parameter [1:0][9:0] SIZE = {10'd352, 10'd352},
    parameter TILE_WIDTH = 32
)

(
    input logic CLK, RESET_H,
    input logic FRAME_CLK,
    input logic [9:0] DrawX, DrawY,
    input logic [3:0] KnightX, KnightY,
    input logic [10:0][10:0][12:0] MapConfig,
    output logic [7:0] COLOR_ID

    // input logic [1:0][9:0] COOR,
    // input logic [1:0][9:0] SIZE
);
    // How to get access to display memory?
//    assign Colors = {8'hff, 8'h99, 8'hsff};
    logic isKnight;
    logic [1:0][7:0] COLOR_IDs;

    
    logic [9:0] posX;
    logic [9:0] posY; 
    logic [3:0] tileX;   
    logic [3:0] tileY;   
    logic [9:0] relPos;
    PostitionCalc #(.COOR(COOR), .TILE_WIDTH(TILE_WIDTH)) posCalc(.*);

    AnimationTile animation(.*, .ANIMATION_EN(1), .TileID(MapConfig[tileY][tileX]), .relPos, .COLOR_ID(COLOR_IDs[0]));
    KnightMovement knightmovement(.*, .ANIMATION_EN(1), .relPos, .COLOR_ID(COLOR_IDs[1]));

    assign COLOR_ID = COLOR_IDs[isKnight];
	 
    always_comb begin
        isKnight = 0;
        if (tileX == KnightX && tileY == KnightY && COLOR_IDs[1] != 8'd0)
            isKnight = 1;
    end
endmodule

module AnimationTile  (
    input  logic       CLK,
    input  logic       FRAME_CLK,
    input  logic       ANIMATION_EN,
    input  logic       RESET_H,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos,
    output logic [7:0] COLOR_ID
);
    logic [1:0][7:0] COLOR_ID_FRAME;
    logic frameSelect, frameSelect_in;
    logic [5:0] counter, counter_in;

    always_ff @(posedge FRAME_CLK) begin
        if (RESET_H) begin
            counter <= 4'b0;
            frameSelect <= 0;
        end
        else begin
            counter <= counter_in;
            frameSelect <= frameSelect_in;
        end
    end

    always_comb begin 
        counter_in = counter + 4'd1;
        frameSelect_in = frameSelect;
        if (counter >= 4'd15) begin
            counter_in = 4'd0;
            frameSelect_in = !frameSelect_in;
        end
    end
    

    assign COLOR_ID = ANIMATION_EN ? COLOR_ID_FRAME[frameSelect] : COLOR_ID_FRAME[0];

    Tile1 frame1_inst(.*, .COLOR_ID(COLOR_ID_FRAME[0]));
    Tile2 frame2_inst(.*, .COLOR_ID(COLOR_ID_FRAME[1]));
endmodule

module Tile1 (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [28 * 1024 - 1 : 0];

    initial
    begin
	 $readmemh("resource/tiles1.txt", tiles);
    end


    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*1024 + relPos];
    end 
endmodule

module Tile2 (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [28 * 1024 - 1 : 0];

    initial
    begin
	 $readmemh("resource/tiles2.txt", tiles);
    end


    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*1024 + relPos];
    end 
endmodule

module KnightMovement(
    input  logic       CLK, RESET_H,
    input  logic       FRAME_CLK,
    input  logic       ANIMATION_EN,
    input  logic [3:0] KnightX, KnightY,
    input  logic [9:0] relPos,
    output logic [7:0] COLOR_ID
);
    logic [1:0] up       = 2'd0;
    logic [1:0] down     = 2'd1;
    logic [1:0] left     = 2'd2;
    logic [1:0] right    = 2'd3;

    logic [3:0] KnightX_prev, KnightY_prev, KnightX_now, KnightY_now;
    logic [1:0][7:0] COLOR_ID_FRAME;
    logic frameSelect, frameSelect_in;
    logic [5:0] counter, counter_in;
    logic [1:0] direction, direction_prev;
	 
    always_ff @(posedge FRAME_CLK) begin
        if (RESET_H) begin
            counter <= 4'b0;
            frameSelect <= 1'b0;
            direction_prev <= 2'b0;
        end
        else begin
            counter <= counter_in;
            frameSelect <= frameSelect_in;
            direction_prev <= direction;
        end

        KnightX_now <= KnightX;
        KnightX_prev <= KnightX_now;
        KnightY_now <= KnightY;
        KnightY_prev <= KnightY_now;
        
    end

    always_comb begin 
        frameSelect_in = frameSelect;
        counter_in = 6'd0;
        direction = direction_prev;
        if (counter >= 6'd15) begin
            counter_in = 6'd0;
        end
        
        unique case (frameSelect)
            0: begin
                if (KnightX_now != KnightX_prev || KnightY_now != KnightY_prev) begin
                    frameSelect_in = 1;
                    counter_in = counter + 6'd1;
                end
            end 
            1: begin
                counter_in = counter + 6'd1;
                if (counter == 6'd15) begin 
                    frameSelect_in = 0;
                end
                if (KnightX_now != KnightX_prev || KnightY_now != KnightY_prev) begin
                        frameSelect_in = 1;                
                end
            end
        endcase

        if (KnightX_now != KnightX_prev || KnightY_now != KnightY_prev) begin
            if (KnightX_now < KnightX_prev && KnightY_now == KnightY_prev) begin 
                direction = left;
            end
            else if (KnightX_now > KnightX_prev && KnightY_now == KnightY_prev) begin
                direction = right;            
            end
            else if (KnightX_now == KnightX_prev && KnightY_now < KnightY_prev) begin
                direction = up;
            end
            if (KnightX_now == KnightX_prev && KnightY_now > KnightY_prev) begin
                direction = down; 
            end
        end

    end
    

    assign COLOR_ID = ANIMATION_EN ? COLOR_ID_FRAME[frameSelect] : COLOR_ID_FRAME[0];

    KnightTile1 knight1(.*, .TileID(direction), .COLOR_ID(COLOR_ID_FRAME[0]));
    KnightTile2 knight2(.*, .TileID(direction), .COLOR_ID(COLOR_ID_FRAME[1]));
endmodule

module KnightTile1 (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [4 * 1024 - 1 : 0];

    initial
    begin
	 $readmemh("resource/Knight1.txt", tiles);
    end


    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*1024 + relPos];
    end 
endmodule

module KnightTile2 (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [4 * 1024 - 1 : 0];

    initial
    begin
	 $readmemh("resource/Knight2.txt", tiles);
    end


    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*1024 + relPos];
    end 
endmodule