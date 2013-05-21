#include "TESForm.h"
#include "TESDialog.h"
#include "[Common]\CLIWrapper.h"

HINSTANCE*					TESCSMain::Instance = (HINSTANCE*)0x00A0AF1C;
HWND*						TESCSMain::WindowHandle = (HWND*)0x00A0AF20;
HWND*						TESCSMain::MainToolbarHandle = (HWND*)0x00A0AFD0;
HMENU*						TESCSMain::MainMenuHandle = (HMENU*)0x00A0B630;
char**						TESCSMain::ActivePluginNameBuffer = (char**)0x00A0AF00;
UInt8*						TESCSMain::AllowAutoSaveFlag = (UInt8*)0x00A0B628;
UInt8*						TESCSMain::ExittingCSFlag = (UInt8*)0x00A0B63C;
const char*					TESCSMain::INIFilePath = (const char*)0x00A0ABB8;

HWND*						TESObjectWindow::WindowHandle = (HWND*)0x00A0AF44;
HWND*						TESObjectWindow::FormListHandle = (HWND*)0x00A0BAA0;
HWND*						TESObjectWindow::TreeViewHandle = (HWND*)0x00A0BAA4;
UInt8*						TESObjectWindow::MainMenuState = (UInt8*)0x00A0AF40;

HWND*						TESCellViewWindow::WindowHandle = (HWND*)0x00A0AF4C;
HWND*						TESCellViewWindow::ObjectListHandle = (HWND*)0x00A0AA00;
HWND*						TESCellViewWindow::CellListHandle = (HWND*)0x00A0AA34;
UInt8*						TESCellViewWindow::MainMenuState = (UInt8*)0x00A0AF48;
TESObjectCELL**				TESCellViewWindow::CurrentCellSelection = (TESObjectCELL**)0x00A0A9DC;
int*						TESCellViewWindow::ObjectListSortColumn = (int*)0x00A0A9D4;

ResponseEditorData**		ResponseEditorData::EditorCache = (ResponseEditorData**)0x00A10E2C;

HWND*						TESPreviewWindow::WindowHandle = (HWND*)0x00A0A71C;
TESPreviewControl**			TESPreviewWindow::PreviewControl = (TESPreviewControl**)0x00A0A730;

TESObjectSelection**		TESObjectSelection::PrimaryInstance = (TESRenderSelection**)0x00A0AF60;

FormEditParam::FormEditParam(const char* EditorID)
{
	form = TESForm::LookupByEditorID(EditorID);
	typeID = form->formType;
}

FormEditParam::FormEditParam(UInt32 FormID)
{
	form = TESForm::LookupByFormID(FormID);
	typeID = form->formType;
}

FormEditParam::FormEditParam( TESForm* Form )
{
	form = Form;
	typeID = Form->formType;
}

UInt32 TESDialog::WritePositionToINI( HWND Handle, const char* WindowClassName )
{
	return cdeclCall<UInt32>(0x00417510, Handle, WindowClassName);
}

bool TESDialog::GetPositionFromINI( const char* WindowClassName, LPRECT OutRect )
{
	return cdeclCall<bool>(0x004176D0, WindowClassName, OutRect);
}

LRESULT TESCSMain::WriteToStatusBar( int PanelIndex, const char* Message )
{
	return cdeclCall<UInt32>(0x00431310, PanelIndex, Message);
}

void TESCSMain::InitializeCSWindows()
{
	cdeclCall<UInt32>(0x00430980);
}

void TESCSMain::DeinitializeCSWindows()
{
	cdeclCall<UInt32>(0x00431220);
}

void TESCSMain::SetTitleModified( bool State )
{
	cdeclCall<UInt32>(0x004306F0, State);
}

void TESCSMain::AutoSave()
{
	cdeclCall<UInt32>(0x004307C0);
}

UInt32 TESDialog::GetDialogTemplateForFormType( UInt8 FormTypeID )
{
	return cdeclCall<UInt32>(0x00442050, FormTypeID);
}

TESObjectREFR* TESDialog::ShowSelectReferenceDialog( HWND Parent, TESObjectREFR* DefaultSelection )
{
	return cdeclCall<TESObjectREFR*>(0x0044D660, Parent, DefaultSelection, 0x00545B10, 0);
}

BSExtraData* TESDialog::GetDialogExtraByType( HWND Dialog, UInt16 Type )
{
	return cdeclCall<BSExtraData*>(0x00442990, Dialog, Type);
}

TESForm* TESDialog::GetDialogExtraParam( HWND Dialog )
{
	return cdeclCall<TESForm*>(0x004429D0, Dialog);
}

TESForm* TESDialog::GetDialogExtraLocalCopy( HWND Dialog )
{
	return cdeclCall<TESForm*>(0x004429B0, Dialog);
}

bool TESDialog::GetIsWindowDragDropRecipient( UInt16 FormType, HWND hWnd )
{
	return cdeclCall<bool>(0x004433C0, FormType, hWnd);
}

