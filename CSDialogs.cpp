#include "CSDialogs.h"
#include "WorkspaceManager.h"
#include "Hooks\ScriptEditor.h"
#include "Hooks\TESFile.h"

using namespace Hooks;

TESDialogWindowHandleCollection		g_CustomMainWindowChildrenDialogs;
TESDialogWindowHandleCollection		g_DragDropSupportDialogs;

const char*							g_FormTypeIdentifier[] =			// uses TESForm::typeID as its index
									{
											"None",
											"TES4",
											"Group",
											"GMST",
											"Global",
											"Class",
											"Faction",
											"Hair",
											"Eyes",
											"Race",
											"Sound",
											"Skill",
											"Effect",
											"Script",
											"LandTexture",
											"Enchantment",
											"Spell",
											"BirthSign",
											"Activator",
											"Apparatus",
											"Armor",
											"Book",
											"Clothing",
											"Container",
											"Door",
											"Ingredient",
											"Light",
											"MiscItem",
											"Static",
											"Grass",
											"Tree",
											"Flora",
											"Furniture",
											"Weapon",
											"Ammo",
											"NPC",
											"Creature",
											"LeveledCreature",
											"SoulGem",
											"Key",
											"AlchemyItem",
											"SubSpace",
											"SigilStone",
											"LeveledItem",
											"SNDG",
											"Weather",
											"Climate",
											"Region",
											"Cell",
											"Reference",
											"Reference",			// ACHR
											"Reference",			// ACRE
											"PathGrid",
											"World Space",
											"Land",
											"TLOD",
											"Road",
											"Dialog",
											"Dialog Info",
											"Quest",
											"Idle",
											"AI Package",
											"CombatStyle",
											"LoadScreen",
											"LeveledSpell",
											"AnimObject",
											"WaterType",
											"EffectShader",
											"TOFT"
										};

UInt32 GetFormDialogTemplate(const char* FormType)
{
	if (!_stricmp(FormType, "Activator") ||
		!_stricmp(FormType, "Apparatus") ||
		!_stricmp(FormType, "Armor") ||
		!_stricmp(FormType, "Book") ||
		!_stricmp(FormType, "Clothing") ||
		!_stricmp(FormType, "Container") ||
		!_stricmp(FormType, "Door") ||
		!_stricmp(FormType, "Ingredient") ||
		!_stricmp(FormType, "Light") ||
		!_stricmp(FormType, "MiscItem") ||
		!_stricmp(FormType, "SoulGem") ||
		!_stricmp(FormType, "Static") ||
		!_stricmp(FormType, "Grass") ||
		!_stricmp(FormType, "Tree") ||
		!_stricmp(FormType, "Flora") ||
		!_stricmp(FormType, "Furniture") ||
		!_stricmp(FormType, "Ammo") ||
		!_stricmp(FormType, "Weapon") ||
		!_stricmp(FormType, "NPC") ||
		!_stricmp(FormType, "Creature") ||
		!_stricmp(FormType, "LeveledCreature") ||
		!_stricmp(FormType, "Spell") ||
		!_stricmp(FormType, "Enchantment") ||
		!_stricmp(FormType, "Potion") ||
		!_stricmp(FormType, "Leveled Item") ||
		!_stricmp(FormType, "Sound") ||
		!_stricmp(FormType, "LandTexture") ||
		!_stricmp(FormType, "CombatStyle") ||
		!_stricmp(FormType, "LoadScreen") ||
		!_stricmp(FormType, "WaterType") ||
		!_stricmp(FormType, "LeveledSpell") ||
		!_stricmp(FormType, "AnimObject") ||
		!_stricmp(FormType, "Subspace") ||
		!_stricmp(FormType, "EffectShader") ||
		!_stricmp(FormType, "SigilStone"))
			return 1;									// FormEdit Dialogs
	else if (!_stricmp(FormType, "Script"))
			return 9;
	else if (!_stricmp(FormType, "Reference"))
			return 10;									// Special Handlers
	else if (!_stricmp(FormType, "Hair") ||
		!_stricmp(FormType, "Eyes") ||
		!_stricmp(FormType, "Race") ||
		!_stricmp(FormType, "Class") ||
		!_stricmp(FormType, "Birthsign") ||
		!_stricmp(FormType, "Climate") ||
		!_stricmp(FormType, "World Space"))
			return 2;									// FormIDListView Dialogs
	else
			return 0;
}

UInt32 GetFormDialogTemplate(UInt8 FormTypeID)
{
	const char* FormType = g_FormTypeIdentifier[FormTypeID];

	return GetFormDialogTemplate(FormType);
}

void InstantitateCustomScriptEditor(const char* ScriptEditorID)
{
	Script* AuxScript = CS_CAST(TESForm::LookupByEditorID(ScriptEditorID), TESForm, Script);
	tagRECT ScriptEditorLoc;
	ComponentDLLInterface::ScriptData* Data = new ComponentDLLInterface::ScriptData(AuxScript);

	TESDialog::GetPositionFromINI("Script Edit", &ScriptEditorLoc);
	CLIWrapper::Interfaces::SE->InstantiateEditor(Data, ScriptEditorLoc.left, ScriptEditorLoc.top, ScriptEditorLoc.right, ScriptEditorLoc.bottom);
}

