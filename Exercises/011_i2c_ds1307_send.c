/*
 * 009_i2c_ds1307_send.c
 *
 *  Created on: Jun 21, 2023
 *      Author: 91701
 */
#include<stdio.h>
#include "ds1307.h"
#include <string.h>
#include "syscalls.h"
#include "lcd.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define SYSTICK_TIM_CLK   16000000UL

/* Enable this macro if you want to test RTC on LCD */
//#define PRINT_LCD

char* get_day_of_week(uint8_t i)
{
	char* days[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

	return days[i-1];
}


void number_to_string(uint8_t num , char* buf)
{

	if(num < 10){
		buf[0] = '0';
		buf[1] = num+48;
	}else if(num >= 10 && num < 99)
	{
		buf[0] = (num/10) + 48;
		buf[1]= (num % 10) + 48;
	}
}



//hh:mm:ss
char* time_to_string(RTC_time_t *rtc_time)
{
	static char buf[9];

	buf[2]= ':';
	buf[5]= ':';

	number_to_string(rtc_time->hours,buf);
	number_to_string(rtc_time->minutes,&buf[3]);
	number_to_string(rtc_time->seconds,&buf[6]);

	buf[8] = '\0';

	return buf;

}

//dd/mm/yy
char* date_to_string(RTC_date_t *rtc_date)
{
	static char buf[9];

	buf[2]= '/';
	buf[5]= '/';

	number_to_string(rtc_date->date,buf);
	number_to_string(rtc_date->month,&buf[3]);
	number_to_string(rtc_date->year,&buf[6]);

	buf[8]= '\0';

	return buf;

}

//static void mdelay(uint32_t cnt)
//{
//	for(uint32_t i=0 ; i < (cnt * 1000); i++);
//}

char buffer[512] = {0};


int main(void)
{

	RTC_time_t current_time;
	RTC_date_t current_date;
	int a =8;
	printf("RTC test\n");
	sprintf(buffer,"RTC test %d ",a);
	hardik_print(buffer,strlen(buffer));
	if(ds1307_init()){
		sprintf(buffer,"RTC init has failed\n %d ",a);
		hardik_print(buffer,strlen(buffer));
//		printf("RTC init has failed\n");
		while(1);

	}


		current_date.day = WEDNESDAY;
		current_date.date = 21;
		current_date.month = 6;
		current_date.year = 23;

		current_time.hours = 10;
		current_time.minutes = 16;
		current_time.seconds = 30;
		current_time.time_format = TIME_FORMAT_12HRS_PM;

		ds1307_set_current_date(&current_date);
		ds1307_set_current_time(&current_time);

		ds1307_get_current_time(&current_time);
		ds1307_get_current_date(&current_date);


		char *am_pm;
			if(current_time.time_format != TIME_FORMAT_24HRS){
				am_pm = (current_time.time_format) ? "PM" : "AM";
			//	printf("Current time = %s %s\n",time_to_string(&current_time),am_pm); // 04:25:41 PM
				char buffer[512] = {0};

				sprintf(buffer,"Current time = %s %s\n",time_to_string(&current_time),am_pm);
					hardik_print(buffer,strlen(buffer));
			}else{
			//	printf("Current time = %s\n",time_to_string(&current_time)); // 04:25:41
				char buffer[512] = {0};

				sprintf(buffer,"Current time = %s\n",time_to_string(&current_time));
					hardik_print(buffer,strlen(buffer));
			}

	printf("Current date = %s <%s>\n",date_to_string(&current_date), get_day_of_week(current_date.day));

	char buffer[512] = {0};

	sprintf(buffer,"Current date = %s <%s>\n",date_to_string(&current_date), get_day_of_week(current_date.day));
		hardik_print(buffer,strlen(buffer));
}




