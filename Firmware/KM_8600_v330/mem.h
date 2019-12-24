/************************************************************************************************
* Библиотека для работы с памятью EEPROM и FLASH контроллеров KM01-8600.M0
*
*************************************************************************************************/
#ifndef _MEM_	
#define _MEM_

// --- Подключаемые библиотеки ---
#include <avr/io.h>	
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "km_8600.h"

// --- Объявляю структуру для памяти ---
typedef struct
{
	unsigned char Address_device;	// Адрес модуля в сети ModBus
	unsigned char COM_Speed;		// Категория скорости в сети
	unsigned char COM_Param;		// Параметры сети
	unsigned char PWM_Mode;			// Разрешение работы ШИМ для выходов №5, №6
	unsigned char PWM_Freq;			// Категория частоты ШИМ
	unsigned char INP_Mode;			// Режим работы цифровых входов
	unsigned char CB_cnt1;			// Значение накопительного счетчика для входа №1
	unsigned char CB_cnt2;			// Значение накопительного счетчика для входа №2
	unsigned char CB_cnt3;			// Значение накопительного счетчика для входа №3
	unsigned char CB_cnt4;			// Значение накопительного счетчика для входа №4
	unsigned char CB_cnt5;			// Значение накопительного счетчика для входа №5
	unsigned char CB_cnt6;			// Значение накопительного счетчика для входа №6
	unsigned char CB_cnt7;			// Значение накопительного счетчика для входа №7
	unsigned char CB_cnt8;			// Значение накопительного счетчика для входа №8
	unsigned int HW_cnt1;			// Старшее слово начального значения для счетного входа №1
	unsigned int LW_cnt1;			// Младшее слово начального значения для счетного входа №1
	unsigned int HW_cnt2;			// Старшее слово начального значения для счетного входа №2
	unsigned int LW_cnt2;			// Младшее слово начального значения для счетного входа №2
	unsigned int HW_cnt3;			// Старшее слово начального значения для счетного входа №3
	unsigned int LW_cnt3;			// Младшее слово начального значения для счетного входа №3
	unsigned int HW_cnt4;			// Старшее слово начального значения для счетного входа №4
	unsigned int LW_cnt4;			// Младшее слово начального значения для счетного входа №4
	unsigned int HW_cnt5;			// Старшее слово начального значения для счетного входа №5
	unsigned int LW_cnt5;			// Младшее слово начального значения для счетного входа №5
	unsigned int HW_cnt6;			// Старшее слово начального значения для счетного входа №6
	unsigned int LW_cnt6;			// Младшее слово начального значения для счетного входа №6
	unsigned int HW_cnt7;			// Старшее слово начального значения для счетного входа №7
	unsigned int LW_cnt7;			// Младшее слово начального значения для счетного входа №7
	unsigned int HW_cnt8;			// Старшее слово начального значения для счетного входа №8
	unsigned int LW_cnt8;			// Младшее слово начального значения для счетного входа №8
	
} config;

// --------- Объявление рабочей структуры в EEPROM -------------------------------------------
config MEM EEMEM;	// Значения настроек - рабочая структура в EEPROM

// ------- Уставки контроллера по умолчанию (храняться в EEPROM) -----------------------------
config MEM_df EEMEM = 
{
	0xEF,					// Адрес модуля в сети ModBus (239)
	0x07,					// Категория скорости в сети (19200)
	0x00,					// Параметры сети (8E1)	
	0x00,					// Запрещена работа ШИМ для выходов №5, №6
	0x00,					// Частота ШИМ = 60Гц
	0x00,					// Цифровые входы в обычном режиме (не счетные входа)
	0x01,					// входящие импульсы накапливать по 1 для входа №1
	0x01,					// входящие импульсы накапливать по 1 для входа №2
	0x01,					// входящие импульсы накапливать по 1 для входа №3
	0x01,					// входящие импульсы накапливать по 1 для входа №4
	0x01,					// входящие импульсы накапливать по 1 для входа №5
	0x01,					// входящие импульсы накапливать по 1 для входа №6
	0x01,					// входящие импульсы накапливать по 1 для входа №7
	0x01,					// входящие импульсы накапливать по 1 для входа №8
	0x0000,					// Ст опорное число = 0
	0x0000,					// Мл опорное число = 0
	0x0000,					// Ст опорное число = 0
	0x0000,					// Мл опорное число = 0
	0x0000,					// Ст опорное число = 0
	0x0000,					// Мл опорное число = 0
	0x0000,					// Ст опорное число = 0
	0x0000,					// Мл опорное число = 0
	0x0000,					// Ст опорное число = 0
	0x0000,					// Мл опорное число = 0
	0x0000,					// Ст опорное число = 0
	0x0000,					// Мл опорное число = 0
	0x0000,					// Ст опорное число = 0
	0x0000,					// Мл опорное число = 0
	0x0000,					// Ст опорное число = 0
	0x0000					// Мл опорное число = 0
};

