#pragma once

#include "AvalonEditDefs.h"
#include "ScriptTextEditorInterface.h"
#include "AvalonEditXSHD.h"
#include "AvalonEditComponents.h"
#include "IntelliSense\IntelliSenseInterface.h"

namespace ConstructionSetExtender
{
	namespace TextEditors
	{
		namespace AvalonEditor
		{
			using namespace ICSharpCode;
			using namespace System::Windows::Forms::Integration;

			typedef System::Windows::Media::Imaging::RenderTargetBitmap			RTBitmap;
			typedef System::EventHandler<AvalonEdit::Editing::TextEventArgs^>	AvalonEditTextEventHandler;

			ref class AvalonEditTextEditor : public IScriptTextEditor
			{
				static AvalonEditXSHDManager^						SyntaxHighlightingManager = gcnew AvalonEditXSHDManager();
			protected:
				static enum class									PreventTextChangeFlagState
				{
					Disabled = 0,
					AutoReset,
					ManualReset
				};

				static enum class									MoveSegmentDirection
				{
					Up = 0,
					Down
				};

				Panel^												WinFormsContainer;
				ElementHost^										WPFHost;
				System::Windows::Controls::DockPanel^				TextFieldPanel;
				AvalonEdit::TextEditor^								TextField;
				System::Windows::Shapes::Rectangle^					AnimationPrimitive;

				ScriptErrorBGColorizer^								ErrorColorizer;
				FindReplaceBGColorizer^								FindReplaceColorizer;
				AvalonEdit::Folding::FoldingManager^				CodeFoldingManager;
				ObScriptCodeFoldingStrategy^						CodeFoldingStrategy;
				BraceHighlightingBGColorizer^						BraceColorizer;

				bool												InitializingFlag;
				bool												ModifiedFlag;
				PreventTextChangeFlagState							PreventTextChangedEventFlag;
				System::Windows::Input::Key							KeyToPreventHandling;
				IntelliSense::IntelliSenseInterface^				IntelliSenseBox;
				int													LastKnownMouseClickOffset;
				System::Windows::Input::Key							LastKeyThatWentDown;

				System::Windows::Point								MiddleMouseScrollStartPoint;
				System::Windows::Vector								MiddleMouseCurrentScrollOffset;
				bool												IsMiddleMouseScrolling;
				Timer^												MiddleMouseScrollTimer;

				bool												IsFocused;

				Timer^												ScrollBarSyncTimer;
				VScrollBar^											ExternalVerticalScrollBar;
				HScrollBar^											ExternalHorizontalScrollBar;
				bool												SynchronizingExternalScrollBars;
				bool												SynchronizingInternalScrollBars;
				System::Windows::Vector								PreviousScrollOffsetBuffer;

				bool												SetTextAnimating;
				System::Windows::Media::Animation::DoubleAnimation^	SetTextPrologAnimationCache;
				UInt32												ParentWorkspaceIndex;

				Timer^												SemanticAnalysisTimer;
				bool												TextFieldInUpdateFlag;

				int													PreviousLineBuffer;
				ObScriptSemanticAnalysis::AnalysisData^				SemanticAnalysisCache;

				EventHandler^										TextFieldTextChangedHandler;
				EventHandler^										TextFieldCaretPositionChangedHandler;
				EventHandler^										TextFieldScrollOffsetChangedHandler;
				System::Windows::Input::KeyEventHandler^			TextFieldKeyUpHandler;
				System::Windows::Input::KeyEventHandler^			TextFieldKeyDownHandler;
				System::Windows::Input::MouseButtonEventHandler^	TextFieldMouseDownHandler;
				System::Windows::Input::MouseButtonEventHandler^	TextFieldMouseUpHandler;
				System::Windows::Input::MouseWheelEventHandler^		TextFieldMouseWheelHandler;
				System::Windows::Input::MouseEventHandler^			TextFieldMouseHoverHandler;
				System::Windows::Input::MouseEventHandler^			TextFieldMouseHoverStoppedHandler;
				EventHandler^										TextFieldSelectionChangedHandler;
				System::Windows::RoutedEventHandler^				TextFieldLostFocusHandler;
				System::Windows::Input::MouseEventHandler^			TextFieldMiddleMouseScrollMoveHandler;
				System::Windows::Input::MouseButtonEventHandler^	TextFieldMiddleMouseScrollDownHandler;
				EventHandler^										MiddleMouseScrollTimerTickHandler;
				EventHandler^										ScrollBarSyncTimerTickHandler;
				EventHandler^										SemanticAnalysisTimerTickHandler;
				EventHandler^										ExternalScrollBarValueChangedHandler;
				EventHandler^										SetTextAnimationCompletedHandler;
				EventHandler^										ScriptEditorPreferencesSavedHandler;
				AvalonEditTextEventHandler^							TextFieldTextCopiedHandler;

				virtual void								OnScriptModified(bool ModificationState);
				virtual void								OnKeyDown(System::Windows::Input::KeyEventArgs^ E);
				virtual void								OnMouseClick(System::Windows::Input::MouseButtonEventArgs^ E);

				void										TextField_TextChanged(Object^ Sender, EventArgs^ E);
				void										TextField_CaretPositionChanged(Object^ Sender, EventArgs^ E);
				void										TextField_ScrollOffsetChanged(Object^ Sender, EventArgs^ E);
				void										TextField_TextCopied(Object^ Sender, AvalonEdit::Editing::TextEventArgs^ E);

				void										TextField_KeyUp(Object^ Sender, System::Windows::Input::KeyEventArgs^ E);
				void										TextField_KeyDown(Object^ Sender, System::Windows::Input::KeyEventArgs^ E);
				void										TextField_MouseDown(Object^ Sender, System::Windows::Input::MouseButtonEventArgs^ E);
				void										TextField_MouseUp(Object^ Sender, System::Windows::Input::MouseButtonEventArgs^ E);
				void										TextField_MouseWheel(Object^ Sender, System::Windows::Input::MouseWheelEventArgs^ E);

				void										TextField_MouseHover(Object^ Sender, System::Windows::Input::MouseEventArgs^ E);
				void										TextField_MouseHoverStopped(Object^ Sender, System::Windows::Input::MouseEventArgs^ E);

				void										TextField_SelectionChanged(Object^ Sender, EventArgs^ E);
				void										TextField_LostFocus(Object^ Sender, System::Windows::RoutedEventArgs^ E);

				void										TextField_MiddleMouseScrollMove(Object^ Sender, System::Windows::Input::MouseEventArgs^ E);
				void										TextField_MiddleMouseScrollDown(Object^ Sender, System::Windows::Input::MouseButtonEventArgs^ E);

				void										MiddleMouseScrollTimer_Tick(Object^ Sender, EventArgs^ E);
				void										ScrollBarSyncTimer_Tick(Object^ Sender, EventArgs^ E);
				void										SemanticAnalysisTimer_Tick(Object^ Sender, EventArgs^ E);

				void										ExternalScrollBar_ValueChanged(Object^ Sender, EventArgs^ E);
				void										SetTextAnimation_Completed(Object^ Sender, EventArgs^ E);
				void										ScriptEditorPreferences_Saved(Object^ Sender, EventArgs^ E);

				String^										GetTokenAtIndex(int Index, bool SelectText, int% StartIndexOut, int% EndIndexOut);
				String^										GetTextAtLocation(Point Location, bool SelectText);		// line breaks need to be replaced by the caller
				String^										GetTextAtLocation(int Index, bool SelectText);
				array<String^>^								GetTextAtLocation(int Index);							// gets three of the closest tokens surrounding the offset

				bool										GetCharIndexInsideStringSegment(int Index);

				void										SetPreventTextChangedFlag(PreventTextChangeFlagState State) { PreventTextChangedEventFlag = State; }
				void										HandleKeyEventForKey(System::Windows::Input::Key Key) { KeyToPreventHandling = Key; }

				void										HandleTextChangeEvent();
				void										GotoLine(int Line);										// line numbers start at 1

				void										RefreshBGColorizerLayer();
				void										RefreshTextView();
				int											PerformFindReplaceOperationOnSegment(System::Text::RegularExpressions::Regex^ ExpressionParser, IScriptTextEditor::FindReplaceOperation Operation, AvalonEdit::Document::DocumentLine^ Line, String^ Replacement, IScriptTextEditor::FindReplaceOutput^ Output, UInt32 Options);
				void										StartMiddleMouseScroll(System::Windows::Input::MouseButtonEventArgs^ E);
				void										StopMiddleMouseScroll();

				void										UpdateSemanticAnalysisCache(bool FillVariables, bool FillControlBlocks);
				void										UpdateCodeFoldings();
				void										UpdateSyntaxHighlighting(bool Regenerate);
				void										SynchronizeExternalScrollBars();

				void										MoveTextSegment(AvalonEdit::Document::ISegment^ Segment, MoveSegmentDirection Direction);

				RTBitmap^									RenderFrameworkElement(System::Windows::FrameworkElement^ Element);
				void										ClearFindResultIndicators(void);
				void										SearchBracesForHighlighting(int CaretPos);
				AvalonEditHighlightingDefinition^			CreateSyntaxHighlightDefinitions(bool UpdateStableDefs);
				String^										SanitizeUnicodeString(String^ In);			// removes unsupported characters
				virtual void								Destroy();

				static const double							kSetTextFadeAnimationDuration = 0.10;		// in seconds
			public:
				AvalonEditTextEditor(Font^ Font, UInt32 ParentWorkspaceIndex);
				virtual ~AvalonEditTextEditor();

				// interface events
				virtual event TextEditorScriptModifiedEventHandler^			ScriptModified;
				virtual event KeyEventHandler^								KeyDown;
				virtual event TextEditorMouseClickEventHandler^				MouseClick;

				// interface methods
				virtual void										SetFont(Font^ FontObject);
				virtual void										SetTabCharacterSize(int PixelWidth);	// AvalonEdit uses character lengths
				virtual void										SetContextMenu(ContextMenuStrip^% Strip);

				virtual void										AddControl(Control^ ControlObject);

				virtual String^										GetText(void);
				virtual UInt32										GetTextLength(void);
				virtual String^										GetTextAtLine(int LineNumber);
				virtual void										SetText(String^ Text, bool PreventTextChangedEventHandling, bool ResetUndoStack);
				virtual void										InsertText(String^ Text, int Index, bool PreventTextChangedEventHandling);

				virtual String^										GetSelectedText(void);
				virtual void										SetSelectedText(String^ Text, bool PreventTextChangedEventHandling);

				virtual void										SetSelectionStart(int Index);
				virtual void										SetSelectionLength(int Length);
				virtual bool										GetInSelection(int Index);

				virtual int											GetCharIndexFromPosition(Point Position);
				virtual Point										GetPositionFromCharIndex(int Index);
				virtual Point										GetAbsolutePositionFromCharIndex(int Index);
				virtual int											GetLineNumberFromCharIndex(int Index);
				virtual bool										GetCharIndexInsideCommentSegment(int Index);
				virtual int											GetCurrentLineNumber(void);

				virtual String^										GetTokenAtCharIndex(int Offset);
				virtual String^										GetTokenAtCaretPos();
				virtual void										SetTokenAtCaretPos(String^ Replacement);
				virtual String^										GetTokenAtMouseLocation();
				virtual array<String^>^								GetTokensAtMouseLocation();

				virtual int											GetCaretPos();
				virtual void										SetCaretPos(int Index);
				virtual void										ScrollToCaret();

				virtual IntPtr										GetHandle();

				virtual void										FocusTextArea();
				virtual void										LoadFileFromDisk(String^ Path);
				virtual void										SaveScriptToDisk(String^ Path, bool PathIncludesFileName, String^ DefaultName, String^ DefaultExtension);

				virtual bool										GetModifiedStatus();
				virtual void										SetModifiedStatus(bool Modified);

				virtual bool										GetInitializingStatus();
				virtual void										SetInitializingStatus(bool Initializing);

				virtual int											GetLastKnownMouseClickOffset(void);

				virtual int											FindReplace(IScriptTextEditor::FindReplaceOperation Operation, String^ Query, String^ Replacement, IScriptTextEditor::FindReplaceOutput^ Output, UInt32 Options);
				virtual void										ToggleComment(int StartIndex);
				virtual void										UpdateIntelliSenseLocalDatabase(void);

				virtual Control^									GetContainer();
				virtual void										ScrollToLine(String^ LineNumber);
				virtual void										ScrollToLine(UInt32 LineNumber);
				virtual Point										PointToScreen(Point Location);
				virtual bool										GetLineVisible(UInt32 LineNumber);

				virtual void										HighlightScriptError(int Line);
				virtual void										ClearScriptErrorHighlights(void);
				virtual void										SetEnabledState(bool State);

				virtual void										OnGotFocus(void);
				virtual void										OnLostFocus(void);

				virtual void										BeginUpdate(void);
				virtual void										EndUpdate(bool FlagModification);
				virtual UInt32										GetTotalLineCount(void);
				virtual IntelliSense::IntelliSenseInterface^		GetIntelliSenseInterface(void);
				virtual UInt32										GetIndentLevel(UInt32 LineNumber);
				virtual void										InsertVariable(String^ VariableName, ObScriptSemanticAnalysis::Variable::DataType VariableType);

				ObScriptSemanticAnalysis::AnalysisData^				GetSemanticAnalysisCache(bool UpdateVars, bool UpdateControlBlocks);
			};
		}
	}
}