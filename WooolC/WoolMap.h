#pragma once
#include "framework.h"

class CWoolMap
{
public:
	CWoolMap(void);
	~CWoolMap(void);
protected:
	long m_Height;
	long m_Width;
	bool* m_pData;
public:
	bool TestMap(long x, long y);
	void GetMapSize(long& w, long& h);
	void LoadMap(LPCTSTR lpszPathName);
};