/**************** установка заводских настроек (заданных по умолчанию) ********************************************
* изначально все уставки находяться в  и переписываются в eeprom, затем из eeprom в рагистры ОЗУ
*******************************************************************************************************************/
void set_default(void)
{
config tma;		// Временный массив!
	// --- заполню массив настроек по умолчанию ---
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_read_block(&tma,&MEM_df,sizeof(MEM_df));	// Считаю вcе из EEPROM в ОЗУ
	WDR();
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_block(&tma,&MEM,sizeof(tma));		// Записать всю структуру ОЗУ в EEPROM структуру рабочих настроек
	
}

//================================================ Работа с INPUT регистрами ===============================================================

/************ Чтение имени контроллера из FLASH в Ireg регистр ****************************************************/
void rd_name(void)
{
for(unsigned char i=0;i<6;i++)
	{
		MB_Ireg[28+i] = (unsigned int) (pgm_read_byte(&fl_name[i*2]) << 8);
		MB_Ireg[28+i] |= pgm_read_byte(&fl_name[(i*2)+1]);
	}
}
/************ Чтение версии ПО контроллера из FLASH в Ireg регистр ***********************************************/
void rd_ver(void)
{
for(unsigned char i=0;i<3;i++)
  {
	MB_Ireg[36+i] = (unsigned int) (pgm_read_byte(&fl_version[i*2]) << 8);
	MB_Ireg[36+i] |= pgm_read_byte(&fl_version[(i*2)+1]);
  }
}
/************ Чтение серийного номера контроллера из FLASH в Ireg регистр ****************************************/
void rd_ser(void)
{
for(unsigned char i=0;i<3;i++)
  {
	MB_Ireg[39+i] = (unsigned int) (pgm_read_byte(&fl_progid[i*2]) << 8);
	MB_Ireg[39+i] |= pgm_read_byte(&fl_progid[(i*2)+1]);
  }
}
//================================================ Работа с HOLDING регистрами ===============================================================
//============================================================================================================================================

/************ Чтение адреса контроллера в ModBus сети из EEPROM в Hreg регистр ***********************************/
void rd_adr(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();						// Ждать готовности eeprom
	WDR();
	MB_Hreg[61] = (unsigned int) eeprom_read_byte(&MEM.Address_device); // Считаю сетевой адрес контроллера из EEPROM в ОЗУ			
}
/*** Чтение категории скорости и параметров в сети для контроллера, из EEPROM в Hreg регистр *********************/
void rd_par(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[62] = eeprom_read_byte(&MEM.COM_Param) << 8;		// Считаю сначала параметры сети для контроллера и сдвиг т.к. это старший байт
	WDR();
	MB_Hreg[62] |= eeprom_read_byte(&MEM.COM_Speed);			// Считаю категорию скорости для контроллера и склеиваю со старшим.
}
/*** Чтение категории работы ШИМ для контроллера (вывод №5, и №6), из EEPROM в Hreg регистр *********************/
void rd_pwm(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[34] = eeprom_read_byte(&MEM.PWM_Freq) << 8;		// Считаю сначала частоту ШИМ для контроллера и сдвиг т.к. это старший байт
	WDR();
	MB_Hreg[34] |= eeprom_read_byte(&MEM.PWM_Mode);			// Считаю Флаги активности ШИМ для контроллера и склеиваю со старшим.
}
//=====================================================================================================================================
//======================================== РАБОТА С СЧЕТНЫМИ ВХОДАМИ - ЧТЕНИЕ =========================================================

