/*
 * TMR0_config.h
 *
 * Created: 2/11/2026 2:35:55 PM
 *  Author: hamza
 */ 


#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_

#define TMR0_PRELOAD_VLAUE			        152
#define TMR0_OVERFLOW_COUNTER			    2442

#define TMR0_OUTPUT_COMPARE_VLAUE			249
#define TMR0_CTCT_COUNTER			        100

/*
Options for TMR0 Operation Mode
1- TMR0_NORMAL_MODE
2- TMR0_CTC_MODE
*/

#define TMR0_MODE			TMR0_CTC_MODE

#endif /* TMR0_CONFIG_H_ */