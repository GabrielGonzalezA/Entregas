/**
 * IMT - Rafael Corsi
 * 
 * PIO - 07
 *  Configura o PIO do SAM4S (Banco A, pino 19) para operar em
 *  modo de output. Esse pino está conectado a um LED, que em 
 *  lógica alta apaga e lógica baixa acende.
*/

#include <asf.h>

//#include "Driver/pmc_maua.h"
//#include "Driver/pio_maua.h"
/*
 * Prototypes
 */

/** 
 * Definição dos pinos
 * Pinos do uC referente aos LEDS.
 *
 * O número referente ao pino (PIOAxx), refere-se ao
 * bit que deve ser configurado no registrador para alterar
 * o estado desse bit específico.
 *
 * exe : O pino PIOA_19 é configurado nos registradores pelo bit
 * 19. O registrador PIO_SODR configura se os pinos serão nível alto.
 * Nesse caso o bit 19 desse registrador é referente ao pino PIOA_19
 *
 * ----------------------------------
 * | BIT 19  | BIT 18  | ... |BIT 0 |
 * ----------------------------------
 * | PIOA_19 | PIOA_18 | ... |PIOA_0|
 * ----------------------------------
 */
#define PIN_LED_BLUE 19
#define PIN_LED_GREEN 20
#define PIN_LED_RED 20
#define PIN_BOTAO 3
#define MASK_BOTAO (1 << PIN_BOTAO)



/**
 * Main function
 * 1. configura o clock do sistema
 * 2. desabilita wathdog
 * 3. ativa o clock para o PIOA
 * 4. ativa o controle do pino ao PIO
 * 5. desabilita a proteção contra gravações do registradores
 * 6. ativa a o pino como modo output
 * 7. coloca o HIGH no pino
 */

int main (void)
{
	
	/**
	* Inicializando o clock do uP
	*/
	sysclk_init();
	
	/** 
	*  Desabilitando o WathDog do uP
	*/
	WDT->WDT_MR = WDT_MR_WDDIS;
		
	// 29.17.4 PMC Peripheral Clock Enable Register 0
	// 1: Enables the corresponding peripheral clock.
	// ID_PIOA = 11 - TAB 11-1
	//_pmc_enable_clock_periferico(ID_PIOA);
	//_pmc_enable_clock_periferico(ID_PIOC);
	
	//ativar o resgistrador responsavel por ativar o clock do periferico a e o b 
	
	PMC->PMC_PCER0 = 1 << ID_PIOA;
	PMC->PMC_PCER0 = 1 << ID_PIOB;
	PMC->PMC_PCER0 = 1 << ID_PIOC;
	
	//31.6.1 PIO Enable Register
	// 1: Enables the PIO to control the corresponding pin (disables peripheral control of the pin).
	
	//faz os re4gistradores controlar os leds 
		
	PIOA->PIO_PER = (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN );
	PIOC->PIO_PER = (1 << PIN_LED_RED );
	
	// 31.6.46 PIO Write Protection Mode Register
	// 0: Disables the write protection if WPKEY corresponds to 0x50494F (PIO in ASCII).
	PIOA->PIO_WPMR = 0;
	PIOC->PIO_WPMR = 0;
	// 31.6.4 PIO Output Enable Register
	// value =
	//	 	1 : Enables the output on the I/O line.
	//	 	0 : do nothing
	PIOA->PIO_OER =  (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN );
	PIOC->PIO_OER =  (1 << PIN_LED_RED );
	// 31.6.10 PIO Set Output Data Register
	// value = 
	// 		1 : Sets the data to be driven on the I/O line.
	// 		0 : do nothing
	PIOA->PIO_SODR = (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN );
	PIOC->PIO_SODR = (1 << PIN_LED_RED );
	
	/*
	*BOTAO
	*/
	//
	PIOB->PIO_PER = MASK_BOTAO;
	//desativa o bufer
	PIOB->PIO_ODR = MASK_BOTAO;
	//ativar pull-up
	PIOB->PIO_PUER = MASK_BOTAO;
	// utilizando o debouncing
	PIOB->PIO_IFER = MASK_BOTAO;
	// ativando clock do debouncing
	PIOB->PIO_IFSCER = MASK_BOTAO;
	// tempo do clock - metade do clock do sistema -- td=(PIO_SCDR + 1)*2tsys
	PIOB->PIO_SCDR = 2;
	
	
	
	
	
	/**
	*	Loop infinito
	*/
		while(1){
			if((PIOB->PIO_PDSR & MASK_BOTAO)>0)
			{
				
				PIOA->PIO_SODR =  (1 << PIN_LED_BLUE ); //led azul apaga
				PIOC->PIO_CODR =  (1 << PIN_LED_RED ); //led red apaga
				PIOA->PIO_SODR =  (1 << PIN_LED_GREEN ); //led verde apaga         
			}
			
			else
			{
				/*
             * Utilize a função delay_ms para fazer o led piscar na frequência
             * escolhida por você.
             */
			PIOC->PIO_SODR =  (1 << PIN_LED_RED ); //led red acende
			delay_ms(1000);
			PIOC->PIO_CODR =  (1 << PIN_LED_RED ); //led red apaga
			PIOA->PIO_CODR =  (1 << PIN_LED_BLUE ); //led azul acende
			delay_ms(1000);
			PIOA->PIO_SODR =  (1 << PIN_LED_BLUE ); //led azul apaga
			PIOA->PIO_CODR =  (1 << PIN_LED_GREEN ); //led verde acende
			delay_ms(1000);
			PIOA->PIO_SODR =  (1 << PIN_LED_GREEN ); //led verde apaga
			}
                 
	}
}