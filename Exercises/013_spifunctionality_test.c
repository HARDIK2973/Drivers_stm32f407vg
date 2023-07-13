

#include "spifunctions.h"
#include <string.h>

int main(void)
{

	char data[] = "Hello World!";

	//Initializing GPIO and SPI
	SPI2Begin();

	//SPI2 Send data
	SPI2Send((uint8_t *)data,strlen(data));

	while(1);
	return 0;


}