bool TESDialog::SelectTESFileCommonDialog( HWND Parent, const char* SaveDir, bool SaveAsESM, char* FileNameOut, size_t OutSize )
{
	return cdeclCall<bool>(0x00446D40, Parent, SaveDir, SaveAsESM, FileNameOut, OutSize);
}

HWND TESDialog::ShowFormEditDialog( TESForm* Form )
{
	if (GetIsFormEditDialogCompatible(Form) == false)
		return NULL;

	FormEditParam InitData(Form);
	return BGSEEUI->ModelessDialog(*TESCSMain::Instance,
							(LPSTR)GetDialogTemplateForFormType(InitData.typeID),
							*TESCSMain::WindowHandle,
							(DLGPROC)0x00447580,
							(LPARAM)&InitData,
							true);
}

void TESDialog::ShowScriptEditorDialog( TESForm* InitScript )
{
	Script* AuxScript = CS_CAST(InitScript, TESForm, Script);
	RECT ScriptEditorLoc;
	ComponentDLLInterface::ScriptData* Data = NULL;

	if (AuxScript)
		Data = new ComponentDLLInterface::ScriptData(AuxScript);

	TESDialog::GetPositionFromINI("Script Edit", &ScriptEditorLoc);
	ConstructionSetExtender::CLIWrapper::Interfaces::SE->InstantiateEditor(Data, ScriptEditorLoc.left, ScriptEditorLoc.top, ScriptEditorLoc.right, ScriptEditorLoc.bottom);
}


bool TESDialog::GetIsFormEditDialogCompatible( TESForm* Form )
{
	switch (Form->formType)
	{
	case TESForm::kFormType_Activator:
	case TESForm::kFormType_Apparatus:
	case TESForm::kFormType_Armor:
	case TESForm::kFormType_Book:
	case TESForm::kFormType_Clothing:
	case TESForm::kFormType_Container:
	case TESForm::kFormType_Door:
	case TESForm::kFormType_Ingredient:
	case TESForm::kFormType_Light:
	case TESForm::kFormType_Misc:
	case TESForm::kFormType_Key:
	case TESForm::kFormType_SoulGem:
	case TESForm::kFormType_Static:
	case TESForm::kFormType_Grass:
	case TESForm::kFormType_Tree:
	case TESForm::kFormType_Flora:
	case TESForm::kFormType_Furniture:
	case TESForm::kFormType_Ammo:
	case TESForm::kFormType_Weapon:
	case TESForm::kFormType_NPC:
	case TESForm::kFormType_Creature:
	case TESForm::kFormType_LeveledCreature:
	case TESForm::kFormType_Spell:
	case TESForm::kFormType_Enchantment:
	case TESForm::kFormType_AlchemyItem:
	case TESForm::kFormType_LeveledItem:
	case TESForm::kFormType_LeveledSpell:
	case TESForm::kFormType_Sound:
	case TESForm::kFormType_LandTexture:
	case TESForm::kFormType_CombatStyle:
	case TESForm::kFormType_LoadScreen:
	case TESForm::kFormType_WaterForm:
	case TESForm::kFormType_AnimObject:
	case TESForm::kFormType_SubSpace:
	case TESForm::kFormType_EffectShader:
	case TESForm::kFormType_SigilStone:
		return true;
	default:
		return false;
	}
}

HWND TESDialog::ShowUseReportDialog( TESForm* Form )
{
	return BGSEEUI->ModelessDialog(*TESCSMain::Instance, (LPSTR)TESDialog::kDialogTemplate_UseReport, NULL, (DLGPROC)0x00433FE0, (LPARAM)Form, true);
}

void TESDialog::ResetFormListControls()
{
	TESCSMain::DeinitializeCSWindows();

	SendMessage(*TESCellViewWindow::WindowHandle, 0x40E, 1, 1);			// for worldspaces
	SendMessage(*TESPackage::WindowHandle, 0x41A, 0, 0);				// for AI packages

	TESCSMain::InitializeCSWindows();
}

float TESDialog::GetDlgItemFloat( HWND Dialog, int ID )
{
	return cdeclCall<float>(0x00404A80, Dialog, ID);
}

void TESDialog::ShowDialogPopupMenu( HMENU Menu, POINT* Coords, HWND Parent, LPARAM Data )
{
	cdeclCall<void>(0x00443520, Menu, Coords, Parent, Data);
}

void TESDialog::SetDlgItemFloat( HWND Dialog, int ID, float Value, int DecimalPlaces )
{
	cdeclCall<void>(0x00404A90, Dialog, ID, Value, DecimalPlaces);
}

void TESDialog::ClampDlgEditField( HWND EditControl, float Min, float Max, bool NoDecimals /*= false*/, UInt32 DecimalPlaces /*= 2*/ )
{
	cdeclCall<void>(0x004042C0, EditControl, Min, Max, NoDecimals, DecimalPlaces);
}

ExtraDataList* TESDialog::GetDialogExtraDataList( HWND Dialog )
{
	return cdeclCall<ExtraDataList*>(0x00442980, Dialog);
}

