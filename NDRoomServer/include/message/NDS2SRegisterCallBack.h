#ifndef __ROOMSERVER_ND_S2S_REGISTER_CALLBACK_H__
#define __ROOMSERVER_ND_S2S_REGISTER_CALLBACK_H__



#include "main/local/NDPreCompiler.h"

class NDS2SRegisterCallBack : public NDProtocolCallBack
{
public:
	NDS2SRegisterCallBack(void);
	~NDS2SRegisterCallBack(void);

	NDBool process( NDIStream& rIStream, NDProtocolHeader& protocolHeader );

private:

	NDBool rs2wsRegisterResDispose( NDIStream& rIStream, NDProtocolHeader& header );
	NDBool rs2gsRegisterResDispose( NDIStream& rIStream, NDProtocolHeader& header );
	NDBool gws2rsRegisterReqDispose( NDIStream& rIStream, NDProtocolHeader& header );
};

#endif
