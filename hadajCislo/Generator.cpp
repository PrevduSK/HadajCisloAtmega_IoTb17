/* 
* Generator.cpp
*
* Created: 22. 1. 2022 21:31:14
* Author: HP
*/


#include "Generator.h"

// default constructor
Generator::Generator()
{
	this->Seed = 0x00;
	this->Magic = 0x5c;
	this->rozptil = 2;
	Led rgb1;
	this->rgb = rgb1;
	Display seg1;
	this->seg = seg1;
	seg.circle();
	Eeprom pam;
	
	if(pam.read( 0)== 0){
		pam.write( 0, 0x07);
	} else if(pam.read( 0) > 0x1d){
		pam.write(0, 0x02);
	} else {
		zpam = pam.read(0);
		zpam += 0x03;
		pam.write(0, this->zpam);
	}
	this->zpam = pam.read(0);
	
} //Generator

// default destructor
Generator::~Generator()
{
} //~Generator

uint8_t Generator::RotateRight(uint8_t val, short nr)
{
	uint8_t tmp;
	while(nr--)
	{
		tmp = val & 1;
		tmp >>= 1;
		val |= tmp;
	}
	return val;
}

uint8_t Generator::Rand()
{
	Seed = RotateRight(Seed, 3);
	Seed += Magic;

	return Seed;
}

void Generator::Srand(uint8_t val)
{
	Seed = val;
}

void Generator::generuj()
{
	seg.show(16); // zobrazi bodku ze je pripravena hodnota
	//this->nahc = rand()% 15; //return
	short i;
	for(;;)
	{
		Seed = 0;
		//printf("%d\n", Magic); //02x
		i = 0;
		while(Rand())
		i++;
		if(i < 0xfe)
		Magic++;
		else
		break;
	}
	for(i=0; i< this->zpam; i++)// 0x10
		this->nahc =  Rand()%15;
	//printf("%d , z pamate %d : 0x%x \r\n", nahc, zpam, zpam);//02x

}

uint8_t Generator::dolHranica()
{	
	uint8_t pomDoh, pomHoh;
	if( this->nahc < 2 ){
		pomDoh = 0;

	}else if( this->nahc > 13 ){
		pomHoh = this->nahc + rozptil;
		if( pomHoh == 16)
			pomDoh = this->nahc - rozptil;
		if( pomHoh == 17)
			pomDoh = this->nahc - rozptil - 1;

	} else {
		if( (this->perc = Rand()% 100) < 50) {
			pomDoh = this->nahc -rozptil + 1;
		} else {
			pomDoh = this->nahc -rozptil;
		}
		//printf("percenta %d \r\n", perc);
	}
	//printf("nahodne %d , dolna hranica %d \r\n", nahc, dolh);
	this->dolh = pomDoh;
	return pomDoh;
}
	
uint8_t Generator::horHranica()
{
	uint8_t pomDoh, pomHoh;
	if( this->nahc < 2 ){
		pomDoh = this->nahc -rozptil;
		if( pomDoh == 254)
			pomHoh = this->nahc + rozptil + 1;
		if( pomDoh == 255)
			pomHoh = this->nahc + rozptil;

	}else if( this->nahc > 13 ){
		pomHoh = 15;

	} else {
		if( (this->perc) < 50) { // = Rand()% 100
			pomHoh = this->nahc + rozptil;
		} else {
			pomHoh = this->nahc + rozptil - 1;
		}
		//printf("percenta %d \r\n", perc);
	}
	//printf("nahodne %d , horna hranica %d \r\n", nahc, horh);
	this->horh = pomHoh;
	return pomHoh;
	
	/*	if( nahc < 2 ){
		dolh = nahc -rozptil;
		if( dolh == 254)
		horh = nahc + rozptil + 1;
		if( dolh == 255)
		horh = nahc + rozptil;
		dolh = 0;

	}else if( nahc > 13 ){
		horh = nahc + rozptil;
		if( horh == 16)
		dolh = nahc - rozptil;
		if( horh == 17)
		dolh = nahc - rozptil - 1;
		horh = 20;

	} else {
		if( (perc = rand()% 100) < 50) {
			dolh = nahc -rozptil + 1;
			horh = nahc + rozptil;
		} else {
			dolh = nahc -rozptil;
			horh = nahc + rozptil - 1;
		}
	} */
}

void Generator::showInteval()
{
	presMedziHod();

	rgb.set(cyan);
	_delay_ms(500);
	rgb.set(off);
	_delay_us(2);
	seg.show(dolHranica());
	_delay_ms(800);
	//seg.showMultip(dolHranica(), 1800, 2); //dolna hranica intevalu
	
	presMedziHod();
	
	rgb.set(blue);
	_delay_ms(500);
	rgb.set(off);
	_delay_us(2);
	seg.show(horHranica());
	_delay_ms(800);
	//seg.showMultip(horHranica(), 1800, 2); //holna hranica intevalu
	printf("Interval= <%d, %d> \r\n", dolh, horh);
	
	presMedziHod();
	
	rgb.set(on); // signal, hrac moze hadat cislo
	_delay_ms(500);
	rgb.set(off);
}

void Generator::presMedziHod()
{
	seg.show(18);
	_delay_us(10);
	rgb.set(off);
	_delay_ms(500);
}

uint8_t Generator::odhadCis(uint8_t odhad, uint8_t pokus)
{
	if(odhad >= 0 && odhad < 16){
		rgb.set(off);
		if(pokus > 0){
			if( odhad < nahc){
				printf("odhad: %d < cislo.\r\n", odhad);
				--pokus;
				rgb.set(yellow); // je mensie
				_delay_ms(600);
				} else if( odhad > nahc){
				printf("odhad: %d > cislo.\r\n", odhad);
				--pokus;
				rgb.set(magenta); // vecie
				_delay_ms(600);
				} else { //==
				printf("odhad: %d = cislo: %d \r\n", odhad, nahc);
				rgb.set(green); // rovne
				_delay_ms(600);
			}
		}
		if(pokus == 0) {
			rgb.set(red); // vyprsal pocet pokusov
			_delay_ms(600);			
		}
	}
	return pokus;
}