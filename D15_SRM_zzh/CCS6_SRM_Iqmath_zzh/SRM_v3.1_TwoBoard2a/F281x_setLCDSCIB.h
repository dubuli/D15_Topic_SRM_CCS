/*********************************************************************************
*	LCDҺ��λ640*480�ķֱ��ʣ���ʾ16*16���֣�������ʾ30�У�40��
* 
*
*
*
*
*
*
*
*
*
*
*
**********************************************************************************/




char	asc_to_hex(char asc)     ;
char	hex_to_asc(char hex)     ;
WORD	hex2_to_decimal(BYTE b)  ;
LONG	hex4_to_decimal(WORD w)  ;
void	delay_us(unsigned int d) ;
void	delay_ms(unsigned int d) ;


void	LCDPO_Clears(void)   ;

// ������ɫ�궨��
#define   BLACK		0x0000      /* ��ɫ��    0,   0,   0 */
#define   NAVY		0x000F      /* ����ɫ��  0,   0, 128 */
#define   DGREEN	0x03E0		/* ����ɫ��  0, 128,   0 */
#define   DCYAN		0x03EF		/* ����ɫ��  0, 128, 128 */
#define   MAROON	0x7800		/* ���ɫ��128,   0,   0 */
#define   PURPLE	0x780F		/* ��ɫ��  128,   0, 128 */
#define   OLIVE		0x7BE0 	    /* ����̣�128, 128,   0 */
#define   LGRAY		0xC618	    /* �Ұ�ɫ��192, 192, 192 */
#define   DGRAY		0x7BEF		/* ���ɫ��128, 128, 128 */
#define   BLUE		0x001F		/* ��ɫ��    0,   0, 255 */
#define   GREEN		0x07E0		/* ��ɫ��    0, 255,   0 */
#define   CYAN	    0x07FF 		/* ��ɫ��    0, 255, 255 */
#define   RED		0xF800		/* ��ɫ��  255,   0,   0 */
#define   MAGENTA	0xF81F		/* Ʒ�죺  255,   0, 255 */
#define   YELLOW	0xFFE0		/* ��ɫ��  255, 255, 0   */
#define   WHITE		0xFFFF      /* ��ɫ��  255, 255, 255 */
#define   LBLUE		0x8e5d      /*  */


#define DELAY_1us	asm(" RPT #146 || NOP ");	/* 6.667ns * 150 = 1usec */


void	delay_us(unsigned int d)
{
	while(d--) DELAY_1us;
}

void	delay_ms(unsigned int d)
{
	while(d--) delay_us(992);
}

//==============================================================
 //==============================================================
/**************** Data conversion function ************************/
char	asc_to_hex(char asc)
{
    if((asc >= '0') && (asc <= '9'))    return (asc - '0');
    else if((asc >= 'A') && (asc <= 'F'))   return (asc - 'A' + 0x0a);
    else if((asc >= 'a') && (asc <= 'f'))    return (asc - 'a' + 0x0a);
    else return 0xff;
}       
//==============================================================
 //==============================================================
char	hex_to_asc(char hex)
{
	char	da;
	da = hex & 0x0f;
    if((da >= 0) && (da <= 9))    return  ('0' + da);
    else    return  ('A' + da - 0x0a);
}
//==============================================================
 //==============================================================
WORD	hex2_to_decimal(BYTE b)
{
	WORD	d100,d10,d1;
	WORD	dec=0;
	d100 = b/100;
	d10 = (b - d100*100)/10;
	d1 = (b - d100*100 - d10*10); 
	dec = (d100<<8) | (d10<<4) | d1;
	return dec;
}
//==============================================================
 //==============================================================
LONG	hex4_to_decimal(WORD w)
{
	LONG	d10000,d1000,d100,d10,d1;
	LONG	dec=0;
	d10000 = w/10000;
	d1000 = (w - d10000 * 10000)/1000;
	d100 = (w - d10000 * 10000 - d1000 * 1000)/100;
	d10 = (w - d10000 * 10000 - d1000 * 1000 - d100 * 100)/10;
	d1 = w - d10000 * 10000 - d1000 * 1000 - d100 * 100 - d10 * 10;
	dec = (d10000<<16) | (d1000<<12) | (d100<<8) | (d10<<4) | d1;
	return dec;
}

// Test 1,scib  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scib_echoback_init()
{
    // Note: Clocks were turned on to the scib peripheral
    // in the InitSysCtrl() function

 	SciBstRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	SciBstRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	SciBstRegs.SCICTL2.all =0x0003;
	SciBstRegs.SCICTL2.bit.TXINTENA =1;
	SciBstRegs.SCICTL2.bit.RXBKINTENA =1;

	SciBstRegs.SCIHBAUD    =0x0000;  // 9600 baud @LSPCLK = 37.5MHz.
	SciBstRegs.SCILBAUD    =0x0028;

	SciBstRegs.SCICTL1.all =0x00E7;  // Relinquish SCI from Reset
}

// Transmit a character from the SCI
void scib_xmit(int a)
{
    while (SciBstRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciBstRegs.SCITXBUF=a;

}

void scib_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scib_xmit(msg[i]);
        i++;
    }
}

// Initalize the SCI FIFO
void scib_fifo_init()
{
    SciBstRegs.SCIFFTX.all=0xE040;
    SciBstRegs.SCIFFRX.all=0x204f;
    SciBstRegs.SCIFFCT.all=0x0;

}

//Һ����ʼ��
void	LCDPO_Init(void)
{
	scib_fifo_init();	   // Initialize the SCI FIFO
    scib_echoback_init();  // Initalize SCI for echoback		
}

