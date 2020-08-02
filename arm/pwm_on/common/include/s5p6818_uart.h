/*  
 *S5P6818 SFR address define
 *hqyj
 *2017.10.1
 *version: 1.0
*/

#ifndef ___S5P6818_UART_H_
#define ___S5P6818_UART_H_

/*********************** UART ************************/

typedef struct {
				unsigned int ULCON;
				unsigned int UCON;
				unsigned int UFCON;
				unsigned int UMCON;
				unsigned int UTRSTAT;
				unsigned int UERSTAT;
				unsigned int UFSTAT;
				unsigned int UMSTAT;
				unsigned int UTXH;
				unsigned int URXH;
				unsigned int UBRDIV;
				unsigned int UFRACVAL;
				unsigned int UINTP;
				unsigned int UINTS;
				unsigned int UINTM;
}uart;
/*************** UART0 *****************/
#define UART0 ( * (volatile uart *)0xC00A1000 )

/*************** UART1 *****************/
#define UART1 ( * (volatile uart *)0xC00A0000 )

/*************** UART2 *****************/
#define UART2 ( * (volatile uart *)0xC00A2000 )

/*************** UART3 *****************/
#define UART3 ( * (volatile uart *)0xC00A3000 )

/*************** UART4 *****************/
#define UART4 ( * (volatile uart *)0xC00AD000 )

/*************** UART5 *****************/
#define UART5 ( * (volatile uart *)0xC00AF000 )

extern void __uart_init(void);
extern char __uart_getc(void);
extern void __uart_putc(const char data);
extern void __uart_puts(const char *pstr);

#endif
