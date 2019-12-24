/************************************************************************************************
* ���������� ��� ������ � ������� EEPROM � FLASH ������������ KM01-8600.M0
*
*************************************************************************************************/
#ifndef _MEM_	
#define _MEM_

// --- ������������ ���������� ---
#include <avr/io.h>	
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "km_8600.h"

// --- �������� ��������� ��� ������ ---
typedef struct
{
	unsigned char Address_device;	// ����� ������ � ���� ModBus
	unsigned char COM_Speed;		// ��������� �������� � ����
	unsigned char COM_Param;		// ��������� ����
	unsigned char PWM_Mode;			// ���������� ������ ��� ��� ������� �5, �6
	unsigned char PWM_Freq;			// ��������� ������� ���
	unsigned char INP_Mode;			// ����� ������ �������� ������
	unsigned char CB_cnt1;			// �������� �������������� �������� ��� ����� �1
	unsigned char CB_cnt2;			// �������� �������������� �������� ��� ����� �2
	unsigned char CB_cnt3;			// �������� �������������� �������� ��� ����� �3
	unsigned char CB_cnt4;			// �������� �������������� �������� ��� ����� �4
	unsigned char CB_cnt5;			// �������� �������������� �������� ��� ����� �5
	unsigned char CB_cnt6;			// �������� �������������� �������� ��� ����� �6
	unsigned char CB_cnt7;			// �������� �������������� �������� ��� ����� �7
	unsigned char CB_cnt8;			// �������� �������������� �������� ��� ����� �8
	unsigned int HW_cnt1;			// ������� ����� ���������� �������� ��� �������� ����� �1
	unsigned int LW_cnt1;			// ������� ����� ���������� �������� ��� �������� ����� �1
	unsigned int HW_cnt2;			// ������� ����� ���������� �������� ��� �������� ����� �2
	unsigned int LW_cnt2;			// ������� ����� ���������� �������� ��� �������� ����� �2
	unsigned int HW_cnt3;			// ������� ����� ���������� �������� ��� �������� ����� �3
	unsigned int LW_cnt3;			// ������� ����� ���������� �������� ��� �������� ����� �3
	unsigned int HW_cnt4;			// ������� ����� ���������� �������� ��� �������� ����� �4
	unsigned int LW_cnt4;			// ������� ����� ���������� �������� ��� �������� ����� �4
	unsigned int HW_cnt5;			// ������� ����� ���������� �������� ��� �������� ����� �5
	unsigned int LW_cnt5;			// ������� ����� ���������� �������� ��� �������� ����� �5
	unsigned int HW_cnt6;			// ������� ����� ���������� �������� ��� �������� ����� �6
	unsigned int LW_cnt6;			// ������� ����� ���������� �������� ��� �������� ����� �6
	unsigned int HW_cnt7;			// ������� ����� ���������� �������� ��� �������� ����� �7
	unsigned int LW_cnt7;			// ������� ����� ���������� �������� ��� �������� ����� �7
	unsigned int HW_cnt8;			// ������� ����� ���������� �������� ��� �������� ����� �8
	unsigned int LW_cnt8;			// ������� ����� ���������� �������� ��� �������� ����� �8
	
} config;

// --------- ���������� ������� ��������� � EEPROM -------------------------------------------
config MEM EEMEM;	// �������� �������� - ������� ��������� � EEPROM

// ------- ������� ����������� �� ��������� (��������� � EEPROM) -----------------------------
config MEM_df EEMEM = 
{
	0xEF,					// ����� ������ � ���� ModBus (239)
	0x07,					// ��������� �������� � ���� (19200)
	0x00,					// ��������� ���� (8E1)	
	0x00,					// ��������� ������ ��� ��� ������� �5, �6
	0x00,					// ������� ��� = 60��
	0x00,					// �������� ����� � ������� ������ (�� ������� �����)
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �1
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �2
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �3
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �4
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �5
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �6
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �7
	0x01,					// �������� �������� ����������� �� 1 ��� ����� �8
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000,					// �� ������� ����� = 0
	0x0000					// �� ������� ����� = 0
};

