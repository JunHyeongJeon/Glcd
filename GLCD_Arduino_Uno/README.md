#define glcdData0Pin        8
#define glcdData1Pin        9
#define glcdData2Pin        10
#define glcdData3Pin        11
#define glcdData4Pin        4
#define glcdData5Pin        5
#define glcdData6Pin        6
#define glcdData7Pin        7


#define glcdCSEL1        14
#define glcdCSEL2        15

#if NBR_CHIP_SELECT_PINS > 2
#define glcdCSEL3         3   // third chip select if needed

#if NBR_CHIP_SELECT_PINS > 3
#define glcdCSEL4         2   // fourth chip select if needed

#define glcdRW           16
#define glcdDI           17
#define glcdEN           18