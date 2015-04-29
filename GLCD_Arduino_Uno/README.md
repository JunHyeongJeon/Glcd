glcdData0Pin        8
glcdData1Pin        9
glcdData2Pin        10
glcdData3Pin        11
glcdData4Pin        4
glcdData5Pin        5
glcdData6Pin        6
glcdData7Pin        7

glcdCSEL1        14
glcdCSEL2        15

if NBR_CHIP_SELECT_PINS > 2
   glcdCSEL3         3   // third chip select if needed

else if NBR_CHIP_SELECT_PINS > 3
        glcdCSEL4         2   // fourth chip select if needed

glcdRW           16
glcdDI           17
glcdEN           18
