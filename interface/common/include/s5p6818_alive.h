/*  
 *S5P6818 SFR address define
 *hqyj
 *2017.10.1
 *version: 1.0
*/

#ifndef __S5P6818_ALIVE_H__
#define __S5P6818_ALIVE_H__

/************** ALIVE ****************/
typedef struct {
	uint32 ALIVEPWRGATEREG;							///< 0x00 : Alive Power Gating Register
	uint32 ALIVEGPIOASYNCDETECTMODERSTREG0;			///< 0x04 : Alive GPIO ASync Detect Mode Reset Register0
	uint32 ALIVEGPIOASYNCDETECTMODESETREG0;			///< 0x08 : Alive GPIO ASync Detect Mode Set Register0
	uint32 ALIVEGPIOLOWASYNCDETECTMODEREADREG;		///< 0x0C : Alive GPIO Low ASync Detect Mode Read Register

	uint32 ALIVEGPIOASYNCDETECTMODERSTREG1;			///< 0x10 : Alive GPIO ASync Detect Mode Reset Register1
	uint32 ALIVEGPIOASYNCDETECTMODESETREG1;			///< 0x14 : Alive GPIO ASync Detect Mode Set Register1
	uint32 ALIVEGPIOHIGHASYNCDETECTMODEREADREG;		///< 0x18 : Alive GPIO High ASync Detect Mode Read Register

	uint32 ALIVEGPIODETECTMODERSTREG0;				///< 0x1C : Alive GPIO Detect Mode Reset Register0
	uint32 ALIVEGPIODETECTMODESETREG0;				///< 0x20 : Alive GPIO Detect Mode Reset Register0
	uint32 ALIVEGPIOFALLDETECTMODEREADREG;			///< 0x24 : Alive GPIO Falling Edge Detect Mode Read Register

	uint32 ALIVEGPIODETECTMODERSTREG1;				///< 0x28 : Alive GPIO Detect Mode Reset Register1
	uint32 ALIVEGPIODETECTMODESETREG1;				///< 0x2C : Alive GPIO Detect Mode Reset Register1
	uint32 ALIVEGPIORISEDETECTMODEREADREG;			///< 0x30 : Alive GPIO Rising Edge Detect Mode Read Register

	uint32 ALIVEGPIODETECTMODERSTREG2;				///< 0x34 : Alive GPIO Detect Mode Reset Register2
	uint32 ALIVEGPIODETECTMODESETREG2;				///< 0x38 : Alive GPIO Detect Mode Reset Register2
	uint32 ALIVEGPIOLOWDETECTMODEREADREG;			///< 0x3C : Alive GPIO Low Level Detect Mode Read Register

	uint32 ALIVEGPIODETECTMODERSTREG3;				///< 0x40 : Alive GPIO Detect Mode Reset Register3
	uint32 ALIVEGPIODETECTMODESETREG3;				///< 0x44 : Alive GPIO Detect Mode Reset Register3
	uint32 ALIVEGPIOHIGHDETECTMODEREADREG;			///< 0x48 : Alive GPIO High Level Detect Mode Read Register

	uint32 ALIVEGPIODETECTENBRSTREG;				///< 0x4C : Alive GPIO Detect Enable Reset Register
	uint32 ALIVEGPIODETECTENBSETREG;				///< 0x50 : Alive GPIO Detect Enable Set Register
	uint32 ALIVEGPIODETECTENBREADREG;				///< 0x54 : Alive GPIO Detect Enable Read Register

	uint32 ALIVEGPIOINTENBRSTREG;					///< 0x58 : Alive GPIO Interrupt Enable Reset Register
	uint32 ALIVEGPIOINTENBSETREG;					///< 0x5C : Alive GPIO Interrupt Enable Set Register
	uint32 ALIVEGPIOINTENBREADREG;					///< 0x60 : Alive GPIO Interrupt Enable Read Register

	uint32 ALIVEGPIODETECTPENDREG;					///< 0x64 : Alive GPIO Detect Pending Register

	uint32 ALIVESCRATCHRSTREG;						///< 0x68 : Alive Scratch Reset Register
	uint32 ALIVESCRATCHSETREG;						///< 0x6C : Alive Scratch Set Register
	uint32 ALIVESCRATCHREADREG;						///< 0x70 : Alive Scratch Read Register

	uint32 ALIVEGPIOPADOUTENBRSTREG;				///< 0x74 : Alive GPIO PAD Out Enable Reset Register
	uint32 ALIVEGPIOPADOUTENBSETREG;				///< 0x78 : Alive GPIO PAD Out Enable Set Register
	uint32 ALIVEGPIOPADOUTENBREADREG;				///< 0x7C : Alive GPIO PAD Out Enable Read Register

	uint32 ALIVEGPIOPADPULLUPRSTREG;				///< 0x80 : Alive GPIO PAD Pullup Reset Register
	uint32 ALIVEGPIOPADPULLUPSETREG;				///< 0x84 : Alive GPIO PAD Pullup Set Register
	uint32 ALIVEGPIOPADPULLUPREADREG;				///< 0x88 : Alive GPIO PAD Pullup Read Register

	uint32 ALIVEGPIOPADOUTRSTREG;					///< 0x8C : Alive GPIO PAD Out Reset Register
	uint32 ALIVEGPIOPADOUTSETREG;					///< 0x90 : Alive GPIO PAD Out Set Register
	uint32 ALIVEGPIOPADOUTREADREG;					///< 0x94 :    Alive GPIO PAD Out Read Register

	uint32 VDDCTRLRSTREG;							///< 0x98 : VDD Control Reset Register
	uint32 VDDCTRLSETREG;							///< 0x9C : VDD Control Set Register
	uint32 VDDCTRLREADREG;							///< 0xA0 : VDD Control Read Register

	uint32 CLEARWAKEUPSTATUS;						///< 0x0A4 :  wCS[41]
	uint32 WAKEUPSTATUS;							///< 0x0A8 :  wCS[42]

	uint32 ALIVESCRATCHRST1;						///< 0x0AC :  wCS[43]
	uint32 ALIVESCRATCHSET1;						///< 0x0B0 :  wCS[44]
	uint32 ALIVESCRATCHVALUE1;						///< 0x0B4 :  wCS[45]

	uint32 ALIVESCRATCHRST2;						///< 0x0B8 :  wCS[46]
	uint32 ALIVESCRATCHSET2;						///< 0x0BC :  wCS[47]
	uint32 ALIVESCRATCHVALUE2;						///< 0x0C0 :  wCS[48]

	uint32 ALIVESCRATCHRST3;						///< 0x0C4 :  wCS[49]
	uint32 ALIVESCRATCHSET3;						///< 0x0C8 :  wCS[50]
	uint32 ALIVESCRATCHVALUE3;						///< 0x0CC :  wCS[51]

	uint32 ALIVESCRATCHRST4;						///< 0x0D0 :  wCS[52]
	uint32 ALIVESCRATCHSET4;						///< 0x0D4 :  `wCS[53]
	uint32 ALIVESCRATCHVALUE4;						///< 0x0D8 :  wCS[54]

	uint32 ALIVESCRATCHRST5;						///< 0x0DC :  wCS[55]
	uint32 ALIVESCRATCHSET5;						///< 0x0E0 :  wCS[56]
	uint32 ALIVESCRATCHVALUE5;						///< 0x0E4 :  wCS[57]

	uint32 ALIVESCRATCHRST6;						///< 0x0E8 :  wCS[58]
	uint32 ALIVESCRATCHSET6;						///< 0x0EC :  wCS[59]
	uint32 ALIVESCRATCHVALUE6;						///< 0x0F0 :  wCS[60]

	uint32 ALIVESCRATCHRST7;						///< 0x0F4 :  wCS[61]
	uint32 ALIVESCRATCHSET7;						///< 0x0F8 :  wCS[62]
	uint32 ALIVESCRATCHVALUE7;						///< 0x0FC :  wCS[63]

	uint32 ALIVESCRATCHRST8;						///< 0x100 :  wCS[64]
	uint32 ALIVESCRATCHSET8;						///< 0x104 :  wCS[65]
	uint32 ALIVESCRATCHVALUE8;						///< 0x108 :  wCS[66]

	uint32 VDDOFFCNTVALUERST;						///< 0x10C :  wCS[67]
	uint32 VDDOFFCNTVALUESET;						///< 0x110 :  wCS[68]

	uint32 VDDOFFCNTVALUE0;							///< 0x114 :  wCS[69]
	uint32 VDDOFFCNTVALUE1;							///< 0x118 :  wCS[70]

	uint32 ALIVEGPIOINPUTVALUE;						///< 0x11C :  wCS[71]

}alive;
#define  ALIVE     (* (volatile alive *)0xC0010800)


#endif	// __S5P6818_ALIVE_H__
