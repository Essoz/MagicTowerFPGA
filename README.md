# MagicTowerFPGA
# ECE 385 Final Report

## Overview and Purpose

In this project, we tried to rebuild a classical RPG game "Magic Tower" on FPGA board. "Magic Tower" is a story for the knight to save the princess from the tower and protect the kingdom. In this game, the player can control the knight to move, collect item and fight with monsters. Although the overall design difficulty for the baseline is not really high, the game is flexible and can be extended to a version with more features with advanced difficulty level. In our implementation, we used two NIOS-II CPU on the board to control the keyboard detection and game internal logic. We also have a complex draw engine to show the figures located in different areas. To communicate between hardware and software, we have a simple interface to transfer data.

## Introduction - An Overview of Features

![logic-block-diagram](C:\discipline\ece385\ece385\final\logic-block-diagram.png

![image-20220106210559985](C:\Users\13982\AppData\Roaming\Typora\typora-user-images\image-20220106210559985.png)

***Tile-based display controllers for the game interface.*** 

  - 32x32 tiles with a 256-color system palette. The specific tiles to be displayed are based on a 11x11 array that is initiated and manipulated by our soc. 
  - Flexible & extendable string sprites implemented.
  - 3 frame animation supported.

***Framebuffer Displays for complex image drawing***

  - Implemented SGDMA interface to copy data from SDRAM to Framebuffer efficiently
  - Flexible Text drawing in both Simplified Chinese and English. The size of each font is adjustable.
  - Simple visual effects supported.
  - An 8-bit SRAM dual controller IP is implemented to provide access to two Avalon-MM master in one cycle (50MHz - 20ns). Access is switched to the draw engine in the first half cycle and to the SOC or DMA in the second half cycle. This IP enables us to build a framebuffer in SRAM.

***USB Keyboard support (single player)***

***Big Register File as Hardware & Software Interface***

- Receive data from software and pass them to the draw engine
- Update when there is any modification to the OCM

***Completely Implement Game Control Logic onto the Software (C code)***

- Easier to implement and read
- Game Extendable (e.g. If you want to add floors or add types of monsters, you just need to add data into game_data_constant.h and monster_data.h)



## The Draw Engine

### Overall Description

The draw engine is the most complex component of this game, mixing hardware and software designs. The software part contains code that copies image data from SDRAM using DMA engines to framebuffer and draws text on framebuffer. A SGDMA IP core is correctly connected to SDRAM and SRAM dual port controller (a self-implemented IP core). The hardware part contains, besides basic modules serving as the VGA interface (e.g. vgaclk, VGA controller), fixed function display controllers based on tiles and a modified color mapper that support color multiplexing. A 256-color system palette is used to save memory and convert 8-bit color to RGB888 encoding for VGA display.

### Fixed Function Drawers

Due to the need of our game, we have implemented the display of main game interface into three separate controllers, as indicated by the graph below.

![image-20220106221119853](C:\Users\13982\AppData\Roaming\Typora\typora-user-images\image-20220106221119853.png)

- General structures

  The three controllers have very similar structures. Each controller has a tile table based on on-chip memory to construct the display according to the data to be displayed. The display is purely data-driven. For example, the input to GameInterfaceController is simply a 11x11x8bit array that contains 121 mapIDs so that the controller can fetch the specific tile of a location using the mapID. Controllers that have animation support (GameInterfaceController and AttributeTableController) have internal state machines to switch between tile tables when needed. Controllers will output a 8bit color ID while the ColorMapper will choose between colorIDs based on current location to form the correct display.

- Translation Invariance

Each of these controllers know its size and position as will be placed on the 640x480 screen so as to calculate a relative coordinate system inside each controller. This way any sprites declared within a controller only need to know about the relative coordinate system inside that controller. Therefore, the controller can be moved freely as a whole on the global coordinate system without worrying about making sprites' locations incorrect.

- IO Specification

  > ***Name:*** GameInterfaceController
  >
  > ***Param:*** 
  >
  > \[1:0\]\[9:0\] COOR = {10'd32 , 10'd194},
  >
  > \[1:0\]\[9:0\] SIZE = {10'd352, 10'd352},
  >
  > ​                 TILE_WIDTH = 32
  >
  > ***Input:*** 
  >
  > ​                 CLK, RESET_H,
  >
  > ​                 FRAME_CLK,
  >
  > ​        \[9:0\] DrawX, DrawY,
  >
  > ​        \[3:0\] KnightX, KnightY,
  >
  > \[10:0\]\[10:0\]\[12:0\] MapConfig,
  >
  > ***Output:***
  >
  > ​         [7:0] COLOR_ID

  > ***Name:*** AttributeTableController
  >
  > ***Param:*** 
  >
  > \[1:0\]\[9:0\] COOR = {10'd32 , 10'd32},
  >
  > \[1:0\]\[9:0\] SIZE = {10'd192, 10'd160},
  >
  > ​                 TILE_WIDTH = 32
  >
  > ***Input:*** 
  >
  > ​                 CLK, RESET_H,
  >
  > ​                 FRAME_CLK,
  >
  > ​       \[9:0\] DrawX, DrawY,
  >
  > \[4:0\]\[13:0\] ValueArr,
  >
  > \[4:0\] EnergyDone,    // one-hot 
  >
  > \[3:0\] EnergyProgress,
  >
  > ***Output:***
  >
  > ​         [7:0] COLOR_ID


  > ***Name:*** KeyTableController
  >
  > ***Param:*** 
  >
  > \[1:0\]\[9:0\] COOR = {10'd254 , 10'd32},
  >
  > \[1:0\]\[9:0\] SIZE = {10'd128, 10'd160},
  >
  > ​                 TILE_WIDTH = 32
  >
  > ***Input:*** 
  >
  > ​                 CLK, RESET_H,
  >
  > ​                 FRAME_CLK,
  >
  > \[4:0\]\[13:0\] ValueArr,
  >
  > ​        \[9:0\] DrawX, DrawY,
  >
  > ***Output:***
  >
  > ​         [7:0] COLOR_ID

### Framebuffer

The complex interfaces of this game such as dialogue, shop and transition animations called for a framebuffer-based display. Since each framebuffer requires 300KiB for the 640x480 256 color display, we've chosen SRAM to hold our framebuffers. To meet the timing requirement, we have implemented a SRAM dual controller with 8-bit datawidth. We can emulate dual port behavior because access time(10ns) of the asynchronous SRAM chip is exactly the half of our system clock period (20ns). And the SRAM controller has 8-bit datawidth because of our 8-bit color encoding.

Apart from the SRAM dual controller, for the hardware side we need only one more simple module to perform memory-reads from SRAM. All the work of drawing on the framework are the responsibility of software and a SGDMA IP core.

Specifically, the software part code can carry out the following functionalities:

1. Fast-copying images to framebuffer by invoking SGDMA interface functions. The size and location can be specified by users. Using SGDMA, we are able to achieve up to 60 FPS animation.

1. Erase the framebuffer by copying empty data (all zeros) to framebuffer. "0" is a special color ID reserved for transparency control. If the framebuffer reads 0, color mapper will display the fixed function display layers which are below the framebuffer layer.
2. Extendable and Scalable Text drawing by directly writing to framebuffer from NIOS-II. (Note that the font data are retrieved from another project [zjui-ece385-final/chinese.c at master · xddxdd/zjui-ece385-final (github.com)](https://github.com/xddxdd/zjui-ece385-final/blob/master/ECE385_src/resources/chinese.c))

![image-20220106231941323](C:\Users\13982\AppData\Roaming\Typora\typora-user-images\image-20220106231941323.png)

 In this project, we had used this framebuffer to draw the welcome image as well as the gameover image. And all fixed texts (for example chinese characters in the Attribute Table) are drawn on framebuffer.

## Interface Between Hardware and Software

### Overall Description

In this part, we built a big register file resemble to AES register file in Lab9 to transmit data between hardware and software (In fact, data will only travel from Avalon Bus to the FPGA logic part). In order to get access to the Avalon Bus, we compressed this part into an IP block and added it to the Platform Designer. The data will be further used by draw engine to show the status, floor map and the player.

### The Alignment of Register File

In total, the draw engine needs the following information:

1. 11 * 11 bit-map of the current floor configuration
2. The X and Y position of the player
3. The Status of the player (Health, Attack, Defense, etc.)
4. The inventory of the player (Yellow Key, Blue Key, Red Key, Coin, etc.)

For convenience, we used 32-bit registers to store the information mentioned above (Even if some information needs only a few bits). The register configuration is shown below in details.

| Configuration of the 32-Bit Register File (Index starts from 0 at the top) |
| :----------------------------------------------------------: |
|                        Player_Status                         |
|                        Player_Health                         |
|                        Player_Attack                         |
|                        Player_Defense                        |
|                             EXP                              |
|                          Yellow_Key                          |
|                           Blue_Key                           |
|                           Red_Key                            |
|                             Coin                             |
|                        Special_Items                         |
|    11 * 11 Floor Config (121x 32-bit registers in total)     |
|                    Position X (Knight X)                     |
|                    Position Y (Knight Y)                     |

### Module Description of the Interface

>Module Inputs and Outputs:
>
><img src=".\Figures\Control-IP.png" alt="Control-IP" style="zoom: 33%;" />
>
>Description:
>
>​	Based on the register configuration shown above, it will do the following:
>
>	1. When the data from software is ready, it will copy them into the corresponding registers through AVL_WRITEDATA port
>	2. This module will export the data out to the top-level module for drawing.
>
>Purpose:
>
>​	This module is the interface between the software and the hardware for data transmission.

## Software Section

### Overall Description of the Software Section

In this section, we mainly wrote all the game data and game logic that is not trivial to implement with hardware. To have better performance, we allocated two NIOS-II CPU Cores. One is for keyboard I/O operations, the other is for game control logic. Basically, we stored the initial game data including the monster data, floor data, status data, etc. into the C files, and moved those data into the OCM at the beginning of execution for further modification and management. Then, in the main() function, the program receives the keycode and makes reactions to it. Finally, the software will pass the update to both the OCM and the interface register file.

### Description of C-code Files

>monster_data.h
>
>Description:
>
>​	Each monster type will be stored as a structure indicated as below:
>
><img src=".\Figures\Monster_Data.png" alt="Monster_Data" style="zoom:50%;" />
>
>With all the structures initiated, the pointer to each monster type will be arranged into a pointer list with a specific index. Those attributes will be helpful in battle() function. If the monster has Special skills, it will be activated during the battle.

>game_data_constants.h
>
>Description:
>
>​	This header file stores all the initial player status and floor configurations. The order of data coincides with the alignment of the register file in the interface.
>
>​	For the sequence of player status, we have the following order: {Status, Health, Attack, Defense, EXP, Yellow_Key, Blue_Key, Red_Key, Coin, Special_Items}. After this, we have a big array of floor configuration with size TOT_FLOOR_NUMBER * FLOOR_SIZE. During the execution, we will transfer them to OCM. To save the memory space in OCM, we will use 16-bits for one data entry. So the data type in this file is alt_16.

>main.c
>
>Description:
>
>​	This is the most important file in this project. It ensures the basic functionality of the game, including working, colliding, picking items, battle with monsters and so on. The general procedure is list as following:
>
>1. Initialize all the data to OCM (including the floor config, status, etc.)
>2. Draw all the texts and the cover picture on the screen
>3. When the user press "Enter", the game starts
>4. Send data to the Interface (IP block register file) and draw the floor config through hardware
>5. Receive USB keycode from the OCM which the other NIOS-II Core can also get access to
>6. Based on the keycode and the floor blocks surrounding the player, make the corresponding reactions
>7. Make updates to the status and floor config stored in the OCM
>8. Go back to Step 3

## Resources and Statistics Table

|        LUT        |       19392        |
| :---------------: | :----------------: |
|      **DSP**      |       **0**        |
|     **BRAM**      | **2,082,816 Bits** |
|   **Flip-Flop**   |      **9133**      |
|   **Frequency**   |   **24.28 MHz**    |
| **Static Power**  |   **110.85 mW**    |
| **Dynamic Power** |   **211.54 mW**    |
|  **Total Power**  |   **416.08 mW**    |

## Conclusion

### Restate the Design

In this project, we rebuilt the game "Magic Tower" on FPGA board. In our implementation, we used two NIOS-II CPUs on the board to control the keyboard detection and game internal logic. One CPU core gets data from EZ-OTG chip and stores it into OCM, while the other CPU core reads the keycode and copes with the internal game logic. Our game logic is completely implemented with C code, the player can walk, pick items, battle with monsters, etc.

We also have a complex draw engine to show the figures located in different areas. 

To communicate between hardware and software, we have a simple interface to transfer data. We use about 4000 registers on this interface to interchange the data.

This game is extremely extendable, due to the time limitation, we failed to implement the shop, the energy bar, the battle skills, the embedded games, etc. We plan to further explore this game and try to completely finish it in the future.

### The difficulty we met and how we overcome

The most severe trouble we met is that the complexity of interface we had at the beginning is too high. In the previous design, the position of the player is handled by hardware. The software needs this information to detect the block next to the player, making the relevant changes to the floor and status in the OCM, then transfer this data back to the hardware for drawing. This results several I/O operations within one frame cycle, which will cause problems in the timeline. We had a hard time debugging and finally we failed to demo on Dec. 31st.

Later, according to the suggestions from Professor Li, we move all the logics from hardware to the software. We only leave one register file to communicate between hardware and software. With this simpler design protocol, we can have higher efficiency to handle the internal game logic in software and better stability in hardware.