bool TESDialog::CallFormDialogMessageCallback( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG* outLong )
{
	return cdeclCall<bool>(0x00442BD0, hWnd, uMsg, wParam, lParam, outLong);
}

void TESComboBox::AddItem( HWND hWnd, const char* Text, void* Data, bool ResizeDroppedWidth )
{
	cdeclCall<UInt32>(0x00403540, hWnd, Text, Data, ResizeDroppedWidth);
}

void* TESComboBox::GetSelectedItemData( HWND hWnd )
{
	return cdeclCall<void*>(0x00403690, hWnd);
}

void TESComboBox::PopulateWithForms( HWND hWnd, UInt8 FormType, bool ClearItems, bool AddDefaultItem )
{
	cdeclCall<UInt32>(0x004456F0, hWnd, FormType, ClearItems, AddDefaultItem);
}

void* TESListView::GetSelectedItemData( HWND hWnd )
{
	return cdeclCall<void*>(0x00403C40, hWnd);
}

void* TESListView::GetItemData( HWND hWnd, int Index )
{
	return cdeclCall<void*>(0x00403A30, hWnd, Index);
}

void TESListView::SetSelectedItem( HWND hWnd, int Index )
{
	cdeclCall<void>(0x00403B10, hWnd, Index);
}

int TESListView::GetItemByData( HWND hWnd, void* Data )
{
	return cdeclCall<int>(0x004039E0, hWnd, Data);
}

void TESPreviewWindow::Show( TESBoundObject* Object )
{
	if (*WindowHandle == NULL)
		SendMessage(*TESCSMain::WindowHandle, WM_COMMAND, 40121, NULL);

	if (Object)
		cdeclCall<void>(0x00402BC0, Object);
}

void TESPreviewWindow::HandleResize( HWND PreviewWindow )
{
	cdeclCall<void>(0x004025A0, PreviewWindow);
}

void TESPreviewWindow::Initialize( HWND PreviewWindow )
{
	cdeclCall<void>(0x00402910, PreviewWindow);
}

void TESPreviewWindow::Deinitialize( HWND PreviewWindow )
{
	cdeclCall<void>(0x00402B00, PreviewWindow);
}

bool Subwindow::Build( UInt32 TemplateID )
{
	return cdeclCall<bool>(0x00404EC0, TemplateID, this);
}

void Subwindow::TearDown( void )
{
	thisCall<void>(0x00405340, this);
}

Subwindow* Subwindow::CreateInstance( void )
{
	Subwindow* NewInstance = (Subwindow*)FormHeap_Allocate(sizeof(Subwindow));
	ZeroMemory(NewInstance, sizeof(Subwindow));
	return NewInstance;
}

void Subwindow::DeleteInstance( void )
{
	FormHeap_Free(this);
}

void TESObjectSelection::AddToSelection( TESForm* Form, bool AddSelectionBox )
{
	thisCall<UInt32>(0x00512730, this, Form, AddSelectionBox);
}

void TESObjectSelection::RemoveFromSelection( TESForm* Form, bool RemoveSelectionBox )
{
	thisCall<UInt32>(0x00512830, this, Form, RemoveSelectionBox);
}

void TESObjectSelection::ClearSelection( bool RemoveSelectionBox )
{
	thisCall<UInt32>(0x00511C20, this, RemoveSelectionBox);
}

TESObjectSelection* TESObjectSelection::CreateInstance( TESObjectSelection* Source )
{
	TESObjectSelection* NewInstance = (TESObjectSelection*)FormHeap_Allocate(sizeof(TESObjectSelection));
	thisCall<UInt32>(0x00511A20, NewInstance);

	if (Source && Source->selectionCount)
	{
		for (SelectedObjectsEntry* Itr = Source->selectionList; Itr && Itr->Data; Itr = Itr->Next)
			NewInstance->AddToSelection(Itr->Data);
	}

	return NewInstance;
}

void TESObjectSelection::DeleteInstance()
{
	this->ClearSelection(false);
	FormHeap_Free(this);
}

void TESObjectSelection::CalculatePositionVectorSum( void )
{
	thisCall<void>(0x00511A70, this);
}

bool TESObjectSelection::HasObject( TESForm* Form )
{
	return thisCall<bool>(0x00511CC0, this, Form);
}

void TESFileFormListWindow::Show( HWND Parent, TESFile* File)
{
	if (Parent == NULL)
		Parent = *TESCSMain::WindowHandle;

	BGSEEUI->ModalDialog(*TESCSMain::Instance, MAKEINTRESOURCE(0xB4), Parent, (DLGPROC)0x00410280, (LPARAM)File, true);
}


void TESCellViewWindow::SetCellSelection( TESObjectCELL* Cell )
{
	cdeclCall<void>(0x00409070, Cell);
}


void TESObjectWindow::RefreshFormList( void )
{
	SendMessage(*TESObjectWindow::WindowHandle, 0x41A, NULL, NULL);
}