//ȫ������
void	LCDPO_Clears(void)
{
	scib_xmit(0xAA);
	scib_xmit(0x52);
	scib_xmit(0xCC);
	scib_xmit(0x33);
	scib_xmit(0xC3);
	scib_xmit(0x3C);	
}

//����ǰ��ɫ������ɫ,����������ǰ����
//fc:ǰ��ɫ��16λֵ��RGB565
//bc:����ɫ��16λֵ��RGB565
void	LCDPO_SetColor(Uint16 fc,Uint16 bc)
{
	scib_xmit(0xAA);
	scib_xmit(0x40);
	scib_xmit(fc/256);
	scib_xmit(fc%256);
	scib_xmit(bc/256);
	scib_xmit(bc%256);
	scib_xmit(0xCC);
	scib_xmit(0x33);
	scib_xmit(0xC3);
	scib_xmit(0x3C);	
}
 
void	LCDPO_DispClock(Uint16 x,Uint16 y)
{
	scib_xmit(0xAA);
	scib_xmit(0x9B);
	scib_xmit(0xFF);	//��
	scib_xmit(0x01);	//20xx-x-x 11:11:11
	scib_xmit(0x02);	//���壬8*16
	scib_xmit(0xF8);	//��ɫ
	scib_xmit(0x00);
	scib_xmit(x/256);
	scib_xmit(x%256);
	scib_xmit(y/256);
	scib_xmit(y%256);
	scib_xmit(0xCC);
	scib_xmit(0x33);
	scib_xmit(0xC3);
	scib_xmit(0x3C);	
}

//��ʾ����ASCII�ַ� 
// cmd:0x53 ��ʾ8*8����ASCII�ַ���
//     0x54 ��ʾ16*16�����ִ���GBK�� 
//	   0x55 ��ʾ32*32�����ִ���GB2312��
//	   0x6E ��ʾ12*12�����ִ���GBK�� 
//     0x6F ��ʾ24*24�����ִ���GB2312��

void LCDPO_PutChr(char ch,Uint16 x,Uint16 y)
{
	scib_xmit(0xAA);
    scib_xmit(0x54);
	scib_xmit(x/256);
	scib_xmit(x%256);
	scib_xmit(y/256);
	scib_xmit(y%256);
	scib_xmit(ch);
	scib_xmit(0xCC);
	scib_xmit(0x33);
	scib_xmit(0xC3);
	scib_xmit(0x3C);
}

//��ʾ�����ַ� 
// cmd:0x53 ��ʾ8*8����ASCII�ַ���
//     0x54 ��ʾ16*16�����ִ���GBK�� 
//	   0x55 ��ʾ32*32�����ִ���GB2312��
//	   0x6E ��ʾ12*12�����ִ���GBK�� 
//     0x6F ��ʾ24*24�����ִ���GB2312��
// x:������
// y:������
//str:Ҫ��ʾ���ַ���
void LCD_PutStr(int cmd,Uint16 x,Uint16 y,char *str)
{
	scib_xmit(0xAA);
    scib_xmit(cmd);
	scib_xmit(x/256);
	scib_xmit(x%256);
	scib_xmit(y/256);
	scib_xmit(y%256);
	scib_msg(str);
	scib_xmit(0xCC);
	scib_xmit(0x33);
	scib_xmit(0xC3);
	scib_xmit(0x3C);
}

void	LCDPO_PutHx1(char c,Uint16 x,Uint16 y)	//������ֽ�16������
{
	LCDPO_PutChr(hex_to_asc(c>>4),x,y);
	LCDPO_PutChr(hex_to_asc(c),x+8,y);
}

void	LCDPO_PutHx2(WORD w,Uint16 x,Uint16 y)	//���˫�ֽ�16������
{
	LCDPO_PutChr(hex_to_asc(w>>12),x,    y);
	LCDPO_PutChr(hex_to_asc(w>>8) ,x+8,  y);
	LCDPO_PutChr(hex_to_asc(w>>4) ,x+16, y);
	LCDPO_PutChr(hex_to_asc(w)    ,x+24, y);
}

void	LCDPO_PutHx4(LONG l,Uint16 x,Uint16 y)
{
	LCDPO_PutChr(hex_to_asc(l>>28),x,	 y);
	LCDPO_PutChr(hex_to_asc(l>>24),x+8,	 y);
	LCDPO_PutChr(hex_to_asc(l>>20),x+16, y);
	LCDPO_PutChr(hex_to_asc(l>>16),x+24, y);
	LCDPO_PutChr(hex_to_asc(l>>12),x+32, y);
	LCDPO_PutChr(hex_to_asc(l>>8) ,x+40, y);
	LCDPO_PutChr(hex_to_asc(l>>4) ,x+48, y);
	LCDPO_PutChr(hex_to_asc(l)    ,x+56, y);
}

void	LCDPO_PutDc1(BYTE b,Uint16 x,Uint16 y)
{
	WORD	w;
	
	w = hex2_to_decimal(b);
	
	LCDPO_PutChr(hex_to_asc(w>>8),x	  , y);
	LCDPO_PutChr(hex_to_asc(w>>4),x+8 , y);
	LCDPO_PutChr(hex_to_asc(w)	 ,x+16, y);
}

void	LCDPO_PutDc2(WORD w,Uint16 x,Uint16 y)
{
	LONG	l;
	
	l = hex4_to_decimal(w);
	
	LCDPO_PutChr(hex_to_asc(l>>16) ,x	,y);
	LCDPO_PutChr(hex_to_asc(l>>12) ,x+8 ,y);
	LCDPO_PutChr(hex_to_asc(l>>8)  ,x+16,y);
	LCDPO_PutChr(hex_to_asc(l>>4)  ,x+24,y);
	LCDPO_PutChr(hex_to_asc(l)	   ,x+32,y);
}


