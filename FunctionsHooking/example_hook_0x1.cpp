#include "hooklib.hpp"

Utility::HookManager * pHookManager = 0;

void MsgBoxExt( Utility::x86Registers* pRegs )
{
	puts( "Here i am fucker." );
	pRegs->stack[ 3 ] = ( void* )"AIDS";
	// will replace FUCKIN LUZER with AIDS
}

uintptr_t msg_box_return = 0;
int __stdcall MsgBox( int a , void* b, void* c, int d )
{
	puts( "Here i am fucker." );
	typedef int  ( __stdcall *mbox ) ( int, void*, void*, int );
	auto pFN = ( mbox ) msg_box_return;

	return pFN( a, b, c, d );
}

int main( )
{
	pHookManager = new Utility::HookManager( );

	//pHookManager->HookFunctionExt( ( uintptr_t ) MessageBoxA, ( uintptr_t ) MsgBoxExt );                                  // Crasha!
	msg_box_return = pHookManager->HookFunction( ( uintptr_t ) MessageBoxA, ( uintptr_t ) MsgBox );
	MessageBoxA( 0, "FUCKIN LUZER", "XD", MB_OKCANCEL );
	pHookManager->UnhookFunction( ( uintptr_t ) MessageBoxA );
	MessageBoxA( 0, "FUCKIN LUZER", "XD", MB_OKCANCEL );


	getchar( );
}