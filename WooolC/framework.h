#pragma once
#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#include <afxsock.h>		// MFC 网络组件

typedef BYTE u8;
typedef WORD u16;
typedef DWORD u32;

#define STRING_LENGTH (1024)
#define BUF_LENGTH (0x2000)
int WINAPI Encode6BitBuf(const unsigned char* pszSrc, char* pszDest, int nSrcLen, int nDestLen);
int WINAPI Decode6BitBuf(const char* pszSrc, char* pszDest, int nDestLen);
int hex2int(char c);
void LogSystem(LPCTSTR log, COLORREF tc = RGB(0xff, 0xff, 0xff));
void LogChat(LPCTSTR log, COLORREF tc = RGB(0, 0, 0), COLORREF bc = RGB(0xff, 0xff, 0xff));
int memprintf(char* dest, const unsigned char* src, unsigned long len);
extern const int ColorTable[];


//传奇消息数据结构
struct MMSG
{
	union
	{
		DWORD	dwFlag;
		struct
		{
			WORD	wa;
			WORD	wb;
		};
	};
	WORD	wCmd;
	WORD	w1;
	WORD	w2;
	WORD	w3;
	//char __u[20];
};
//封包中的装备结构
struct item_in_buf
{
	u16 idx;
	u8 magic;
	char name[14];
	u8 stdmod;
	u8 shape;
	u8 weight;
	u8 anicount;
	u8 source;
	u8 reserved;
	u8 unknow;
	u16 looks;
	u16 default_dura;
	u8 ac;
	u8 ac_max;
	u8 mac;
	u8 mac_max;
	u8 dc;
	u8 dc_max;
	u8 mc;
	u8 mc_max;
	u8 sc;
	u8 sc_max;
	u8 need;
	u8 need_level;
	u16 unknow_2;
	u32 price;
	u32 id;
	u16 dura;
	u16 dura_max;
};
//封包中的背包物品结构
struct bagitem_in_buf
{
	u8 magic;
	char name[14];
	u8 stdmod;
	u8 shape;
	u8 weight;
	u8 anicount;
	u8 source;
	u8 reserved;
	u8 unknow;
	u16 looks;
	u16 default_dura;
	u8 ac;
	u8 ac_max;
	u8 mac;
	u8 mac_max;
	u8 dc;
	u8 dc_max;
	u8 mc;
	u8 mc_max;
	u8 sc;
	u8 sc_max;
	u8 need;
	u8 need_level;
	u16 unknow_2;
	u32 price;
	u32 id;
	u16 dura;
	u16 dura_max;
};
struct magic_in_buf
{
	unsigned char key;
	unsigned char level;
	unsigned short unknow_1;
	unsigned long exp;
	unsigned short magic_id;
	unsigned char name_len;
	char name[12];
	unsigned char effect_type;
	unsigned char effect;
	unsigned short spell;
	unsigned short power;
	unsigned char unkonw_3;
	unsigned char need_l1;
	unsigned char need_l2;
	unsigned char need_l3;
	unsigned char unknow_2[3];
	unsigned long exp_need[3];
};
struct MMSGSETCHARINFO
{
	DWORD	dwGold;
	WORD	wCmd;
	BYTE	bProf;
	BYTE	bHair;
	BYTE	bSex;
	BYTE	bOO;
	WORD	wUnknow;
	BYTE	bLevel;
	BYTE	bUnknow;

	BYTE	ACLow;
	BYTE	ACHi;

	BYTE	MACLow;
	BYTE	MACHi;

	BYTE	DCLow;
	BYTE	DCHi;

	BYTE	MCLow;
	BYTE	MCHi;

	BYTE	SCLow;
	BYTE	SCHi;

	WORD	Hp;
	WORD	Mp;
	WORD	MaxHp;
	WORD	MaxMp;
	DWORD	dwUnknow;
	DWORD	Exp;
	DWORD	MaxExp;
	WORD	BagWeight;
	WORD	MaxBagWeight;
	BYTE	BodyWeight;
	BYTE	MaxBodyWeight;
	BYTE	HandWeight;
	BYTE	MaxHandWeight;
};

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC 支持功能区和控制条