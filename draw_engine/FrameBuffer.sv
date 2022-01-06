module frame_buffer_drawer(
    input  logic [9:0] DrawX, DrawY,
    input  logic [7:0] FB_DIN,
    output logic [20:0] FB_ADDR,
    output logic [7:0] COLOR_ID 
);
localparam WIDTH = 640;
localparam HEIGHT = 480;

always_comb begin
    FB_ADDR = 21'bx;
    if (DrawX < WIDTH && DrawY < HEIGHT) begin
        FB_ADDR = DrawX + DrawY * WIDTH;
    end
end

assign COLOR_ID = FB_DIN;
endmodule

