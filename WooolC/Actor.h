#pragma once

class CActor
{
public:
	CActor(void);
	~CActor(void);
	DWORD id;
	DWORD x;
	DWORD y;
	CString name;
	unsigned char type;
};
