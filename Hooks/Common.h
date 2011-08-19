#pragma once
#include "../[Common]/CLIWrapper.h"
#include "../[Common]/HandshakeStructs.h"
#include "../WindowManager.h"
#include "../resource.h"
#include "../HallofFame.h"
#include "../CSInterop.h"
#include "../WindowManager.h"
#include "../Exports.h"

class TESForm;
class TESObjectCELL;
class TESWorldSpace;
class INISetting;

#pragma warning(disable:4005)

namespace Hooks
{
	extern FARPROC		g_WindowHandleCallAddr;

	using namespace	MemoryHandler;

	void __stdcall GetWindowTextAddress(void);
	void __stdcall CreateDialogParamAddress(void);
	void __stdcall EndDialogAddress(void);
	void __stdcall EnableWindowAddress(void);
	void __stdcall GetWindowLongAddress(void);
	void __stdcall CreateWindowExAddress(void);
	void __stdcall SetWindowTextAddress(void);
	void __stdcall SendDlgItemMessageAddress(void);
	void __stdcall SendMessageAddress(void);
	void __stdcall TrackPopupMenuAddress(void);
	void __stdcall ShowWindowAddress(void);
	void __stdcall MessageBoxAddress(void);
	void __stdcall GetClientRectAddress(void);

	UInt32 __stdcall IsControlKeyDown(void);
}