#include "framework.h"
#include "ClientSocket.h"
#include "MainFrm.h"

// CClientSocket
CClientSocket::CClientSocket(CWnd* pNotifyWnd)
{
	pWnd = pNotifyWnd;
	CClientSocket* LastSocket = ((CMainFrame*)pWnd)->m_pSocket;
	((CMainFrame*)pWnd)->m_pSocket = this;
	if (LastSocket != NULL)
	{
		LastSocket->Close();
		delete LastSocket;
	}
}

CClientSocket::~CClientSocket()
{
	if (((CMainFrame*)pWnd)->m_pSocket == this)
	{
		((CMainFrame*)pWnd)->m_pSocket = NULL;
	}
}


// CClientSocket ³ÉÔ±º¯Êý

void CClientSocket::OnConnect(int nErrorCode)
{
	if (pWnd)
	{
		if (nErrorCode == 0)
			((CMainFrame*)pWnd)->m_pSocket = this;
		((CMainFrame*)pWnd)->OnConnect(nErrorCode, this);
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSocket::OnReceive(int nErrorCode)
{
	if (pWnd)((CMainFrame*)pWnd)->OnReceive(nErrorCode, this);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	if (pWnd)((CMainFrame*)pWnd)->OnClose(nErrorCode, this);
	CAsyncSocket::OnClose(nErrorCode);
}

int CClientSocket::SendString(LPCTSTR string)
{
	return Send(string, strlen(string));
}

int CClientSocket::SendMsg(MMSG* msg, const char* data)
{
	char buf[BUF_LENGTH];
	char buf2[BUF_LENGTH];
	ZeroMemory(buf, BUF_LENGTH);
	ZeroMemory(buf2, BUF_LENGTH);
	int pos = Encode6BitBuf((unsigned char*)msg, buf, 12/*sizeof(MMSG)*/, BUF_LENGTH);
	pos += Encode6BitBuf((unsigned char*)data, buf + pos, strlen(data), BUF_LENGTH - pos);
	sprintf(buf2, "#%c%s!", ((CMainFrame*)pWnd)->m_chFlag, buf);
	((CMainFrame*)pWnd)->m_chFlag++;
	if (((CMainFrame*)pWnd)->m_chFlag > '9')((CMainFrame*)pWnd)->m_chFlag = '1';
	return SendString(buf2);
}