/****** Чтение значения режима работы цифровых входов контроллера из EEPROM в Hreg регистр ********************/
void rd_mcnt(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[35] = (unsigned int) eeprom_read_byte(&MEM.INP_Mode); // Считаю значение режимов работы из EEPROM в ОЗУ
}
/****** Чтение значения счетчика для входа №1 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[36] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt1); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №1 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[45] = eeprom_read_word(&MEM.LW_cnt1);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №1 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[44] = eeprom_read_word(&MEM.HW_cnt1);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}

/****** Чтение значения счетчика для входа №2 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[37] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt2); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №2 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[47] = eeprom_read_word(&MEM.LW_cnt2);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №2 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[46] = eeprom_read_word(&MEM.HW_cnt2);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}

/****** Чтение значения счетчика для входа №3 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[38] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt3); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №3 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[49] = eeprom_read_word(&MEM.LW_cnt3);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №3 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[48] = eeprom_read_word(&MEM.HW_cnt3);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}

/****** Чтение значения счетчика для входа №4 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[39] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt4); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №4 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[51] = eeprom_read_word(&MEM.LW_cnt4);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №4 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[50] = eeprom_read_word(&MEM.HW_cnt4);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}

/****** Чтение значения счетчика для входа №5 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[40] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt5); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №5 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[53] = eeprom_read_word(&MEM.LW_cnt5);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №5 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[52] = eeprom_read_word(&MEM.HW_cnt5);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}

/****** Чтение значения счетчика для входа №6 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[41] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt6); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №6 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[55] = eeprom_read_word(&MEM.LW_cnt6);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №6 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[54] = eeprom_read_word(&MEM.HW_cnt6);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}

/****** Чтение значения счетчика для входа №7 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[42] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt7); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №7 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[57] = eeprom_read_word(&MEM.LW_cnt7);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №7 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[56] = eeprom_read_word(&MEM.HW_cnt7);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}

/****** Чтение значения счетчика для входа №8 контроллера из EEPROM в Hreg регистр *****************************/
void rd_vcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// Ждать готовности eeprom
	WDR();
	MB_Hreg[43] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt8); // Считаю значение счетчика из EEPROM в ОЗУ
}
/****** Чтение младшего слова значения счетчика для входа №8 контроллера из EEPROM в Hreg регистр *************/
void rd_vlcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[59] = eeprom_read_word(&MEM.LW_cnt8);			// Считаю мл слово опорного числа счетчика из EEPROM в ОЗУ
}
/****** Чтение старшего слова значения счетчика для входа №8 контроллера из EEPROM в Hreg регистр *************/
void rd_vhcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// Ждать готовности eeprom
	WDR();
	MB_Hreg[58] = eeprom_read_word(&MEM.HW_cnt8);			// Считаю ст слово опорного числа счетчика из EEPROM в ОЗУ
}
//====================================== КОНЕЦ РАБОТЫ С СЧЕТНЫМИ ВХОДАМИ ==============================================================
//=====================================================================================================================================

//------------------------------------------------------------------------------------------------------------------------- ЗАПИСЬ ---
/******************* Запись адреса контроллера в сети ModBus из Hreg в EEPROM ***********************************/
void wr_adr(void)
{
unsigned char b;
	b = (unsigned char) MB_Hreg[61];				// беру младший байт
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.Address_device,b);		// Записать значение в память EEPROM
}
/******************* Запись параметров сети контроллера в ModBus из Hreg в EEPROM ******************************/
void wr_par(void)
{
	unsigned char b;
	b = (unsigned char) MB_Hreg[62];				// беру младший байт
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.COM_Speed,b);			// Записать значение скорости в память EEPROM
	WDR();
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	b = (unsigned char) (MB_Hreg[62] >> 8);			// беру старший байт
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.COM_Param,b);			// Записать значение параметров в память EEPROM
}

/******************* Запись параметров ШИМ контроллера в ModBus из Hreg в EEPROM ******************************/
void wr_pwm(void)
{
	unsigned char b;
	b = (unsigned char) MB_Hreg[34];				// беру младший байт
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.PWM_Mode,b);				// Записать значение активности выводов ШИМ в память EEPROM
	WDR();
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	b = (unsigned char) (MB_Hreg[34] >> 8);			// беру старший байт
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.PWM_Freq,b);				// Записать значение скорости ШИМ в память EEPROM
}

//=========================================== РАБОТА С СЧЕТНЫМИ ВХОДАМИ - ЗАПИСЬ ================================================
//===============================================================================================================================
/******************* Запись режима работы входов контроллера из Hreg в EEPROM ******************************/
void wr_mcnt(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.INP_Mode,(unsigned char) MB_Hreg[35]);	// Записать значение в память EEPROM
}

/********** Запись числа пересчета для счетного входа №1 контроллера из Hreg в EEPROM *********************/
void wr_vcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt1,(unsigned char) MB_Hreg[36]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №1 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt1,MB_Hreg[45]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №1 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt1,MB_Hreg[44]);	// Записать значение в память EEPROM
}

