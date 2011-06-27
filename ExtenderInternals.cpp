#include "ExtenderInternals.h"
#include "Exports.h"
#include "[Common]\CLIWrapper.h"
#include "ElapsedTimeCounter.h"

std::string							g_INIPath;
std::string							g_AppPath;
std::string							g_DLLPath;
bool								g_PluginPostLoad = false;
INI::INIManager*					g_INIManager = new CSEINIManager();
INI::INIEditGUI*					g_INIEditGUI = new INI::INIEditGUI();

char								g_TextBuffer[0x200] = {0};
HINSTANCE							g_DLLInstance = NULL;

ElapsedTimeCounter					g_RenderWindowTimeManager;

TES**								g_TES = (TES**)0x00A0ABB0;
TESDataHandler**					g_TESDataHandler = (TESDataHandler **)0x00A0E064;

const HINSTANCE*					g_TESCS_Instance = (HINSTANCE*)0x00A0AF1C;
const DLGPROC						g_ScriptEditor_DlgProc = (DLGPROC)0x004FE760;
const DLGPROC						g_FormUseReport_DlgProc = (DLGPROC)0x00433FE0;
const DLGPROC						g_TESDialogFormEdit_DlgProc = (DLGPROC)0x00447580;
const DLGPROC						g_TESDialogFormIDListView_DlgProc = (DLGPROC)0x00448820;
const DLGPROC						g_TESDialogSelectReference_DlgProc = (DLGPROC)0x0044D470;

HWND*								g_HWND_RenderWindow = (HWND*)0x00A0AF28;
HWND*								g_HWND_ObjectWindow = (HWND*)0x00A0AF44;
HWND*								g_HWND_CellView = (HWND*)0x00A0AF4C;
HWND*								g_HWND_CSParent = (HWND*)0x00A0AF20;
HWND*								g_HWND_AIPackagesDlg = (HWND*)0x00A0AFD8;
HWND*								g_HWND_ObjectWindow_FormList = (HWND*)0x00A0BAA0;
HWND*								g_HWND_ObjectWindow_Tree = (HWND*)0x00A0BAA4;
HWND*								g_HWND_MainToolbar = (HWND*)0x00A0AFD0;
HWND*								g_HWND_QuestWindow = (HWND*)0x00A0B034;

TBBUTTON*							g_MainToolbarButtonArray = (TBBUTTON*)0x009EAD50;
Setting*							g_LocalMasterPath = (Setting*)0x009ED710;
char**								g_TESActivePluginName = (char**)0x00A0AF00;
UInt8*								g_TESCSAllowAutoSaveFlag = (UInt8*)0x00A0B628;
UInt8*								g_TESCSExittingCSFlag = (UInt8*)0x00A0B63C;
TESRenderSelection**				g_TESRenderSelectionPrimary = (TESRenderSelection**)0x00A0AF60;
HMENU*								g_RenderWindowPopup = (HMENU*)0x00A0BC40;
void*								g_ScriptCompilerUnkObj = (void*)0x00A0B128;
TESWaterForm**						g_DefaultWater = (TESWaterForm**)0x00A137CC;
TESObjectREFR**						g_PlayerRef = (TESObjectREFR**)0x00A0E088;
GenericNode<Archive>**				g_LoadedArchives = (GenericNode<Archive>**)0x00A0DD8C;
UInt8*								g_Flag_ObjectWindow_MenuState = (UInt8*)0x00A0AF40;
UInt8*								g_Flag_CellView_MenuState = (UInt8*)0x00A0AF48;
CRITICAL_SECTION*					g_ExtraListCS = (CRITICAL_SECTION*)0x00A0DA80;
TESSound**							g_FSTSnowSneak = (TESSound**)0x00A110F0;
BSTextureManager**					g_TextureManager = (BSTextureManager**)0x00A8E760;
NiDX9Renderer**						g_CSRenderer = (NiDX9Renderer**)0x00A0F87C;
UInt8*								g_RenderWindowUpdateViewPort = (UInt8*)0x00A0BC4D;
UInt32*								g_RenderWindowStateFlags = (UInt32*)0x00A0B058;
FileFinder**						g_FileFinder = (FileFinder**)0x00A0DE8C;
ResponseEditorData**				g_ResponseEditorData = (ResponseEditorData**)0x00A10E2C;
GameSettingCollection*				g_GMSTCollection = (GameSettingCollection*)0x00A10198;
void*								g_GMSTMap = (void*)0x00A102A4;
void**								g_IdleFormTree = (void**)0x00A107F8;
TESRenderUndoStack**				g_TESRenderUndoStack = (TESRenderUndoStack**)0x00A0B124;
TESObjectREFR**						g_TESPreviewControlRef = (TESObjectREFR**)0x00A0B054;

