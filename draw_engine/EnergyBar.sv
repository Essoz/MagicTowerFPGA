module EnergyBar 
#(
    parameter [1:0][9:0] COOR = {10'd160, 10'd64 },
    parameter [1:0][9:0] SIZE = {10'd32 , 10'd60 },
    parameter TILE_WIDTH = 12
)
(
    input  logic CLK, RESET_H,
    input  logic FRAME_CLK,
    input  logic [9:0] DrawX, DrawY,
    input  logic [4:0] EnergyDone,      // one-hot 
    input  logic [3:0] EnergyProgress,
    output logic isEnergyBar,
    output logic [7:0] COLOR_ID
); 
    always_comb begin
        isEnergyBar = 0;
        if (DrawX >= COOR[0] && DrawX <= COOR[0] + SIZE[0] 
            && DrawY >= COOR[1] && DrawY <= COOR[1] + SIZE[1])
            isEnergyBar = COLOR_ID == 8'b0 ? 0 : 1;
        
    end

    logic [9:0] posX;
    logic [9:0] posY; 
    logic [3:0] tileX;   
    logic [3:0] tileY;   
    logic [9:0] relPos;
    PostitionCalc #(.COOR(COOR), .TILE_WIDTH(TILE_WIDTH)) posCalc(.*);

    
    logic [2:0][7:0] COLOR_ID_FRAME;
    logic [7:0] COLOR_ID_DRAW;


    always_comb begin
        if (tileY == 0) begin
            COLOR_ID = COLOR_ID_FRAME[frameSelect];
        end        
        else begin
            COLOR_ID = COLOR_ID_DRAW;
        end
    end

    localparam progressBarY_top    = 9'd14;
    localparam progressBarY_bottom = 9'd24;
    localparam borderWidth         = 9'd1;
    localparam granularity         = SIZE[0] / 16;
    logic [9:0] progress;

    always_comb begin : progressBar
        COLOR_ID_DRAW = 8'd0;
        progress = EnergyProgress * granularity;
    
        if (posY >= progressBarY_top && posY <= progressBarY_bottom && posX <= progress) 
            COLOR_ID_DRAW = 8'd153;

        if ((posY <= progressBarY_top && posY >= progressBarY_top - borderWidth) 
        || (posY >= progressBarY_bottom && posY <= progressBarY_bottom + borderWidth) )
            COLOR_ID_DRAW = 8'd135;
        if (posY >= progressBarY_top && posY <= progressBarY_bottom && (posX <= borderWidth || posX >= SIZE[0] - borderWidth))
            COLOR_ID_DRAW = 8'd135;

    end


    logic [1:0] frameSelect, frameSelect_in;
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
        if (counter >= 4'd4) begin
            counter_in = 4'd0;
            frameSelect_in = frameSelect + 1;
        end
        if (frameSelect == 2'd3) begin
            frameSelect_in = 2'd0;
        end
    end

    EnergyBarTile0 energyTile0 (.*, .TileID(EnergyDone[tileX]), .COLOR_ID(COLOR_ID_FRAME[0]));
    EnergyBarTile1 energyTile1 (.*, .TileID(EnergyDone[tileX]), .COLOR_ID(COLOR_ID_FRAME[1]));
    EnergyBarTile2 energyTile2 (.*, .TileID(EnergyDone[tileX]), .COLOR_ID(COLOR_ID_FRAME[2]));

endmodule

module EnergyBarTile0 (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [2 * 144 - 1 : 0];

    initial
    begin
	 $readmemh("resource/light0.txt", tiles);
    end

    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*144 + relPos];
    end 


endmodule

module EnergyBarTile1 (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [2 * 144 - 1 : 0];

    initial
    begin
	 $readmemh("resource/light1.txt", tiles);
    end

    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*144 + relPos];
    end 


endmodule

module EnergyBarTile2 (
    input  logic       CLK,
    input  logic [7:0] TileID,
    input  logic [9:0] relPos, 
    output logic [7:0] COLOR_ID
);
    logic [7:0] tiles [2 * 144 - 1 : 0];

    initial
    begin
	 $readmemh("resource/light2.txt", tiles);
    end

    always_ff @ (posedge CLK) begin
        COLOR_ID <= tiles[TileID*144 + relPos];
    end 


endmodule