#pragma once
#include "[Common]\AuxiliaryWindowsForm.h"

namespace cse
{
	namespace preferences
	{
		using namespace System::ComponentModel;

		ref class SettingsGroup abstract
		{
			static String^	SectionPrefix = "ScriptEditor::";
		public:
			virtual bool	Validate(SettingsGroup^ OldValue, String^% OutMessage) abstract;
			void			Save();
			bool			Load();
			SettingsGroup^	Clone();

			String^			GetCategoryName();
		};

		ref struct GeneralSettings : public SettingsGroup
		{
			static String^ CategoryName = "General";

			[Category("General")]
			[Description("Automatically indent script lines")]
			property bool AutoIndent;

			[Category("General")]
			[Description("Hide script editor window in Windows taskbar/task-switcher")]
			property bool HideInTaskbar;

			[Category("General")]
			[Description("Save/restore caret position on save/load")]
			property bool SaveRestoreCaret;

			[Category("General")]
			[Description("'Load Script(s)' updates existing scripts if editorIDs match")]
			property bool LoadScriptUpdatesExistingScripts;

			[Category("General")]
			[Description("Cut/copy entire line when no text is selected")]
			property bool CutCopyEntireLine;

			[Category("General")]
			[Description("Recompile dependencies after variable index modification")]
			property bool RecompileDependsOnVarIdxMod;

			GeneralSettings()
			{
				AutoIndent = true;
				HideInTaskbar = false;
				SaveRestoreCaret = false;
				LoadScriptUpdatesExistingScripts = true;
				CutCopyEntireLine = true;
				RecompileDependsOnVarIdxMod = true;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override { return true; }
		};

		ref struct IntelliSenseSettings : public SettingsGroup
		{
			static String^ CategoryName = "IntelliSense";

			[Category("Suggestions")]
			[Description("Automatically display suggestions")]
			property bool ShowSuggestions;

			[Category("Suggestions")]
			[Description("Character threshold for automatic suggestions")]
			property UInt32 SuggestionCharThreshold;

			[Category("Suggestions")]
			[Description("Insert suggestions with ENTER key")]
			property bool InsertSuggestionsWithEnterKey;

			[Category("Suggestions")]
			[Description("Prevent suggestion pop-up from acquiring focus")]
			property bool PreventSuggestionPopupFocus;

			[Category("Suggestions")]
			[Description("Filter suggestions using substring search")]
			property bool UseSubstringSearch;

			[Category("Suggestions")]
			[Description("Maximum number of suggestions to display")]
			property UInt32 MaxSuggestionsToDisplay;

			[Category("Insight Info")]
			[Description("Show info tooltip on mouse hover")]
			property bool ShowInsightToolTip;

			[Category("Insight Info")]
			[Description("Duration in Earth seconds for which the info tooltip is displayed")]
			property UInt32 InsightToolTipDisplayDuration;

			[Category("Insight Info")]
			[Description("Show error messages in info tooltip")]
			property bool ShowErrorsInInsightToolTip;

			[Category("Database")]
			[Description("IntelliSense database update interval in Earth minutes")]
			property UInt32 DatabaseUpdateInterval;

			IntelliSenseSettings()
			{
				ShowSuggestions = true;
				SuggestionCharThreshold = 5;
				InsertSuggestionsWithEnterKey = true;
				PreventSuggestionPopupFocus = false;
				UseSubstringSearch = false;
				MaxSuggestionsToDisplay = 7;
				ShowInsightToolTip = true;
				InsightToolTipDisplayDuration = 8;
				ShowErrorsInInsightToolTip = true;
				DatabaseUpdateInterval = 5;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override;
		};

		ref struct PreprocessorSettings : public SettingsGroup
		{
			static String^ CategoryName = "Preprocessor";

			[Category("Preprocessor")]
			[Description("Allow macro redefinitions")]
			property bool AllowMacroRedefs;

			[Category("Preprocessor")]
			[Description("Number of preprocessing passes to apply")]
			property UInt32 NumPasses;

			PreprocessorSettings()
			{
				AllowMacroRedefs = true;
				NumPasses = 1;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override;
		};

		ref struct AppearanceSettings : public SettingsGroup
		{
			static String^ CategoryName = "Appearance";

			[Category("General")]
			[Description("Text foreground color")]
			property Color ForeColor;

			[Category("General")]
			[Description("Text background color")]
			property Color BackColor;

			[Category("General")]
			[Description("Display size of tab characters")]
			property UInt32 TabSize;

			[Category("General")]
			[Description("Default text font")]
			property Font^ TextFont;

			[Category("General")]
			[Description("Word wrap text")]
			property bool WordWrap;

			[Category("General")]
			[Description("Display tab characters")]
			property bool ShowTabs;

			[Category("General")]
			[Description("Display space characters")]
			property bool ShowSpaces;


			[Category("Adornments")]
			[Description("Show scope breadcrumb toolbar")]
			property bool ShowScopeBar;

			[Category("Adornments")]
			[Description("Show code folding margin")]
			property bool ShowCodeFolding;

			[Category("Adornments")]
			[Description("Show ")]
			property bool ShowBlockVisualizer;


			[Category("Highlighting")]
			[Description("Syntax highlighting foreground color for script keywords")]
			property Color ForeColorKeywords;

			[Category("Highlighting")]
			[Description("Syntax highlighting foreground color for digits")]
			property Color ForeColorDigits;

			[Category("Highlighting")]
			[Description("Syntax highlighting color preprocessor directives")]
			property Color ForeColorPreprocessor;

			[Category("Highlighting")]
			[Description("Syntax highlighting color script block names")]
			property Color ForeColorScriptBlocks;

			[Category("Highlighting")]
			[Description("Syntax highlighting color string literals")]
			property Color ForeColorStringLiterals;

			[Category("Highlighting")]
			[Description("Syntax highlighting foreground color for comments")]
			property Color ForeColorComments;

			[Category("Highlighting")]
			[Description("Syntax highlighting foreground color for local variables")]
			property Color ForeColorLocalVariables;

			[Category("Highlighting")]
			[Description("Highlighting background color for selected text")]
			property Color BackColorSelection;

			[Category("Highlighting")]
			[Description("Highlighting background color for current line")]
			property Color BackColorCurrentLine;

			[Category("Highlighting")]
			[Description("Highlighting background color for lines exceeding the character limit (512)")]
			property Color BackColorCharLimit;

			[Category("Highlighting")]
			[Description("Highlighting color for error squigglies")]
			property Color UnderlineColorError;

			[Category("Highlighting")]
			[Description("Highlighting color for find results")]
			property Color BackColorFindResults;

			[Category("Highlighting")]
			[Description("Use bold-face font style for all highlighted text")]
			property bool BoldFaceHighlightedText;

			AppearanceSettings()
			{
				ForeColor = Control::DefaultForeColor;
				BackColor = Control::DefaultBackColor;
				TabSize = 4;
				TextFont = Control::DefaultFont;
				WordWrap = false;
				ShowTabs = false;
				ShowSpaces = false;

				ShowScopeBar = true;
				ShowCodeFolding = true;
				ShowBlockVisualizer = true;

				ForeColorDigits = Control::DefaultForeColor;
				ForeColorPreprocessor = Control::DefaultForeColor;
				ForeColorScriptBlocks = Control::DefaultForeColor;
				ForeColorStringLiterals = Control::DefaultForeColor;
				ForeColorComments = Control::DefaultForeColor;
				ForeColorLocalVariables = Control::DefaultForeColor;
				BackColorSelection = Color::LightBlue;
				BackColorCurrentLine = Color::LightGray;
				BackColorCharLimit = Color::DarkMagenta;
				UnderlineColorError = Color::Red;
				BackColorFindResults = Color::LightYellow;
				BoldFaceHighlightedText = false;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override;
		};

		ref struct SanitizerSettings : public SettingsGroup
		{
			static String^ CategoryName = "Sanitizer";

			[Category("General")]
			[Description("Normalize identifier casing")]
			property bool NormalizeIdentifiers;

			[Category("General")]
			[Description("Indent script lines")]
			property bool IndentLines;

			[Category("General")]
			[Description("Prefix 'Eval' to 'If' & 'ElseIf' statements")]
			property bool PrefixIfElseIfWithEval;

			[Category("General")]
			[Description("Apply compiler override to script blocks")]
			property bool ApplyCompilerOverride;

			SanitizerSettings()
			{
				NormalizeIdentifiers = true;
				IndentLines = true;
				PrefixIfElseIfWithEval = false;
				ApplyCompilerOverride = false;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override { return true; }
		};

		ref struct BackupSettings : public SettingsGroup
		{
			static String^ CategoryName = "Backup";

			[Category("Auto-Recovery")]
			[Description("Use Auto-Recovery")]
			property bool UseAutoRecovery;

			[Category("Auto-Recovery")]
			[Description("Auto-recovery save interval in Earth minutes")]
			property UInt32 AutoRecoveryInterval;

			BackupSettings()
			{
				UseAutoRecovery = true;
				AutoRecoveryInterval = 5;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override;
		};

		ref struct ValidatorSettings : public SettingsGroup
		{
			static String^ CategoryName = "Validator";

			[Category("Collision Checking")]
			[Description("Check for variable-form name collisions (recommended)")]
			property bool CheckVarFormNameCollisions;

			[Category("Collision Checking")]
			[Description("Check for variable-command name collisions (recommended)")]
			property bool CheckVarCommandNameCollisions;

			[Category("General")]
			[Description("Count local variable references")]
			property bool CountVariableRefs;

			[Category("General")]
			[Description("Suppress local variable references for Quest scripts")]
			property bool NoQuestVariableRefCounting;


			ValidatorSettings()
			{
				CheckVarFormNameCollisions = false;
				CheckVarCommandNameCollisions = false;
				CountVariableRefs = true;
				NoQuestVariableRefCounting = true;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override { return true; }
		};

		ref struct FindReplaceSettings : public SettingsGroup
		{
			static String^ CategoryName = "Find-Replace";

			[Category("General")]
			[Description("Case insensitive search")]
			property bool CaseInsensitive;

			[Category("General")]
			[Description("Match whole word only")]
			property bool MatchWholeWord;

			[Category("General")]
			[Description("Use regular expressions")]
			property bool UseRegEx;

			[Category("General")]
			[Description("Ignore hits inside comments")]
			property bool IgnoreComments;

			[Category("General")]
			[Description("'Ctrl+F' displays inline search panel")]
			property bool ShowInlineSearchPanel;

			FindReplaceSettings()
			{
				CaseInsensitive = false;
				MatchWholeWord = false;
				UseRegEx = true;
				IgnoreComments = true;
				ShowInlineSearchPanel = true;
			}

			virtual bool Validate(SettingsGroup^ OldValue, String^% OutMessage) override { return true; }
		};


		ref class SettingsHolder
		{
			static SettingsHolder^	Singleton = nullptr;

			SettingsHolder()
			{
				General = gcnew GeneralSettings;
				IntelliSense = gcnew IntelliSenseSettings;
				Preprocessor = gcnew PreprocessorSettings;
				Appearance = gcnew AppearanceSettings;
				Sanitizer = gcnew SanitizerSettings;
				Backup = gcnew BackupSettings;
				Validator = gcnew ValidatorSettings;
				FindReplace = gcnew FindReplaceSettings;

				AllGroups = gcnew List<SettingsGroup^>;

				AllGroups->Add(General);
				AllGroups->Add(IntelliSense);
				AllGroups->Add(Preprocessor);
				AllGroups->Add(Appearance);
				AllGroups->Add(Sanitizer);
				AllGroups->Add(Backup);
				AllGroups->Add(Validator);
				AllGroups->Add(FindReplace);
			}
		public:
			GeneralSettings^		General;
			IntelliSenseSettings^	IntelliSense;
			PreprocessorSettings^	Preprocessor;
			AppearanceSettings^		Appearance;
			SanitizerSettings^		Sanitizer;
			BackupSettings^			Backup;
			ValidatorSettings^		Validator;
			FindReplaceSettings^	FindReplace;

			property List<SettingsGroup^>^
									AllGroups;
			event EventHandler^		SavedToDisk;

			void					SaveToDisk();
			void					LoadFromDisk();

			static SettingsHolder^	Get();
		};


		ref class PreferencesDialog : public System::Windows::Forms::Form
		{
			System::ComponentModel::Container^		components;

			PropertyGrid^			PropertyGrid;
			ToolStrip^				ToolStripSettingCategories;
			ToolStripLabel^			ToolStripLabelCategories;
			Label^					LabelCurrentCategory;

			void					ToolStripCategoryButton_Click(Object^ Sender, EventArgs^ E);
			void					Dialog_Cancel(Object^ Sender, CancelEventArgs^ E);

			void					InitializeComponent();
			bool					PopulateCategories();
			bool					SwitchCategory(SettingsGroup^ Group);

			Dictionary<SettingsGroup^, ToolStripButton^>^
									RegisteredCategories;
			SettingsGroup^			CurrentSelection;
			SettingsGroup^			CurrentSelectionSnapshot;
		public:
			PreferencesDialog();
			~PreferencesDialog();
		};
	}
}