float*								g_RenderWindowRefMovementSpeed = (float*)0x00A0B078;
float*								g_RenderWindowSnapGridDistance = (float*)0x00A0B060;
float*								g_RenderWindowRefRotationSpeed = (float*)0x00A0B070;
float*								g_RenderWindowSnapAngle = (float*)0x00A0B068;
float*								g_RenderWindowCameraRotationSpeed = (float*)0x00A0B080;
float*								g_RenderWindowCameraZoomSpeed = (float*)0x00A0B088;
float*								g_RenderWindowCameraPanSpeed = (float*)0x00A0B090;

UInt8*								g_RenderWindowPathGridEditModeFlag = (UInt8*)0x00A0BC5C;
GenericNode<TESPathGridPoint>*		g_RenderWindowSelectedPathGridPoints = (GenericNode<TESPathGridPoint>*)0x00A0AF68;

TESForm**							g_DoorMarker = (TESForm**)0x00A13470;
TESForm**							g_NorthMarker = (TESForm**)0x00A13484;
TESForm**							g_TravelMarker = (TESForm**)0x00A13480;
TESForm**							g_MapMarker = (TESForm**)0x00A13474;
TESForm**							g_HorseMarker = (TESForm**)0x00A134A0;

LPDIRECT3DTEXTURE9*					g_LODD3DTexture32x = (LPDIRECT3DTEXTURE9*)0x00A0AAC4;
LPDIRECT3DTEXTURE9*					g_LODD3DTexture64x = (LPDIRECT3DTEXTURE9*)0x00A0AAC0;
LPDIRECT3DTEXTURE9*					g_LODD3DTexture128x = (LPDIRECT3DTEXTURE9*)0x00A0AABC;
LPDIRECT3DTEXTURE9*					g_LODD3DTexture512x = (LPDIRECT3DTEXTURE9*)0x00A0AAC8;
LPDIRECT3DTEXTURE9*					g_LODD3DTexture1024x = (LPDIRECT3DTEXTURE9*)0x00A0AAD0;
LPDIRECT3DTEXTURE9*					g_LODD3DTexture2048x = (LPDIRECT3DTEXTURE9*)0x00A0AACC;

BSRenderedTexture**					g_LODBSTexture32x = (BSRenderedTexture**)0x00A0AADC;
BSRenderedTexture**					g_LODBSTexture64x = (BSRenderedTexture**)0x00A0AAD8;
BSRenderedTexture**					g_LODBSTexture128x = (BSRenderedTexture**)0x00A0AAD4;
BSRenderedTexture**					g_LODBSTexture512x = (BSRenderedTexture**)0x00A0AAE0;
BSRenderedTexture**					g_LODBSTexture1024x = (BSRenderedTexture**)0x00A0AAE8;
BSRenderedTexture**					g_LODBSTexture2048x = (BSRenderedTexture**)0x00A0AAE4;

LPDIRECT3DTEXTURE9					g_LODD3DTexture256x = NULL;
BSRenderedTexture*					g_LODBSTexture256x = NULL;
LPDIRECT3DTEXTURE9					g_LODD3DTexture4096x = NULL;
BSRenderedTexture*					g_LODBSTexture4096x = NULL;
LPDIRECT3DTEXTURE9					g_LODD3DTexture8192x = NULL;
BSRenderedTexture*					g_LODBSTexture8192x = NULL;

