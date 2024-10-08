/*
 * hadajCislo.cpp
 *
 * Created: 21. 1. 2022 20:01:14
 * Author : HP
 * 
 * Program je hra hadaj cislo ktorá sa hra na IoT 2017 boarde a komunikuje s PC cez Uart
 * Na doske sa zobrazuje cislo zaroven s farbou ktore oznacuju, hranicu intevalu hornu alebo dolnu
 * Hrac cez Uart pise cislo o ktorm si mysli ze ja to to vygenerovane hladene cislo
 * V pripade nezhody zasvietli LED ktora upozurnuje ci gener. cis. je vacsie alebo mensie
 * Hrac ma 3 pokusi trafit gener. cis.    
 */ 

#include <avr/io.h>

#include "Led.h"
#include "Button.h"
#include "Display.h"
#include "Uart.h"
#include "Generator.h"

#define POC_POKUS 2

int main(void)
{
    /* Replace with your application code */
	Led rgb;
	Button btn;
	Display seg;
	Uart ter;
	Generator gen;
	
	gen.generuj(); // generuje nahodne cislo od 0 po f
	
	while(!btn.isPressed()){}
	
	gen.showInteval(); // zorazi interval blikne farba ktora oznacuej hranicu 
							// a zobrazi cislo na segmetovke
	uint8_t   odhad, pokus = POC_POKUS, kontP; //nahc, dolh, horh, rozptil, , perc
	unsigned char zber;
	
	printf("zadaj cislo v intervale ....\r\n");
	
    while (1)
    {	kontP = pokus;
		
		odhad = 16;
		zber = getchar() ;
		if (zber > 47 && zber < 58) {
			odhad = zber - 48; // 0
		} else {
			if(zber > 64 && zber < 71)
				odhad = zber - 65 + 10; // A: 10 cisla > ako 9 sa zadavaju ako psismena (a - f)
			if(zber > 96 && zber < 103)
				odhad = zber - 97 + 10; // a: 10	
		}
		printf("Zadane cislo %d \r\n", odhad );
		
		pokus = gen.odhadCis(odhad, pokus);
		_delay_ms(1000);
		if(pokus == 0)
			break;
		else if(  pokus== kontP ){ //kontP < POC_POKUS &&
			gen.generuj();
			gen.showInteval();
			printf("zadaj cislo v intervale ....\r\n");
		}
		printf("pokus %d \r\n", pokus);
		//printf("kont pokus %d \r\n", kontP);
		//rgb.set(off);
		
    }
	printf("Koniec hry.\r\n");
	rgb.set(off);
}