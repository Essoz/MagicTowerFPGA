module DigitLineSprite #(
    parameter [1:0][9:0] COOR = {10'd16, 10'd60},
    parameter NUM_DIGIT = 3
) 
(
    input  logic [9:0] DrawX, DrawY,
    input  logic [$clog2(10**NUM_DIGIT) - 1:0] Value,
    output logic IsDigit
);

    localparam [1:0][9:0] DIGIT_SIZE = {10'd16, 10'd8};

    logic [NUM_DIGIT - 1:0][3:0] ValueArr;
    logic [NUM_DIGIT - 1:0] IsDigitArr;
    logic [$clog2(NUM_DIGIT) - 1:0] CurrDigit; 
    integer j;
    always_comb begin
        IsDigit = IsDigitArr[NUM_DIGIT - CurrDigit - 1];
        CurrDigit = (DrawX - COOR[0]) / DIGIT_SIZE[0];

            for(j = 0; j < NUM_DIGIT; j = j + 1)
                begin   : SetDigit
                        ValueArr[j] = Value / (10**j) % 10;  
                end

        // for(j = NUM_DIGIT - 1; j > 0; j = j - 1)
        //     begin   : SetNullDigit
        //             ValueArr[j] = ValueArr[j] != 0 ? ValueArr[j] : 4'hf;
        //     end
        
    end

    // generate from HIGHER digit to LOWER digit
    genvar i;
    generate 
        for(i = 0; i < NUM_DIGIT; i = i + 1)
            begin : GenerateDigitSprite
        DigitSprite #(.COOR_Y(COOR[1]), .COOR_X(COOR[0] + i * DIGIT_SIZE[0])) digitSprite (.*, .Value(ValueArr[NUM_DIGIT - i - 1]), .IsDigit(IsDigitArr[NUM_DIGIT - i - 1]));
            end
    endgenerate

endmodule