const _FormHeap_Allocate			FormHeap_Allocate = (_FormHeap_Allocate)0x00401E80;
const _FormHeap_Free				FormHeap_Free = (_FormHeap_Free)0x00401EA0;
const _Oblivion_DynamicCast			Oblivion_DynamicCast = (_Oblivion_DynamicCast)0x0088DC0C;
const _TESDialog_WriteToStatusBar	TESDialog_WriteToStatusBar = (_TESDialog_WriteToStatusBar)0x00431310;
const _TESDialog_WritePositionToINI	TESDialog_WritePositionToINI = (_TESDialog_WritePositionToINI)0x00417510;
const _TESDialog_GetPositionFromINI	TESDialog_GetPositionFromINI = (_TESDialog_GetPositionFromINI)0x004176D0;
const _TESDialog_GetDialogTemplateForFormType
									TESDialog_GetDialogTemplateForFormType = (_TESDialog_GetDialogTemplateForFormType)0x00442050;
const _TESDialog_GetComboBoxSelectedItemData
									TESDialog_GetComboBoxSelectedItemData = (_TESDialog_GetComboBoxSelectedItemData)0x00403690;
const _TESDialog_SelectTESFileCommonDialog	
									TESDialog_SelectTESFileCommonDialog = (_TESDialog_SelectTESFileCommonDialog)0x00446D40;
const _TESDialog_SetCSWindowTitleModifiedFlag
									TESDialog_SetCSWindowTitleModifiedFlag = (_TESDialog_SetCSWindowTitleModifiedFlag)0x004306F0;
const _TESDialog_ShowSelectReferenceDialog
									TESDialog_ShowSelectReferenceDialog = (_TESDialog_ShowSelectReferenceDialog)0x0044D660;	// pass TESObjectREFR__PickComparator as arg3 and 0 as args 2 and 4
const _TESDialog_InitializeCSWindows
									TESDialog_InitializeCSWindows = (_TESDialog_InitializeCSWindows)0x00430980;
const _TESDialog_DeinitializeCSWindows		
									TESDialog_DeinitializeCSWindows = (_TESDialog_DeinitializeCSWindows)0x00431220;
const _TESDialog_AddFormToObjectWindow
									TESDialog_AddFormToObjectWindow = (_TESDialog_AddFormToObjectWindow)0x00422470;
const _InitializeDefaultPlayerSpell	InitializeDefaultPlayerSpell = (_InitializeDefaultPlayerSpell)0x0056FD90;
const _ConstructEffectSetting		ConstructEffectSetting = (_ConstructEffectSetting)0x0056AC40;
const _TESDialog_AddComboBoxItem	TESDialog_AddComboBoxItem = (_TESDialog_AddComboBoxItem)0x00403540;
const _BSPrintF						BSPrintF = (_BSPrintF)0x004053F0;
const _ShowCompilerError			ShowCompilerError = (_ShowCompilerError)0x004FFF40;
const _AutoSavePlugin				AutoSavePlugin = (_AutoSavePlugin)0x004307C0;
const _CreateArchive				CreateArchive = (_CreateArchive)0x004665C0;
const _TESDialog_GetListViewSelectedItemLParam
									TESDialog_GetListViewSelectedItemLParam = (_TESDialog_GetListViewSelectedItemLParam)0x00403C40;
const _TESForm_LookupByFormID		TESForm_LookupByFormID = (_TESForm_LookupByFormID)0x00495EF0;
const _TESForm_LookupByEditorID		TESForm_LookupByEditorID = (_TESForm_LookupByEditorID)0x00495F20;
const _TESDialog_GetDialogExtraParam
									TESDialog_GetDialogExtraParam = (_TESDialog_GetDialogExtraParam)0x004429D0;
const _TESDialog_ComboBoxPopulateWithRaces
									TESDialog_ComboBoxPopulateWithRaces = (_TESDialog_ComboBoxPopulateWithRaces)0x00445240;
