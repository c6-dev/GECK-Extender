#pragma once

#include "Macros.h"
#include "IScriptEditorController.h"

namespace cse
{


namespace scriptEditor
{


namespace controllerImpl
{


namespace components
{


using namespace controller;

ref class ViewTabTearingHelper
{
	static ViewTabTearingHelper^ Singleton = nullptr;

	model::IScriptDocument^ TornDocument;
	IScriptEditorController^ SourceController;
	bool Active;
	bool ProcessingMouseMessage;
	MouseEventHandler^ TearingEventDelegate;
	Dictionary<view::components::ITabStrip^, IScriptEditorController^>^ ActiveTabStrips;

	void TearingEventHandler(Object^ Sender, MouseEventArgs^ E);
	void End();

	ViewTabTearingHelper();
public:
	~ViewTabTearingHelper();

	void InitiateHandling(model::IScriptDocument^ Tearing, IScriptEditorController^ ParentController);
	void RegisterTabStrip(view::components::ITabStrip^ TabStrip, IScriptEditorController^ ParentController);
	void DeregisterTabStrip(view::components::ITabStrip^ TabStrip);

	property bool InProgress
	{
		bool get() { return Active; }
	}

	static ViewTabTearingHelper^ Get();
};


ref class DocumentNavigationHelper
{
	static UInt32 MaxCrumbItemTextLength = 40;
	static Dictionary<obScriptParsing::Structurizer::Node::eNodeType, Image^>^ NodeIcons = gcnew Dictionary<obScriptParsing::Structurizer::Node::eNodeType, Image^>;

	static Image^ GetNodeIcon(obScriptParsing::Structurizer::Node::eNodeType NodeType);
	static Object^ OutlineListViewAspectGetter(Object^ RowObject);
	static Object^ OutlineListViewImageGetter(Object^ RowObject);
	static bool OutlineListViewCanExpandGetter(Object^ E);
	static Collections::IEnumerable^ OutlineListViewChildrenGetter(Object^ E);

	ref struct CrumbItemData
	{
		property model::IScriptDocument^ ParentScriptDocument;
		property obScriptParsing::Structurizer::Node^ Scope;

		CrumbItemData(model::IScriptDocument^ ParentScriptDocument, obScriptParsing::Structurizer::Node^ Scope);
	};

	view::components::ICrumbBar^ CrumbBar;
	view::components::ICrumbBarItem^ Root;
	obScriptParsing::Structurizer^ CachedStructureData;
	Dictionary<obScriptParsing::Structurizer::Node^, view::components::ICrumbBarItem^>^ ActiveCrumbs;
	view::components::IObjectListView^ OutlineListView;
	EventHandler^ PreferencesChangedEventHandler;

	void Preferences_Changed(Object^ Sender, EventArgs^ E);

	void GenerateAllCrumbs(obScriptParsing::Structurizer^ Data, model::IScriptDocument^ SourceDocument);
	void EnumerateChildCrumbs(view::components::ICrumbBarItem^ Item, model::IScriptDocument^ SourceDocument);
	void CreateNewCrumb(obScriptParsing::Structurizer::Node^ Source, view::components::ICrumbBarItem^ Parent, model::IScriptDocument^ SourceDocument, bool EnumerateChildren);
	void ResetCrumbs();
	void UpdateToLine(UInt32 Line);
	void InitOutlineListView();
	void RefreshOutlineListView(obScriptParsing::Structurizer^ Data);
public:
	DocumentNavigationHelper(view::IScriptEditorView^ View);
	~DocumentNavigationHelper();

	ImplPropertySimple(bool, NavigationBarVisible, CrumbBar->Visible);

	void SyncWithDocument(model::IScriptDocument^ SourceDocument);

	void HandleCrumbBarEvent(view::ViewComponentEvent^ E, model::IScriptDocument^ SourceDocument);
	void HandleListViewEvent(view::ViewComponentEvent^ E, model::IScriptDocument^ SourceDocument);
	void HandleNavigationChangedEvent(model::components::INavigationHelper::NavigationChangedEventArgs^ E, model::IScriptDocument^ SourceDocument);
};


ref struct GlobalFindReplaceResult
{
	ref struct ScriptDocumentData
	{
		property model::IScriptDocument^ Source;
		property String^ SourceDescription;
		property textEditor::FindReplaceResult^ OperationResult;

		ScriptDocumentData(model::IScriptDocument^ Source, textEditor::FindReplaceResult^ OperationResult);

		property int TotalHits
		{
			int get() { return OperationResult->TotalHits; }
		}
	};

	property textEditor::eFindReplaceOperation Operation;
	property String^ Query;
	property String^ Replacement;
	property textEditor::eFindReplaceOptions Options;
	property List<ScriptDocumentData^>^ DocumentsWithHits;

	GlobalFindReplaceResult();

	void Add(model::IScriptDocument^ ScriptDocument, textEditor::FindReplaceResult^ OperationResult);

	property int TotalHitCount
	{
		int get();
	}

	static bool GenericCanExpandGetter(Object^ E);
	static Collections::IEnumerable^ GenericChildrenGetter(Object^ E);
	static Object^ TextAspectGetter(Object^ E);
	static Object^ LineAspectGetter(Object^ E);
	static Object^ HitsAspectGetter(Object^ E);
};

ref class FindReplaceHelper
{
	static Object^ FindReplaceResultsListLineNumberAspectGetter(Object^ E);
	static Object^ FindReplaceResultsListTextAspectGetter(Object^ E);
	static Object^ FindReplaceResultsListHitsAspectGetter(Object^ E);

	static enum class eFindReplaceSource
	{
		CurrentDocumentSelection,
		CurrentDocumentFullText,
		AllDocumentsSelection,
		AllDocumentsFullText
	};

	ref struct FindReplaceSourceDropdownItem
	{
		eFindReplaceSource Source;

		FindReplaceSourceDropdownItem(eFindReplaceSource Source);

		virtual bool Equals(Object^ obj) override;
		virtual int GetHashCode() override;
		virtual String^ ToString() override;
	};

	view::components::IObjectListView^ FindReplaceResultsListView;
	view::components::IObjectListView^ GlobalFindReplaceResultsListView;

	view::components::IDockablePane^ FindReplaceResultsPane;
	view::components::IDockablePane^ GlobalFindReplaceResultsPane;
	view::components::IDockablePane^ FindReplacePane;

	view::components::IComboBox^ FindReplaceFindDropdown;
	view::components::IComboBox^ FindReplaceReplaceDropdown;
	view::components::IComboBox^ FindReplaceLookInDropdown;

	view::components::IButton^ FindReplaceOptionsButtonMatchCase;
	view::components::IButton^ FindReplaceOptionsButtonMatchWholeWord;
	view::components::IButton^ FindReplaceOptionsButtonUseRegEx;
	view::components::IButton^ FindReplaceOptionsButtonIgnoreComments;

	view::components::IButton^ FindReplaceButtonFind;
	view::components::IButton^ FindReplaceButtonReplace;
	view::components::IButton^ FindReplaceButtonCountMatches;

	List<GlobalFindReplaceResult^>^ CachedGlobalFindReplaceResults;
	EventHandler^ PreferencesChangedEventHandler;

	void Preferences_Changed(Object^ Sender, EventArgs^ E);

	void InitResultsListViews();
	void InitFindReplaceLookInDropdown();
	void LoadPreferences();
	void SavePreferences();
	textEditor::eFindReplaceOptions GetSelectedOptions();
	void UpdateDropdownStrings(view::components::IComboBox^ ComboBox);

	void PerformOperation(textEditor::eFindReplaceOperation Operation, IScriptEditorController^ Controller);
public:
	FindReplaceHelper(view::IScriptEditorView^ View);
	~FindReplaceHelper();

	void HandleResultsViewEvent(view::ViewComponentEvent^ E, IScriptEditorController^ Controller);
	void HandleFindReplaceEvent(view::ViewComponentEvent^ E, IScriptEditorController^ Controller);
	void InvalidateScriptDocumentInGlobalResultsCache(model::IScriptDocument^ ScriptDocument);
	int DoOperation(textEditor::eFindReplaceOperation Operation,
					String^ Query, String^ Replacement,
					textEditor::eFindReplaceOptions Options,
					bool InAllOpenDocuments,
					IScriptEditorController^ Controller);
};

ref class InputManager
{
	ref struct ChordData
	{
		KeyCombo^ SecondChord;
		IAction^ Action;

		ChordData(KeyCombo^ SecondChord, IAction^ Action);
		ChordData(IAction^ Action);

		virtual bool Equals(Object^ obj) override;
	};

	// mutually-exclusive tuple
	// the first is not nullptr in the case of a single key chord command
	// and the second is not nullptr when the primary chord has at least one command with a secondary chord
	using ChordDataUnion = Tuple<ChordData^, List<ChordData^>^>;

	List<Keys>^ BlacklistedKeyCodes;
	Dictionary<KeyCombo^, ChordDataUnion^>^ KeyChordCommands;
	KeyCombo^ LastActiveFirstChord;

	ChordData^ LookupDoubleKeyChordCommand(KeyCombo^ First, KeyCombo^ Second);
	ChordData^ LookupSingleKeyChordCommand(KeyCombo^ First);
	bool HasSecondKeyOfChord(KeyCombo^ First);
	bool IsBound(KeyCombo^ Combo);
public:
	InputManager();
	~InputManager();

	void AddKeyChordCommand(IAction^ Action, KeyCombo^ Primary, KeyCombo^ Secondary, bool OverwriteExisting);
	void AddKeyChordCommand(IAction^ Action, KeyCombo^ Primary, bool OverwriteExisting);

	void HandleKeyDown(KeyEventArgs^ E, IScriptEditorController^ Controller);
	void HandleMouseClick(textEditor::TextEditorMouseClickEventArgs^ E, IScriptEditorController^ Controller);

	bool IsKeyBlacklisted(Keys Key);
};


} // namespace components


} // namespace controllerImpl


} // namespace scriptEditor


} // namespace cse