void InstantitateCustomScriptEditor(UInt32 ScriptFormID)
{
	TESForm* Script = TESForm::LookupByFormID(ScriptFormID);
	if (Script && Script->editorID.c_str())
		InstantitateCustomScriptEditor(Script->editorID.c_str());
}

HWND ShowFormEditDialog(const char* EditorID, const char* FormType)
{
	UInt32 Type = GetFormDialogTemplate(FormType);
	FormEditParam InitData(EditorID);

	switch (Type)
	{
	case 9:
		if (TESForm::LookupByEditorID(EditorID))
			InstantitateCustomScriptEditor(EditorID);
		break;
	case 10:
		LoadReferenceParentCell(EditorID);
		break;
	case 1:
	case 2:
		return CreateDialogParamA(*g_TESCS_Instance,
							(LPCSTR)TESDialog::GetDialogTemplateForFormType(InitData.typeID),
							*g_HWND_CSParent,
							((Type == 1) ? g_TESDialogFormEdit_DlgProc : g_TESDialogFormIDListView_DlgProc),
							(LPARAM)&InitData);
		break;
	}

	return NULL;
}

HWND ShowFormEditDialog(const char* EditorID, UInt8 FormType)
{
	return ShowFormEditDialog(EditorID, g_FormTypeIdentifier[FormType]);
}

HWND ShowFormEditDialog(UInt32 FormID, const char* FormType)
{
	TESForm* Form = TESForm::LookupByFormID(FormID);
	if (Form && Form->editorID.c_str())
		return ShowFormEditDialog(Form->editorID.c_str(), FormType);

	return NULL;
}

HWND ShowFormEditDialog(UInt32 FormID, UInt8 FormType)
{
	return ShowFormEditDialog(FormID, g_FormTypeIdentifier[FormType]);
}

void LoadReferenceParentCell(UInt32 FormID)
{
	TESObjectREFR* Reference = CS_CAST(TESForm::LookupByFormID(FormID), TESForm, TESObjectREFR);
	_TES->LoadCellIntoViewPort(Reference->GetPosition(), Reference);
}

void LoadReferenceParentCell(const char* EditorID)
{
	TESObjectREFR* Reference = CS_CAST(TESForm::LookupByEditorID(EditorID), TESForm, TESObjectREFR);
	_TES->LoadCellIntoViewPort(Reference->GetPosition(), Reference);
}

TESObjectREFR* ShowReferencePickDialog(HWND Parent)
{
	return TESDialog::ShowSelectReferenceDialog(Parent, NULL);
}

void CSStartupManager::LoadStartupPlugin()
{
	if (g_INIManager->GetINIInt("LoadPluginOnStartup"))
	{
		kAutoLoadActivePluginOnStartup.WriteJump();

		const char* PluginName = g_INIManager->GetINIStr("StartupPluginName");
		TESFile* File = _DATAHANDLER->LookupPluginByName(PluginName);

		if (File)
		{
			DebugPrint("Loading plugin '%s' on startup...", PluginName);
			CONSOLE->Indent();

			if (_stricmp(PluginName, "Oblivion.esm"))
				ToggleFlag(&File->fileFlags, TESFile::kFileFlag_Active, true);

			ToggleFlag(&File->fileFlags, TESFile::kFileFlag_Loaded, true);
			SendMessage(*g_HWND_CSParent, WM_COMMAND, 0x9CD1, 0);

			CONSOLE->Exdent();
		}
		else if (strlen(PluginName) >= 1)
		{
			DebugPrint("Couldn't load plugin '%s' on startup - It doesn't exist!", PluginName);
		}

		kAutoLoadActivePluginOnStartup.WriteBuffer();
	}
}

void CSStartupManager::LoadStartupScript()
{
	if (g_INIManager->GetINIInt("OpenScriptWindowOnStartup"))
	{
		const char* ScriptID = g_INIManager->GetINIStr("StartupScriptEditorID");
		if (strcmp(ScriptID, "") && TESForm::LookupByEditorID(ScriptID))
			InstantitateCustomScriptEditor(ScriptID);
		else
			SendMessage(*g_HWND_CSParent, WM_COMMAND, 0x9CE1, 0);
	}
}

void CSStartupManager::LoadStartupWorkspace()
{
	if (g_INIManager->GetINIInt("SetWorkspaceOnStartup"))
		g_WorkspaceManager.SelectWorkspace(g_INIManager->GetINIStr("DefaultWorkspacePath"));
}

