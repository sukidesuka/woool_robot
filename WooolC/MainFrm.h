
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

#include "framework.h"
#include "ClientSocket.h"
#include "WoolMap.h"
#include "Actor.h"
#include "ChildView.h"

//游戏人物状态
struct MAXMININFO
{
	int min;
	int max;
};
struct LOWHIINFO
{
	int low;
	int hi;
};
struct __DWORD
{
	WORD l;
	WORD h;
};
class CHARACTERINFO
{
public:
	CString		Name;
	DWORD		dwServerId;
	int			prof;
	int			sex;
	int			level;
	int			hair;
	int			pos_x;
	int			pos_y;
	long		gold;
	LOWHIINFO	AC;
	LOWHIINFO	MAC;
	LOWHIINFO	DC;
	LOWHIINFO	MC;
	LOWHIINFO	SC;
	MAXMININFO	HandWeight;
	MAXMININFO	BodyWeight;
	MAXMININFO	BagWeight;
	MAXMININFO	Hp;
	MAXMININFO	Mp;
	MAXMININFO	Exp;
	int			Zhunque;
	int			Minjie;
	int			MagicAgainst;
	int			PoisonAgainst;
	int			PoisonRecover;
	int			HpRecover;
	int			MpRecover;

	CHARACTERINFO()
	{
		Name = "";
		dwServerId = 0;
		prof = 0;
		sex = 0;
		level = 0;
		hair = 0;
		pos_x = 0;
		pos_y = 0;
		gold = 0;
		AC.hi = 0;
		AC.low = 0;
		MAC.hi = 0;
		MAC.low = 0;
		DC.hi = 0;
		DC.low = 0;
		MC.hi = 0;
		MC.low = 0;
		SC.hi = 0;
		SC.low = 0;
		HandWeight.max = 0;
		HandWeight.min = 0;
		BodyWeight.max = 0;
		BodyWeight.min = 0;
		BagWeight.max = 0;
		BagWeight.min = 0;
		Hp.max = 0;
		Hp.min = 0;
		Mp.max = 0;
		Mp.min = 0;
		Exp.max = 0;
		Exp.min = 0;
		Zhunque = 0;
		Minjie = 0;
		MagicAgainst = 0;
		PoisonAgainst = 0;
		PoisonRecover = 0;
		HpRecover = 0;
		MpRecover = 0;
	};
};

enum CHAR_INFO_INDEX
{
	CI_NAME,
	CI_SEX,
	CI_GOLD,//金币
	CI_SPOUSE,//配偶
	CI_HP,
	CI_MP,
	CI_PROF,//职业
	CI_LEVEL,//等级
	CI_AC,//防
	CI_MAC,//魔防
	CI_DC,//攻击力
	CI_MC,//魔法力
	CI_SC,//道术
	CI_EXP,//经验
	CI_BAGWEIGHT,//背包负重
	CI_BODYWEIGHT,//负重
	CI_HANDWEIGHT,//腕力
	CI_ZHUNQUE,//准确
	CI_MINJIE,//敏捷
};

struct item
{
	CString name;
	DWORD id;
	LOWHIINFO dc;
	LOWHIINFO mc;
	LOWHIINFO sc;
	LOWHIINFO ac;
	LOWHIINFO mac;
	LOWHIINFO dura;
	int need_level;
	int weight;
	int need;
};

struct magic_item
{
	CString name;
	WORD magic_id;
	unsigned int level;
	unsigned long exp;
	unsigned long exp_need[3];
};


#define MAX_BAG_ITEM_COUNT (100)
#define MAX_MAGIC_COUNT (100)
#define MAX_BODY_ITEM_COUNT (100)

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame() noexcept;
	CHARACTERINFO m_CharSelf;
protected:
	DECLARE_DYNAMIC(CMainFrame)

	// 特性
public:

	// 操作
public:

	// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar        m_wndToolBar;
	CChildView		m_wndView;
	CPtrList		m_ActorList;

	// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLoginGame();
	DECLARE_MESSAGE_MAP()

public:
	void OnConnect(int nErrorCode, CClientSocket* socket);
	void OnReceive(int nErrorCode, CClientSocket* socket);
	void OnClose(int nErrorCode, CClientSocket* socket);
	BOOL GameLoop(const MMSG& msg, const char* data, CClientSocket* socket);
	CString m_SID;
	CWoolMap m_GameMap;
	CString m_CharacterName;

public:
	CClientSocket* m_pSocket;
	void Walk(int dir);
	void Run(int dir);

protected:
	bool m_IsMoveRun;

public:
	unsigned char m_chFlag;
	long m_GameStatus;
	afx_msg void OnDestroy();
	void ActorAppear(DWORD idx, long x, long y, LPCTSTR name, unsigned char type);
	void ActorDisappear(DWORD idx);
	CActor* GetActorByIndex(DWORD idx);
	item m_BodyItem[MAX_BAG_ITEM_COUNT];
	item m_BagItem[MAX_BODY_ITEM_COUNT];
	magic_item	m_MagicList[MAX_MAGIC_COUNT];
	CString m_MapCaption;
	CString m_MapFilename;
	BOOL OnIdle(LONG lCount);
	long* m_DStarArray;
	long m_DStarWidth;
	long m_DStarHeight;
	CString ParseActorName(CString name);

	// 登录服务器所需要的定义
	CString m_server_host;
	int m_server_port;
	CString m_server_name;
	CString m_game_path;

	CString m_account;
	CString m_password;
};