const _TESDialog_ComboBoxPopulateWithForms
									TESDialog_ComboBoxPopulateWithForms = (_TESDialog_ComboBoxPopulateWithForms)0x004456F0;
const _TESDialog_GetSelectedItemData
									TESDialog_GetSelectedItemData = (_TESDialog_GetSelectedItemData)0x00403690;
const _TESDialog_GetDialogExtraLocalCopy
									TESDialog_GetDialogExtraLocalCopy = (_TESDialog_GetDialogExtraLocalCopy)0x004429B0;
const _DataHandler_PlaceTESBoundObjectReference
									DataHandler_PlaceTESBoundObjectReference = (_DataHandler_PlaceTESBoundObjectReference)0x0047C610;

const UInt32						kVTBL_TESObjectREFR = 0x00958824;
const UInt32						kVTBL_TESForm = 0x0094688C;
const UInt32						kVTBL_TESTopicInfo = 0x0094820C;
const UInt32						kVTBL_TESQuest = 0x00945D7C;
const UInt32						kVTBL_TESNPC = 0x0094561C;
const UInt32						kVTBL_TESCreature = 0x00944334;
const UInt32						kVTBL_TESFurniture = 0x00950E94;
const UInt32						kVTBL_TESObjectACTI = 0x009537DC;
const UInt32						kVTBL_TESObjectMISC = 0x00955224;
const UInt32						kVTBL_TESObjectWEAP = 0x00955C8C;
const UInt32						kVTBL_TESObjectCONT = 0x00954B44;
const UInt32						kVTBL_TESObjectCLOT = 0x0095482C;
const UInt32						kVTBL_SpellItem = 0x0095E504;
const UInt32						kVTBL_Script = 0x0094944C;
const UInt32						kVTBL_MessageHandler = 0x00940760;
const UInt32						kVTBL_FileFinder = 0x009389BC;

const UInt32						kCtor_TESNPC = 0x004D8FF0;
const UInt32						kCtor_TESCreature = 0x004CE820;
const UInt32						kCtor_TESFurniture = 0x0050C830;
const UInt32						kCtor_TESObjectACTI = 0x00515530;
const UInt32						kCtor_TESObjectMISC = 0x0051ABA0;
const UInt32						kCtor_TESObjectWEAP = 0x0051DAB0;
const UInt32						kCtor_TESObjectCONT = 0x00518F60;
const UInt32						kCtor_TESObjectREFR = 0x00541870;
const UInt32						kCtor_TESObjectCLOT = 0x00518350;
const UInt32						kCtor_TESQuest = 0x004E0500;
const UInt32						kCtor_Script = 0x004FCA50;
const UInt32						kCtor_TESRenderSelection = 0x00511A20;
const UInt32						kCtor_GameSetting = 0x004FA040;