/**************** ��������� ��������� �������� (�������� �� ���������) ********************************************
* ���������� ��� ������� ���������� �  � �������������� � eeprom, ����� �� eeprom � �������� ���
*******************************************************************************************************************/
void set_default(void)
{
config tma;		// ��������� ������!
	// --- ������� ������ �������� �� ��������� ---
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_read_block(&tma,&MEM_df,sizeof(MEM_df));	// ������ �c� �� EEPROM � ���
	WDR();
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_block(&tma,&MEM,sizeof(tma));		// �������� ��� ��������� ��� � EEPROM ��������� ������� ��������
	
}

//================================================ ������ � INPUT ���������� ===============================================================

/************ ������ ����� ����������� �� FLASH � Ireg ������� ****************************************************/
void rd_name(void)
{
for(unsigned char i=0;i<6;i++)
	{
		MB_Ireg[28+i] = (unsigned int) (pgm_read_byte(&fl_name[i*2]) << 8);
		MB_Ireg[28+i] |= pgm_read_byte(&fl_name[(i*2)+1]);
	}
}
/************ ������ ������ �� ����������� �� FLASH � Ireg ������� ***********************************************/
void rd_ver(void)
{
for(unsigned char i=0;i<3;i++)
  {
	MB_Ireg[36+i] = (unsigned int) (pgm_read_byte(&fl_version[i*2]) << 8);
	MB_Ireg[36+i] |= pgm_read_byte(&fl_version[(i*2)+1]);
  }
}
/************ ������ ��������� ������ ����������� �� FLASH � Ireg ������� ****************************************/
void rd_ser(void)
{
for(unsigned char i=0;i<3;i++)
  {
	MB_Ireg[39+i] = (unsigned int) (pgm_read_byte(&fl_progid[i*2]) << 8);
	MB_Ireg[39+i] |= pgm_read_byte(&fl_progid[(i*2)+1]);
  }
}
//================================================ ������ � HOLDING ���������� ===============================================================
//============================================================================================================================================

/************ ������ ������ ����������� � ModBus ���� �� EEPROM � Hreg ������� ***********************************/
void rd_adr(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();						// ����� ���������� eeprom
	WDR();
	MB_Hreg[61] = (unsigned int) eeprom_read_byte(&MEM.Address_device); // ������ ������� ����� ����������� �� EEPROM � ���			
}
/*** ������ ��������� �������� � ���������� � ���� ��� �����������, �� EEPROM � Hreg ������� *********************/
void rd_par(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[62] = eeprom_read_byte(&MEM.COM_Param) << 8;		// ������ ������� ��������� ���� ��� ����������� � ����� �.�. ��� ������� ����
	WDR();
	MB_Hreg[62] |= eeprom_read_byte(&MEM.COM_Speed);			// ������ ��������� �������� ��� ����������� � �������� �� �������.
}
/*** ������ ��������� ������ ��� ��� ����������� (����� �5, � �6), �� EEPROM � Hreg ������� *********************/
void rd_pwm(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[34] = eeprom_read_byte(&MEM.PWM_Freq) << 8;		// ������ ������� ������� ��� ��� ����������� � ����� �.�. ��� ������� ����
	WDR();
	MB_Hreg[34] |= eeprom_read_byte(&MEM.PWM_Mode);			// ������ ����� ���������� ��� ��� ����������� � �������� �� �������.
}
//=====================================================================================================================================
//======================================== ������ � �������� ������� - ������ =========================================================

/****** ������ �������� ������ ������ �������� ������ ����������� �� EEPROM � Hreg ������� ********************/
void rd_mcnt(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[35] = (unsigned int) eeprom_read_byte(&MEM.INP_Mode); // ������ �������� ������� ������ �� EEPROM � ���
}
/****** ������ �������� �������� ��� ����� �1 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[36] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt1); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �1 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[45] = eeprom_read_word(&MEM.LW_cnt1);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �1 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[44] = eeprom_read_word(&MEM.HW_cnt1);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}

/****** ������ �������� �������� ��� ����� �2 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[37] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt2); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �2 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[47] = eeprom_read_word(&MEM.LW_cnt2);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �2 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[46] = eeprom_read_word(&MEM.HW_cnt2);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}

/****** ������ �������� �������� ��� ����� �3 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[38] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt3); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �3 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[49] = eeprom_read_word(&MEM.LW_cnt3);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �3 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[48] = eeprom_read_word(&MEM.HW_cnt3);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}

/****** ������ �������� �������� ��� ����� �4 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[39] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt4); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �4 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[51] = eeprom_read_word(&MEM.LW_cnt4);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �4 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[50] = eeprom_read_word(&MEM.HW_cnt4);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}

/****** ������ �������� �������� ��� ����� �5 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[40] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt5); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �5 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[53] = eeprom_read_word(&MEM.LW_cnt5);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �5 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[52] = eeprom_read_word(&MEM.HW_cnt5);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}

/****** ������ �������� �������� ��� ����� �6 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[41] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt6); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �6 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[55] = eeprom_read_word(&MEM.LW_cnt6);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �6 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[54] = eeprom_read_word(&MEM.HW_cnt6);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}

/****** ������ �������� �������� ��� ����� �7 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[42] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt7); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �7 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[57] = eeprom_read_word(&MEM.LW_cnt7);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �7 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[56] = eeprom_read_word(&MEM.HW_cnt7);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}

/****** ������ �������� �������� ��� ����� �8 ����������� �� EEPROM � Hreg ������� *****************************/
void rd_vcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();				// ����� ���������� eeprom
	WDR();
	MB_Hreg[43] = (unsigned int) eeprom_read_byte(&MEM.CB_cnt8); // ������ �������� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �8 ����������� �� EEPROM � Hreg ������� *************/
