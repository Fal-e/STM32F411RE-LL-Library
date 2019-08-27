# STM32F411RE-LL-Library
Simple Low Level Library for STM32F411RE Microcontroller by Suad Shahini

Developed a library for the STM32F411RE microcontroller which contains functions for: GPIO, I2C, Timer (delay function), LCD 4 bit, 8 bit and LCD I2C. Bare-metal programming was used to develop the libraries.
    
   To see the custom libraries:
   Open GPIO_Driver folder -> Open "User Library" folder
   
   To see how some of the functions from the library are used:
   Open "GPIO_Driver" folder -> Open "User Application" Folder -> Open "main.c"
   
   Example in the main.c file shows how to set the microcontroller clock frequency to 50 MHz, set up pins, set up I2C and ADC.
   What does it do? An ADC is used to read the voltage output of a potentiometer and display via I2C to an LCD.
   
   
   Needed: Potentiometer and 16x02 LCD with I2C module
   
   Connections: Connect voltage output of a potentiomer to PORT C Pin 0 
                Connect I2C pins to the microcontroller. Connect pin 6 (SCL) and pin 7 (SDA) to PORT B
                
                
 