const UInt32						kTESChildCell_LoadCell = 0x00430F40;
const UInt32						kTESCellUseList_GetUseListRefHead = 0x006E5850;
const UInt32						kTESObjectCELL_GetParentWorldSpace = 0x00532E50;
const UInt32						kScript_SaveResultScript = 0x005034E0;
const UInt32						kScript_SaveScript = 0x00503450;
const UInt32						kLinkedListNode_NewNode = 0x004E3900;
const UInt32						kDataHandler_AddBoundObject = 0x005135F0;
const UInt32						kTESForm_SetFormID = 0x00497E50;
const UInt32						kTESForm_SetEditorID = 0x00497670;
const UInt32						kTESObjectREFR_SetBaseForm = 0x005415A0;
const UInt32						kTESObjectREFR_SetFlagPersistent = 0x0053F0D0;
const UInt32						kExtraDataList_InitItem = 0x0045D740;
const UInt32						kScript_SetText = 0x004FC6C0;
const UInt32						kDataHandler_SortScripts = 0x0047BA30;
const UInt32						kTESScriptableForm_SetScript = 0x004A1830;
const UInt32						kBSStringT_Set = 0x004051E0;
const UInt32						kExtraDataList_CopyListForReference = 0x004603D0;
const UInt32						kExtraDataList_CopyList = 0x00460380;
const UInt32						kGMSTMap_Add = 0x0044F680;
const UInt32						kBSTextureManager_CreateBSRenderedTexture = 0x00773080;
const UInt32						kTESForm_GetOverrideFile = 0x00495FE0;
const UInt32						kTESForm_AddReference = 0x00496430;
const UInt32						kTESForm_GetFormReferenceList = 0x00496380;
const UInt32						kTESForm_CleanupFormReferenceList = 0x00496400;
const UInt32						kTESQuest_SetStartEnabled = 0x004DD7E0;
const UInt32						kTESQuest_SetAllowedRepeatedStages = 0x004DD7C0;
const UInt32						kTESObjectCELL_GetIsInterior = 0x00532240;
const UInt32						kTESBipedModelForm_GetIsPlayable = 0x00490290;
const UInt32						kTESRenderSelection_ClearSelection = 0x00511C20;
const UInt32						kTESRenderSelection_AddFormToSelection = 0x00512730;
const UInt32						kTESRenderSelection_Free = 0x00511A50;
const UInt32						kTESForm_SaveFormRecord = 0x00494950;
const UInt32						kTESFile_GetIsESM = 0x00485B00;
const UInt32						kTESFile_Dtor = 0x00487E60;
const UInt32						kDataHandler_PopulateModList = 0x0047E4C0;
const UInt32						kTESRenderSelection_RemoveFormFromSelection = 0x00512830;
const UInt32						kLinkedListNode_RemoveNode = 0x00452AE0;
const UInt32						kLinkedListNode_GetIsDangling = 0x0048E0E0;
const UInt32						kLinkedListNode_Cleanup = 0x00405DC0;
const UInt32						kLinkedListNode_GetData = 0x004FC950;
const UInt32						kTESForm_SetTemporary = 0x004972A0;
const UInt32						kTESIdleFormTree_AddRootNodes = 0x004D4490;
const UInt32						kTESRenderUndoStack_RecordReference = 0x00432D40;
const UInt32						kTESObjectREFR_PickComparator = 0x00545B10;
const UInt32						kLinkedListNode_CountNodes = 0x0047DC40;
const UInt32						kDataHandler_CreateForm = 0x004793F0;	// pass typeID as arg0
const UInt32						kNiTPointerMap_LookupByKey = 0x004ADB90;
const UInt32						kNiTPointerMap_Remove = 0x004BCBD0;

const UInt32						kBaseExtraList_GetExtraDataByType = 0x0045B1B0;
const UInt32						kBaseExtraList_ModExtraEnableStateParent = 0x0045CAA0;
const UInt32						kBaseExtraList_ModExtraOwnership = 0x0045E060;
const UInt32						kBaseExtraList_ModExtraGlobal = 0x0045E120;
const UInt32						kBaseExtraList_ModExtraRank = 0x0045E1E0;
const UInt32						kBaseExtraList_ModExtraCount = 0x0045E2A0;

const UInt32						kTESObjectREFR_ModExtraHealth = 0x0053F4E0;
const UInt32						kTESObjectREFR_ModExtraCharge = 0x0053F3C0;
const UInt32						kTESObjectREFR_ModExtraTimeLeft = 0x0053F620;
const UInt32						kTESObjectREFR_ModExtraSoul = 0x0053F710;
const UInt32						kTESObjectREFR_SetExtraEnableStateParent_OppositeState = 0x0053FA80;
const UInt32						kTESObjectREFR_GetExtraRef3DData = 0x00542950;
const UInt32						kTESObjectREFR_RemoveExtraTeleport = 0x0053F7A0;