void rd_vlcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[59] = eeprom_read_word(&MEM.LW_cnt8);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
/****** ������ �������� ����� �������� �������� ��� ����� �8 ����������� �� EEPROM � Hreg ������� *************/
void rd_vhcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();			// ����� ���������� eeprom
	WDR();
	MB_Hreg[58] = eeprom_read_word(&MEM.HW_cnt8);			// ������ �� ����� �������� ����� �������� �� EEPROM � ���
}
//====================================== ����� ������ � �������� ������� ==============================================================
//=====================================================================================================================================

//------------------------------------------------------------------------------------------------------------------------- ������ ---
/******************* ������ ������ ����������� � ���� ModBus �� Hreg � EEPROM ***********************************/
void wr_adr(void)
{
unsigned char b;
	b = (unsigned char) MB_Hreg[61];				// ���� ������� ����
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.Address_device,b);		// �������� �������� � ������ EEPROM
}
/******************* ������ ���������� ���� ����������� � ModBus �� Hreg � EEPROM ******************************/
void wr_par(void)
{
	unsigned char b;
	b = (unsigned char) MB_Hreg[62];				// ���� ������� ����
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.COM_Speed,b);			// �������� �������� �������� � ������ EEPROM
	WDR();
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	b = (unsigned char) (MB_Hreg[62] >> 8);			// ���� ������� ����
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.COM_Param,b);			// �������� �������� ���������� � ������ EEPROM
}

/******************* ������ ���������� ��� ����������� � ModBus �� Hreg � EEPROM ******************************/
void wr_pwm(void)
{
	unsigned char b;
	b = (unsigned char) MB_Hreg[34];				// ���� ������� ����
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.PWM_Mode,b);				// �������� �������� ���������� ������� ��� � ������ EEPROM
	WDR();
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	b = (unsigned char) (MB_Hreg[34] >> 8);			// ���� ������� ����
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.PWM_Freq,b);				// �������� �������� �������� ��� � ������ EEPROM
}

//=========================================== ������ � �������� ������� - ������ ================================================
//===============================================================================================================================
/******************* ������ ������ ������ ������ ����������� �� Hreg � EEPROM ******************************/
void wr_mcnt(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.INP_Mode,(unsigned char) MB_Hreg[35]);	// �������� �������� � ������ EEPROM
}

