#include "framework.h"
#include "woolmap.h"

CWoolMap::CWoolMap(void)
	: m_Height(0)
	, m_Width(0)
	, m_pData(NULL)
{
}

CWoolMap::~CWoolMap(void)
{
}

bool CWoolMap::TestMap(long x, long y)
{
	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
	{
		return false;
	}
	return m_pData[y * m_Width + x];
}

void CWoolMap::GetMapSize(long& w, long& h)
{
	w = m_Width;
	h = m_Height;
}

struct file_header
{
	unsigned long unknow_1[2];
	unsigned long map_width;
	unsigned long map_height;
	unsigned long unknow_2[4];
};

void CWoolMap::LoadMap(LPCTSTR lpszPathName)
{
	CFile file;
	file.Open(lpszPathName, CFile::modeRead);
	file_header fh;
	file.Read(&fh, sizeof(fh));
	m_Width = fh.map_width;
	m_Height = fh.map_height;
	char* p;
	char b;
	long len = file.GetLength() - sizeof(fh);
	p = new char[len];
	long i = 0;
	long j = 0;
	file.Read(p, len);
	file.Close();
	if (m_pData != NULL)delete[]m_pData;
	m_pData = new bool[m_Width * m_Height];
	while (i < len)
	{
		b = p[i];
		if (b >= 0x0 && b <= 0x1)
		{
			i += 1;
		}
		else if (b >= 0x2 && b <= 0x5)
		{
			i += 3;
		}
		else if (b >= 0x6 && b <= 0x9)
		{
			i += 5;
		}
		else if (b >= 0xa && b <= 0xd)
		{
			i += 7;
		}
		else if (b >= 0xe && b <= 0xf)
		{
			i += 9;
		}
		else if (b >= 0x10 && b <= 0x11)
		{
			i += 2;
		}
		else if (b >= 0x12 && b <= 0x15)
		{
			i += 4;
		}
		else if (b >= 0x16 && b <= 0x19)
		{
			i += 6;
		}
		else if (b >= 0x1a && b <= 0x1d)
		{
			i += 8;
		}
		else if (b >= 0x1e && b <= 0x1f)
		{
			i += 10;
		}
		else
			break;
		if ((b & 1) == 0)
			m_pData[j] = true;
		else
			m_pData[j] = false;
		j++;
	}
	delete[]p;
}
