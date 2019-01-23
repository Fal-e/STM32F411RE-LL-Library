/*
 * GPIO_Driver.h
 *
 *  Created on: 7Dec.,2018
 *      Author: Falcon
 */

#ifndef GPIO_DRIVER //name of the header file
#define GPIO_DRIVER


#include "stm32f4xx.h"

//PORT NAMES
#define PORTA 	GPIOA
#define PORTB 	GPIOB
#define PORTC 	GPIOC
#define PORTD 	GPIOD
#define PORTE 	GPIOE
#define PORTF 	GPIOF
#define PORTG 	GPIOG



//PIN "MODE" -- GPIO MODER
#define INPUT_MODE 	((uint32_t) 0x00)
#define OUTPUT_MODE ((uint32_t) 0x01) //General Purpose Output Mode
#define ALT_MODE 	((uint32_t) 0x02)
#define ANALOG_MODE ((uint32_t) 0x03)

//INPUT "MODE_TYPE"
// ---nothing here


//OUTPUT "MODE_TYPE" --GPIO OTYPER
#define OUTPUT_PUP 	((uint16_t) 0x00) // By default, when you set a pin for output via OUTPUT_MODE, it is already set as push-pull because by default the pins are 0. So no need to use this.
#define OUTPUT_OD 	((uint16_t) 0x01)


//OUTPUT "SPEED" --GPIO OSPEEDR
#define SPEED_LOW 		((uint32_t) 0x00)
#define SPEED_MEDIUM 	((uint32_t) 0x01)
#define SPEED_HIGH 		((uint32_t) 0x02)
#define SPEED_V_HIGH 	((uint32_t) 0x03)

// Input/Output Pull-up/Pull down "Pull" --GPIO PUPDR
#define NO_PULL ((uint32_t) 0x00)
#define PULL_UP ((uint32_t) 0x01)
#define PULL_DOWN ((uint32_t) 0x02)


//PORT PULL-UP/PULL-DOWN   --GPIO port pull-up/pull-down register (GPIOx_PUPDR)
#define PORT_NOPULL 	((uint32_t) 0x00)
#define PORT_PULLUP 	((uint32_t) 0x01)
#define PORT_PULLDOWN 	((uint32_t) 0x02)


//ENABLE CLOCK

#define GPIO_CLOCK_ENABLE_PORTA (RCC->AHB1ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTB (RCC->AHB1ENR |= (1<<1))
#define GPIO_CLOCK_ENABLE_PORTC (RCC->AHB1ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTD (RCC->AHB1ENR |= (1<<3))
//MORE PORTS CAN BE ADDED
//#define GPIO_CLOCK_ENABLE_ALT_FUNC (RCC->AHB1ENR |= ())


//ALTERNATE FUNCTIONS
#define AF0 	((uint32_t) 0x00)
#define AF1 	((uint32_t) 0x01)
#define AF2 	((uint32_t) 0x02)
#define AF3 	((uint32_t) 0x03)
#define AF4 	((uint32_t) 0x04)
#define AF5 	((uint32_t) 0x05)
#define AF6 	((uint32_t) 0x06)
#define AF7 	((uint32_t) 0x07)
#define AF8 	((uint32_t) 0x08)
#define AF9 	((uint32_t) 0x09)
#define AF10 	((uint32_t) 0x0A)
#define AF11 	((uint32_t) 0x0B)
#define AF12 	((uint32_t) 0x0C)
#define AF13 	((uint32_t) 0x0D)
#define AF14 	((uint32_t) 0x0E)
#define AF15 	((uint32_t) 0x0F)





typedef struct
{
	GPIO_TypeDef *port;

	uint32_t pin;

	uint32_t mode;

	uint32_t mode_type; //output mode type

	uint32_t pull;

	uint32_t speed;

	uint32_t alt_func;


}GPIO_TYPE;


typedef enum // To make coding more intelligible, it is useful to replace integers such as 1,2,3,etc with meaningful names.
{
RISING_EDGE,
FALLING_EDGE,
RISING_FALLING_EDGE
}edge_select; //edge select typedef



//Function Prototypes
//**********************************************************************
//			GPIO CONFIGURATION

//static void config_pin (GPIO_TypeDef *port , uint32_t pinNumber , uint32_t mode_type);
static void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode, uint16_t mode_type, uint32_t alt_func);




// GIO USER PIN FUNCTIONS

void gpio_init(GPIO_TYPE gpio_type);
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state);



void gpio_port_config(GPIO_TYPE gpio_type, int myPins[], int numPins); //Configuring input/output/alternate functions of a port

void gpio_port_set(GPIO_TypeDef *port, uint32_t pins); // Setting multiple pins of a port
void gpio_port_clear(GPIO_TypeDef *port, uint32_t pins); // Clearing multiple pins of a port




//****************************************************************************************
//						INTERRUPT FUNCTIONS


void gpio_interrupt_configure(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge);
void gpio_interrupt_enable(uint32_t pinNumber, IRQn_Type irqNumber);
void gpio_interrupt_clear(uint32_t pinNumber);





//void gpio_configure_interrupt(uint16_t pinNumber, int_edge_sel_t edge_sel);
/**
 * @brief Enable the interrupt for a given pin number and irq number
  @param pinNumber : GPIO pin number
 * @param irq_no : irq_number to be enabled in NVIC
 * @retval None
 */

//void gpio_enable_interrupt(uint16_t pinNumber, IRQn_Type irq_no);




//void gpio_clear_interrupt(uint16_t pin);







//HOW TO USE - set multiple inputs, outputs, alternate, etc

/* GPIO_TYPE myGPIO;
myGPIO.port = PORTA;
myGPIO.mode = OUTPUT_MODE;
int myArray[3]= {1,2,3};
gpio_port_io(myGPIO,3,myArray); */

//Above we have configured pins 1, 2 and 3 as outputs.

#endif /* GPIO_DRIVER_H_ */