/********** ������ ����� ��������� ��� �������� ����� �1 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt1,(unsigned char) MB_Hreg[36]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �1 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt1,MB_Hreg[45]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �1 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt1(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt1,MB_Hreg[44]);	// �������� �������� � ������ EEPROM
}

/********** ������ ����� ��������� ��� �������� ����� �2 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt2,(unsigned char) MB_Hreg[37]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �2 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt2,MB_Hreg[47]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �2 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt2(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt2,MB_Hreg[46]);	// �������� �������� � ������ EEPROM
}
/********** ������ ����� ��������� ��� �������� ����� �3 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt3,(unsigned char) MB_Hreg[38]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �3 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt3,MB_Hreg[49]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �3 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt3(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt3,MB_Hreg[48]);	// �������� �������� � ������ EEPROM
}

/********** ������ ����� ��������� ��� �������� ����� �4 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt4,(unsigned char) MB_Hreg[39]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �4 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt4,MB_Hreg[51]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �4 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt4(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt4,MB_Hreg[50]);	// �������� �������� � ������ EEPROM
}
/********** ������ ����� ��������� ��� �������� ����� �5 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt5,(unsigned char) MB_Hreg[40]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �5 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt5,MB_Hreg[53]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �5 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt5(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt5,MB_Hreg[52]);	// �������� �������� � ������ EEPROM
}

/********** ������ ����� ��������� ��� �������� ����� �6 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt6,(unsigned char) MB_Hreg[41]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �6 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt6,MB_Hreg[55]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �6 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt6(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt6,MB_Hreg[54]);	// �������� �������� � ������ EEPROM
}
/********** ������ ����� ��������� ��� �������� ����� �7 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt7,(unsigned char) MB_Hreg[42]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �7 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt7,MB_Hreg[57]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �7 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt7(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt7,MB_Hreg[56]);	// �������� �������� � ������ EEPROM
}

/********** ������ ����� ��������� ��� �������� ����� �8 ����������� �� Hreg � EEPROM *********************/
void wr_vcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();					// ����� ���������� eeprom
	WDR();
	eeprom_write_byte(&MEM.CB_cnt8,(unsigned char) MB_Hreg[43]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �8 ����������� �� Hreg � EEPROM ******************/
void wr_vlcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.LW_cnt8,MB_Hreg[59]);	// �������� �������� � ������ EEPROM
}
/*** ������ �������� �������� �������� ����� ��� �������� �8 ����������� �� Hreg � EEPROM ******************/
void wr_vhcnt8(void)
{
	if(eeprom_is_ready() == 0) eeprom_busy_wait();	// ����� ���������� eeprom
	WDR();
	eeprom_write_word(&MEM.HW_cnt8,MB_Hreg[58]);	// �������� �������� � ������ EEPROM
}

/*************************************** ������������� ��������� �� ������ ********************************/
void InitMem(void)
{
	// �������� ��������� ��������� INPUT
	rd_name();		// ��� �����������
	rd_ver();		// ������ �� �����������
	rd_ser();		// �������� ����� �����������
	// �������� ��������� ��������� HOLD
	rd_adr();		// ����� ����������� � ���� ModBus
	rd_par();		// ��������� ����
	rd_pwm();		// ��������� ��� ��� ������ �5 � �6
	rd_mcnt();		// ��������� ������ ������ �������� ������
	rd_vcnt1();		// �������� �������� ��� ����� �1
	rd_vcnt2();		// �������� �������� ��� ����� �2
	rd_vcnt3();		// �������� �������� ��� ����� �3
	rd_vcnt4();		// �������� �������� ��� ����� �4
	rd_vcnt5();		// �������� �������� ��� ����� �5
	rd_vcnt6();		// �������� �������� ��� ����� �6
	rd_vcnt7();		// �������� �������� ��� ����� �7
	rd_vcnt8();		// �������� �������� ��� ����� �8
	rd_vhcnt1();	// ������� ����� �������� �������� �������� ����� �1
	rd_vlcnt1();	// ������� ����� �������� �������� �������� ����� �1
	rd_vhcnt2();	// ������� ����� �������� �������� �������� ����� �2
	rd_vlcnt2();	// ������� ����� �������� �������� �������� ����� �2
	rd_vhcnt3();	// ������� ����� �������� �������� �������� ����� �3
	rd_vlcnt3();	// ������� ����� �������� �������� �������� ����� �3
	rd_vhcnt4();	// ������� ����� �������� �������� �������� ����� �4
	rd_vlcnt4();	// ������� ����� �������� �������� �������� ����� �4
	rd_vhcnt5();	// ������� ����� �������� �������� �������� ����� �5
	rd_vlcnt5();	// ������� ����� �������� �������� �������� ����� �5
	rd_vhcnt6();	// ������� ����� �������� �������� �������� ����� �6
	rd_vlcnt6();	// ������� ����� �������� �������� �������� ����� �6
	rd_vhcnt7();	// ������� ����� �������� �������� �������� ����� �7
	rd_vlcnt7();	// ������� ����� �������� �������� �������� ����� �7
	rd_vhcnt8();	// ������� ����� �������� �������� �������� ����� �8
	rd_vlcnt8();	// ������� ����� �������� �������� �������� ����� �8
	
}

#endif
//***************************************************** END ************************************************