void CSEINIManager::Initialize()
{
	DebugPrint("INI Path: %s", INIFile.c_str());
	std::fstream INIStream(INIFile.c_str(), std::fstream::in);
	bool CreateINI = false;

	if (INIStream.fail())
	{
		DebugPrint("INI File not found; Creating one...");
		CreateINI = true;
	}

	INIStream.close();
	INIStream.clear();		// only initializing non script editor keys as those are taken care of by its code

	RegisterSetting(new SME::INI::INISetting(this, "Top", "Extender::Console", "150", "Client Rect Top"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "Left", "Extender::Console", "150", "Client Rect Left"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "Right", "Extender::Console", "500", "Client Rect Right"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "Bottom", "Extender::Console", "350", "Client Rect Bottom"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "LogCSWarnings", "Extender::Console", "1", "Log CS Warnings to the Console"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "LogAssertions", "Extender::Console", "1", "Log CS Assertions to the Console"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "HideOnStartup", "Extender::Console", "0", "Hide the console on CS startup"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "ConsoleUpdatePeriod", "Extender::Console", "2000", "Duration, in milliseconds, between console window updates"), (CreateINI == false));

	RegisterSetting(new SME::INI::INISetting(this, "LoadPluginOnStartup", "Extender::General", "0", "Load a plugin on CS startup"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "StartupPluginName", "Extender::General", "", "Name of the plugin, with extension, that is to be loaded on startup"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "OpenScriptWindowOnStartup", "Extender::General", "0", "Open an empty script editor window on startup"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "StartupScriptEditorID", "Extender::General", "", "EditorID of the script to be loaded on startup, should a script editor also be opened. An empty string results in a blank workspace"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "ShowNumericEditorIDWarning", "Extender::General", "1", "Display a warning when editorIDs start with an integer"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "SetWorkspaceOnStartup", "Extender::General", "0", "Set the working directory to a custom path on startup"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "DefaultWorkspacePath", "Extender::General", "", "Path of the custom workspace directory"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "SaveLoadedESPsAsMasters", "Extender::General", "1", "Save loaded plugin files as the active plugin's master"), (CreateINI == false));

	RegisterSetting(new SME::INI::INISetting(this, "UpdatePeriod", "Extender::Renderer", "8", "Duration, in milliseconds, between render window updates"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "DisplaySelectionStats", "Extender::Renderer", "1", "Display info on the render window selection"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "UpdateViewPortAsync", "Extender::Renderer", "0", "Allow the render window to be updated in the background"), (CreateINI == false));

	RegisterSetting(new SME::INI::INISetting(this, "AltRefMovementSpeed", "Extender::Renderer", "0.8", "Alternate render window movement settings"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "AltRefSnapGrid", "Extender::Renderer", "2", "Alternate render window movement settings"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "AltRefRotationSpeed", "Extender::Renderer", "1.0", "Alternate render window movement settings"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "AltRefSnapAngle", "Extender::Renderer", "45", "Alternate render window movement settings"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "AltCamRotationSpeed", "Extender::Renderer", "1.0", "Alternate render window movement settings"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "AltCamZoomSpeed", "Extender::Renderer", "0.5", "Alternate render window movement settings"), (CreateINI == false));
	RegisterSetting(new SME::INI::INISetting(this, "AltCamPanSpeed", "Extender::Renderer", "5.0", "Alternate render window movement settings"), (CreateINI == false));

	RegisterSetting(new SME::INI::INISetting(this, "BackupOnSave", "Extender::VersionControl", "0", "Create a backup copy of the active plugin to the 'Backup' directory in the active workspace before commencing a save operation"), (CreateINI == false));

	RegisterSetting(new SME::INI::INISetting(this, "GlobalScriptExecutionPeriod", "Extender::CSAS", "10", "Duration, in milliseconds, between global script execution operations"), (CreateINI == false));

	if (CreateINI)		SaveSettingsToINI();
	else				ReadSettingsFromINI();
}

const char* PrintToBuffer(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsprintf_s(g_TextBuffer, sizeof(g_TextBuffer), fmt, args);
	va_end(args);

	return g_TextBuffer;
}

void WaitUntilDebuggerAttached()
{
	CONSOLE->Indent();
	DebugPrint("Waiting For Debugger...");
	while (!IsDebuggerPresent())
		Sleep(5000);
	DebugPrint("Debugger Attached!");
	CONSOLE->Exdent();
}