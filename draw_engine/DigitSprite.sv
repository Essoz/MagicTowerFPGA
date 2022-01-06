module DigitSprite #(
    parameter [9:0] COOR_Y = {10'd8  },
    parameter [9:0] COOR_X = {10'd90 },
    parameter [1:0][9:0] SIZE = {10'd16 , 10'd8  }
) 
(
    input  logic [9:0] DrawX, DrawY,
    input  logic [3:0] Value,
    output logic       IsDigit 
);
    logic [9:0] posX;
    logic [9:0] posY;
    assign posX = DrawX - COOR_X;
    assign posY = DrawY - COOR_Y;

    logic [7:0] ROM_ADDR;
    logic [7:0] ROM_DATA;
    always_comb begin
        IsDigit = 0;
        ROM_ADDR = 0;
        if (posX >= 0 && posX < SIZE[0] && posY >= 0 && posY < SIZE[1])
            ROM_ADDR = (Value + 1) * SIZE[1] + posY;
            IsDigit = ROM_DATA[SIZE[0] - posX - 1];
    end
    DigitFontRom digitFontRom(.addr(ROM_ADDR), .data(ROM_DATA));
endmodule