void ResetRenderWindow()
{
	UInt8 ObjWndState = *g_Flag_ObjectWindow_MenuState, CellWndState = *g_Flag_CellView_MenuState;

	*g_Flag_ObjectWindow_MenuState = 0;
	*g_Flag_CellView_MenuState = 0;

	SendMessage(*g_HWND_RenderWindow, 0x419, 6, 1);
	SendMessage(*g_HWND_RenderWindow, 0x419, 5, 0);
	InvalidateRect(*g_HWND_RenderWindow, 0, 1);

	TESDialog::DeinitializeCSWindows();
	TESDialog::InitializeCSWindows();

	*g_Flag_ObjectWindow_MenuState = ObjWndState;
	*g_Flag_CellView_MenuState = CellWndState;
}

void __stdcall FormEnumerationWrapper::ReinitializeFormLists()
{
	TESDialog::DeinitializeCSWindows();

	SendMessage(*g_HWND_CellView, 0x40E, 1, 1);			// for worldspaces
	SendMessage(*g_HWND_AIPackagesDlg, 0x41A, 0, 0);	// for AI packages

	TESDialog::InitializeCSWindows();
	InvalidateRect(*g_HWND_ObjectWindow_FormList, NULL, TRUE);
	SendMessage(*g_HWND_ObjectWindow_FormList, 0x41A, 0, 0);
}

bool FormEnumerationWrapper::GetUnmodifiedFormHiddenState()	// returns true when hidden
{
	HMENU MainMenu = GetMenu(*g_HWND_CSParent), ViewMenu = GetSubMenu(MainMenu, 2);
	UInt32 State = GetMenuState(ViewMenu, MAIN_VIEW_MODIFIEDRECORDS, MF_BYCOMMAND);

	return (State & MF_CHECKED);
}

bool FormEnumerationWrapper::GetDeletedFormHiddenState()
{
	HMENU MainMenu = GetMenu(*g_HWND_CSParent), ViewMenu = GetSubMenu(MainMenu, 2);
	UInt32 State = GetMenuState(ViewMenu, MAIN_VIEW_DELETEDRECORDS, MF_BYCOMMAND);

	return (State & MF_CHECKED);
}

bool __stdcall FormEnumerationWrapper::GetShouldEnumerateForm(TESForm* Form)
{
	if (GetUnmodifiedFormHiddenState() && (Form->formFlags & TESForm::kFormFlags_FromActiveFile) == 0)
		return false;		// skip addition
	else if (GetDeletedFormHiddenState() && (Form->formFlags & TESForm::kFormFlags_Deleted))
		return false;
	else
		return true;
}

bool __stdcall FormEnumerationWrapper::PerformListViewPrologCheck(UInt32 CallAddress)
{
	switch (CallAddress)
	{
	case 0x00445C88:
	case 0x00445DC8:
	case 0x00445E6E:
	case 0x00452FA8:
	case 0x00440FBD:
	case 0x0040A4BF:
	case 0x00412F7A:
	case 0x0043FDFF:
	case 0x00442576:
	case 0x00452409:
	case 0x00560DC2:
	case 0x00445E12:
	case 0x00445D81:
	case 0x004F00C3:
		return 1;
	default:
		return 0;
	}
}

void FormEnumerationWrapper::ToggleUnmodifiedFormVisibility()
{
	HMENU MainMenu = GetMenu(*g_HWND_CSParent), ViewMenu = GetSubMenu(MainMenu, 2);
	if (GetUnmodifiedFormHiddenState())
		CheckMenuItem(ViewMenu, MAIN_VIEW_MODIFIEDRECORDS, MF_UNCHECKED);
	else
		CheckMenuItem(ViewMenu, MAIN_VIEW_MODIFIEDRECORDS, MF_CHECKED);

	ReinitializeFormLists();
}
void FormEnumerationWrapper::ToggleDeletedFormVisibility()
{
	HMENU MainMenu = GetMenu(*g_HWND_CSParent), ViewMenu = GetSubMenu(MainMenu, 2);
	if (GetDeletedFormHiddenState())
		CheckMenuItem(ViewMenu, MAIN_VIEW_DELETEDRECORDS, MF_UNCHECKED);
	else
		CheckMenuItem(ViewMenu, MAIN_VIEW_DELETEDRECORDS, MF_CHECKED);

	ReinitializeFormLists();
}

void __stdcall FormEnumerationWrapper::ResetFormVisibility(void)
{
	if (GetUnmodifiedFormHiddenState())
		ToggleUnmodifiedFormVisibility();
	if (GetDeletedFormHiddenState())
		ToggleDeletedFormVisibility();
}

TESDialogWindowHandleCollection::HandleCollectionT::iterator TESDialogWindowHandleCollection::FindHandle(HWND Handle)
{
	for (HandleCollectionT::iterator Itr = WindowHandles.begin(); Itr != WindowHandles.end(); Itr++)
	{
		if (*Itr == Handle)
			return Itr;
	}

	return WindowHandles.end();
}

bool TESDialogWindowHandleCollection::RemoveHandle(HWND Handle)
{
	HandleCollectionT::iterator Match = FindHandle(Handle);
	if (Match != WindowHandles.end())
	{
		WindowHandles.erase(Match);
		return true;
	}
	else
		return false;
}