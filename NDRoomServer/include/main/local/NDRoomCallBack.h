#ifndef __ROOMSERVER_ND_ROOM_CALL_BACK_H__
#define __ROOMSERVER_ND_ROOM_CALL_BACK_H__

#include "NDPreCompiler.h"

#include "message/NDS2SRegisterCallBack.h"


class NDRoomCallBack : public NDProtocolCallBack
{
public:
	NDRoomCallBack(void);
	~NDRoomCallBack(void);

	NDBool process( NDIStream& rIStream, NDProtocolHeader& protocolHeader );

private:
	//client ping req protocol dispose;
	NDBool pingProtocolDispose( NDIStream& rIStream, NDProtocolHeader& protocolHeader );
	//client disconnect dispose;
	NDBool disconnectNotifyDispose( NDIStream& rIStream, NDProtocolHeader& protocolHeader );

	//server ping res protocol dispose;
	NDBool pingResProtocolDispose( NDIStream& rIStream, NDProtocolHeader& protocolHeader );

	//NDBool timerNotifyDispose( NDIStream& rIStream, NDProtocolHeader& protocolHeader );

private:
	NDS2SRegisterCallBack		m_NDS2SRegisterCallBack;
	//NDC2LCallBack				m_NDC2LCallBack;
	//NDL2ACallBack				m_NDL2ACallBack;
	//NDClient2LCallBack		m_NDClient2LCallBack;
};

#endif
