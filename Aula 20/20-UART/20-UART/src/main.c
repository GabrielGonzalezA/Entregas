/**
 *	20-UART 
 * Prof. Rafael Corsi
 *
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 */

#include "asf.h"
#include "conf_board.h"
#include "conf_clock.h"
#include <string.h>

/************************************************************************/
/* Configurações                                                        */
/************************************************************************/

#define STRING_EOL    "\r"
#define STRING_VERSAO "-- "BOARD_NAME" --\r\n" \
					  "-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define CONF_UART_BAUDRATE 115200		
#define CONF_UART          CONSOLE_UART
#define tam 15

/** 
 * LEDs
 */ 
#define PIN_LED_BLUE	19
#define PORT_LED_BLUE	PIOA
#define ID_LED_BLUE		ID_PIOA
#define MASK_LED_BLUE	(1u << PIN_LED_BLUE)

#define PIN_LED_GREEN 20
#define PORT_LED_GREEN PIOA
#define ID_LED_GREEN	ID_PIOA
#define MASK_LED_GREEN	(1u << PIN_LED_GREEN)

#define PIN_LED_RED 20
#define PORT_LED_RED	PIOC
#define ID_LED_RED	ID_PIOC
#define MASK_LED_RED	(1u << PIN_LED_RED)


/************************************************************************/
/* prototipagem                                                                      */
/************************************************************************/

void limpvetor(uint8_t *vetor);
int lervetor(uint8_t *vetor);


/************************************************************************/
/* funcoes                                                                     */
/************************************************************************/
int lervetor(uint8_t *vetor)
{
	uint8_t i=0;
	limpvetor(vetor);
	for (i=0;i<tam;i++)
	{
		usart_serial_getchar((Usart *)CONSOLE_UART, (vetor+i));
		if (*(vetor+i) == '\n')
		{
			*(vetor+i) = 0x00;
			return i;
		}
		
	}
	return 0;
}

void limpvetor(uint8_t *vetor)
{
	uint8_t n;
	for(n=0;n<tam;n++)
	{
		*(vetor+n) = 0X00;
	}
}

/************************************************************************/
/* Configura UART                                                       */
/************************************************************************/
void config_uart(void){
	
	/* configura pinos */
	gpio_configure_group(PINS_UART0_PIO, PINS_UART0, PINS_UART0_FLAGS);
	
	/* ativa clock */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	
	/* Configuração UART */
	const usart_serial_options_t uart_serial_options = {
		.baudrate   = CONF_UART_BAUDRATE,
		.paritytype = UART_MR_PAR_NO,
		.stopbits   = 0
	};
	
	stdio_serial_init((Usart *)CONF_UART, &uart_serial_options);
}

/************************************************************************/
/* Display Menu                                                         */
/************************************************************************/
static void display_menu(void)
{
	puts(" 1 : exibe novamente esse menu \n\r"
		 " 2 : Ativa o LED  \n\r"
		 " 3 : Desliga o LED \n\r ");
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{
	uint8_t uc_key;
	uint8_t comd;
	uint8_t palavra[tam+1];
	

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure LED 1 */
	pmc_enable_periph_clk(ID_LED_BLUE);
	pio_set_output(PORT_LED_BLUE  , MASK_LED_BLUE	,1,0,0);
	/* Configure LED 2 */
	pmc_enable_periph_clk(ID_LED_GREEN);
	pio_set_output(PORT_LED_GREEN  , MASK_LED_GREEN	,1,0,0);
	/* Configure LED 3 */
	pmc_enable_periph_clk(ID_LED_RED);
	pio_set_output(PORT_LED_RED  , MASK_LED_RED	,1,0,0);

	pio_clear(PORT_LED_RED, MASK_LED_RED);
	/* Initialize debug console */
	config_uart();
	
	/* frase de boas vindas */
	puts(" ---------------------------- \n\r"
	 	 " Bem vindo terraquio !		\n\r"
		 " ---------------------------- \n\r");
		 
	/* display main menu */
	display_menu();

	limpvetor(&palavra);

	while (1) {

		comd=lervetor(&palavra);

		
		if (strcmp(palavra,"LigaAzul")==0)
		{
					pio_clear(PORT_LED_BLUE, MASK_LED_BLUE);
					puts("Led ON \n\r");
					
		}

		if (strcmp(palavra,"DesligaAzul")==0)
		{
			pio_set(PORT_LED_BLUE, MASK_LED_BLUE);
			puts("Led OFF \n\r");
			
		}
		

		if (strcmp(palavra,"LigaVerde")==0)
		{
					pio_clear(PORT_LED_GREEN, MASK_LED_GREEN);
					puts("Led ON \n\r");
					
		}
		
		if (strcmp(palavra,"DesligaVerde")==0)
		{
			pio_set(PORT_LED_GREEN, MASK_LED_GREEN);
			puts("Led OFF \n\r");
			
		}

		if (strcmp(palavra,"LigaVermelho")==0)
		{
					pio_set(PORT_LED_RED, MASK_LED_RED);
					puts("Led ON \n\r");
					
		}

		if (strcmp(palavra,"DesligaVermelho")==0)
		{
			pio_clear(PORT_LED_RED, MASK_LED_RED);
			puts("Led OFF \n\r");
			
		}
			/*usart_serial_getchar((Usart *)CONSOLE_UART, &uc_key);	
			switch (uc_key) {
				case '1':
					display_menu();
					break;
				case '2':
					pio_clear(PORT_LED_BLUE, MASK_LED_BLUE);
					puts("Led ON \n\r");
					break;
				case '3' :
					pio_set(PORT_LED_BLUE, MASK_LED_BLUE);
					puts("Led OFF \n\r");
					break;
				default:
					printf("Opcao nao definida: %d \n\r", uc_key);
					*/
	}
}