/********** Запись числа пересчета для счетного входа №2 контроллера из Hreg в EEPROM *********************/
void wr_vcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt2,(unsigned char) MB_Hreg[37]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №2 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt2,MB_Hreg[47]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №2 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt2,MB_Hreg[46]);	// Записать значение в память EEPROM
}
/********** Запись числа пересчета для счетного входа №3 контроллера из Hreg в EEPROM *********************/
void wr_vcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt3,(unsigned char) MB_Hreg[38]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №3 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt3,MB_Hreg[49]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №3 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt3,MB_Hreg[48]);	// Записать значение в память EEPROM
}

/********** Запись числа пересчета для счетного входа №4 контроллера из Hreg в EEPROM *********************/
void wr_vcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt4,(unsigned char) MB_Hreg[39]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №4 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt4,MB_Hreg[51]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №4 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt4,MB_Hreg[50]);	// Записать значение в память EEPROM
}
/********** Запись числа пересчета для счетного входа №5 контроллера из Hreg в EEPROM *********************/
void wr_vcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt5,(unsigned char) MB_Hreg[40]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №5 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt5,MB_Hreg[53]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №5 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt5,MB_Hreg[52]);	// Записать значение в память EEPROM
}

/********** Запись числа пересчета для счетного входа №6 контроллера из Hreg в EEPROM *********************/
void wr_vcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt6,(unsigned char) MB_Hreg[41]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №6 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt6,MB_Hreg[55]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №6 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt6,MB_Hreg[54]);	// Записать значение в память EEPROM
}
/********** Запись числа пересчета для счетного входа №7 контроллера из Hreg в EEPROM *********************/
void wr_vcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt7,(unsigned char) MB_Hreg[42]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №7 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt7,MB_Hreg[57]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №7 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt7,MB_Hreg[56]);	// Записать значение в память EEPROM
}

/********** Запись числа пересчета для счетного входа №8 контроллера из Hreg в EEPROM *********************/
void wr_vcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// Ждать готовности eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt8,(unsigned char) MB_Hreg[43]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №8 контроллера из Hreg в EEPROM ******************/
void wr_vlcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt8,MB_Hreg[59]);	// Записать значение в память EEPROM
}
/*** Запись значения младшего опорного числа для счетчика №8 контроллера из Hreg в EEPROM ******************/
void wr_vhcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// Ждать готовности eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt8,MB_Hreg[58]);	// Записать значение в память EEPROM
}

/*************************************** Инициализация регистров из памяти ********************************/
void InitMem(void)
{
	// Заполняю структуру регистров INPUT
	rd_name();		// Имя контроллера
	rd_ver();		// Версия ПО контроллера
	rd_ser();		// Серийный номер контроллера
	// Заполняю структуру регистров HOLD
	rd_adr();		// Адрес контроллера в сети ModBus
	rd_par();		// Параметры сети
	rd_pwm();		// Параметры ШИМ для выхода №5 и №6
	rd_mcnt();		// указатель режима работы цифровых входов
	rd_vcnt1();		// значение делителя для входа №1
	rd_vcnt2();		// значение делителя для входа №2
	rd_vcnt3();		// значение делителя для входа №3
	rd_vcnt4();		// значение делителя для входа №4
	rd_vcnt5();		// значение делителя для входа №5
	rd_vcnt6();		// значение делителя для входа №6
	rd_vcnt7();		// значение делителя для входа №7
	rd_vcnt8();		// значение делителя для входа №8
	rd_vhcnt1();	// старшее слово опорного значения счетного входа №1
	rd_vlcnt1();	// младшее слово опорного значения счетного входа №1
	rd_vhcnt2();	// старшее слово опорного значения счетного входа №2
	rd_vlcnt2();	// младшее слово опорного значения счетного входа №2
	rd_vhcnt3();	// старшее слово опорного значения счетного входа №3
	rd_vlcnt3();	// младшее слово опорного значения счетного входа №3
	rd_vhcnt4();	// старшее слово опорного значения счетного входа №4
	rd_vlcnt4();	// младшее слово опорного значения счетного входа №4
	rd_vhcnt5();	// старшее слово опорного значения счетного входа №5
	rd_vlcnt5();	// младшее слово опорного значения счетного входа №5
	rd_vhcnt6();	// старшее слово опорного значения счетного входа №6
	rd_vlcnt6();	// младшее слово опорного значения счетного входа №6
	rd_vhcnt7();	// старшее слово опорного значения счетного входа №7
	rd_vlcnt7();	// младшее слово опорного значения счетного входа №7
	rd_vhcnt8();	// старшее слово опорного значения счетного входа №8
	rd_vlcnt8();	// младшее слово опорного значения счетного входа №8
	
}

#endif
//***************************************************** END ************************************************