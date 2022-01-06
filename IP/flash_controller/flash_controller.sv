module flash_controller(
    input  logic        CLK,
    input  logic        RESET,
    
    // mode selection
    // input  logic        MODE,       // 0 for Avalon-MM access, 1 for Hardware Access
    
    // Avalon-MM Slave Interface
    input  logic        AVL_READ,           
    input  logic        AVL_WRITE,          // one can never        
    input  logic [22:0] AVL_ADDR,           // 23-bit address space 
    input  logic [7:0]  AVL_WRITEDATA,      // no need for this one actually
    input  logic        AVL_CE_N,
    input  logic        AVL_OE_N,
    output logic [7:0]  AVL_READDATA,       // 
    // Hardware Interface
    // input  logic [22:0] HW_ADDR,
    // output logic [7:0]  HW_DQ,     


    // FLASH Interface
    input  logic [7:0]  FL_DQ,        //FLASH Data
    input  logic        FL_RY,        //FLASH Ready
    output logic [22:0] FL_ADDR,      //FLASH Address
    output logic        FL_CE_N,      //FLASH Chip Enable
    output logic        FL_OE_N,      //FLASH Output Enable
    output logic        FL_WE_N,      //FLASH Write Enable
    output logic        FL_RESET_N,   //FLASH Hardware Reset
    output logic        FL_WP_N       //FLASH Hardware Write Protect
);

    always_comb begin
        FL_CE_N = AVL_CE_N;
        FL_OE_N = AVL_OE_N;
        FL_WE_N = 1;
        FL_WP_N = 1'bZ;
        FL_RESET_N = RESET;
        AVL_READDATA = FL_DQ;
    end

    always_ff @(posedge CLK) begin
        if (AVL_READ) begin            
            FL_ADDR <= AVL_ADDR;
        end
    end

endmodule