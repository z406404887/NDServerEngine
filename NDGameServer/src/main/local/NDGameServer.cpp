
#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


#include "main/local/NDGameServer.h"

initialiseSingleton(NDGameServer);

NDRefCounted<NDServerManager>	refNDServerManager( new NDServerManager );
NDRefCounted<NDGameServer>		refNDGameServer( new NDGameServer );

#ifdef	WIN32
BOOL WINAPI handlerRoutine( DWORD dwCtrlType );
#endif

void	exceptionDispose( void *pParam );
int		mainWapper( int argc, char** argv );

int main(int argc, char** argv)
{
	ND_EXCEPTION_PROTECTED_BEGIN()

	mainWapper( argc, argv );

	ND_EXCEPTION_PROTECTED_CATCH( sNDGameServer.getDumpFilePath(), exceptionDispose )

	return 0;
}


int mainWapper( int argc, char** argv )
{
#ifdef	WIN32
	//for output memory leak report;
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	if( !SetConsoleCtrlHandler( (PHANDLER_ROUTINE)handlerRoutine, TRUE ) ) 
	{
		NDLOG_ERROR( " SetConsoleCtrlHandler failed! " )
		return 1;
	}
#endif

	if ( argc <= 1 )
	{
		NDLOG_ERROR( " argc number less than or equal 1. " )
		return 1;
	}

	NDInt32 nServerID = atoi( argv[1] );
	if ( nServerID <= 0 || nServerID > 200 )
	{
		NDLOG_ERROR( " nServerID less than zero or greater than 200. " )
		return 1;
	}

	//read config file and initialize;
	if ( NDFalse == sNDGameServer.initialize( GAME_SERVER, nServerID, "ServerConfig.xml") )
	{
		NDLOG_ERROR( " NDGameServer initialize failed! " )
		return 1;
	}

	//start server service;
	if ( NDFalse == NDServerManager::getSingleton().startServer( NDGameServer::getSingletonPtr() ) )
	{
		NDLOG_ERROR( " NDGameServer startServer failed! " )
		return 1;
	}

	//set server started state;
	sNDGameServer.setState( NDLocalServer::eServState_Started );


	NDServerManager::getSingleton().mainLoop();

	return 0;
}


void exceptionDispose( void *pParam )
{
	NDLOG_ERROR( " exception has generated! " )
	sNDGameServer.setState( NDLocalServer::eServState_Stopping );
	sNDGameServer.logMgr()->flush();
}

#ifdef	WIN32
//�ص�����;
BOOL WINAPI handlerRoutine( DWORD dwCtrlType )
{
	NDGameServer* pGameServer		= NDGameServer::getSingletonPtr();
	NDServerManager* pServerMgr		= NDServerManager::getSingletonPtr();
	if ( NULL == pGameServer || NULL == pServerMgr )
	{
		return FALSE;
	}

	pGameServer->setState( NDLocalServer::eServState_Stopping );

	switch( dwCtrlType )
	{
	case CTRL_C_EVENT:
		NDLOG_WARNING( " CTRL_C_EVENT " )
		break;
	case CTRL_BREAK_EVENT:
		NDLOG_WARNING( " CTRL_BREAK_EVENT " )
		break;
	case CTRL_CLOSE_EVENT:
		NDLOG_WARNING( " CTRL_CLOSE_EVENT " )
		break;
	case CTRL_LOGOFF_EVENT:
		NDLOG_WARNING( " CTRL_LOGOFF_EVENT " )
		break;
	case CTRL_SHUTDOWN_EVENT:
		NDLOG_WARNING( " CTRL_SHUTDOWN_EVENT " )
		break;
	default:
		NDLOG_WARNING( " default " )
		break;
	}

	pGameServer->logMgr()->close();

	SAFE_DELETE( pServerMgr )
	SAFE_DELETE( pGameServer )

	return TRUE;
}
#endif

