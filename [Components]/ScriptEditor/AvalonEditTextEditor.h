#pragma once

#include "AvalonEditDefs.h"
#include "AvalonEditXSHD.h"
#include "AvalonEditComponents.h"
#include "IntelliSense\IntelliSenseInterface.h"
#include "WorkspaceModelInterface.h"

#define AvalonEditTextEditorDeclareClickHandler(Name)		EventHandler^ Name##ClickHandler; \
															void AvalonEditTextEditor::##Name##_Click(Object^ Sender, EventArgs^ E)
#define AvalonEditTextEditorDefineClickHandler(Name)		Name##ClickHandler = gcnew EventHandler(this, &AvalonEditTextEditor::##Name##_Click)
#define AvalonEditTextEditorSubscribeClickEvent(Name)		Name##->Click += Name##ClickHandler
#define AvalonEditTextEditorUnsubscribeClickEvent(Name)		Name##->Click -= Name##ClickHandler

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

			delegate void JumpToScriptHandler(String^ TargetEditorID);

			ref class AvalonEditTextEditor : public IScriptTextEditor
			{
				static const double									kSetTextFadeAnimationDuration = 0.10;		// in seconds

				static String^										kMetadataBlockMarker = "CSEBlock";
				static String^										kMetadataSigilCaret = "CSECaretPos";

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

				Timer^												SemanticAnalysisTimer;
				bool												TextFieldInUpdateFlag;

				int													PreviousLineBuffer;
				ObScriptSemanticAnalysis::AnalysisData^				SemanticAnalysisCache;

				ScriptEditor::IWorkspaceModel^						ParentModel;
				LineTrackingManager^								LineTracker;
				JumpToScriptHandler^								JumpScriptDelegate;

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

				ContextMenuStrip^									TextEditorContextMenu;
				ToolStripMenuItem^									ContextMenuCopy;
				ToolStripMenuItem^									ContextMenuPaste;
				ToolStripMenuItem^									ContextMenuToggleComment;
				ToolStripMenuItem^									ContextMenuAddBookmark;
				ToolStripMenuItem^									ContextMenuWord;
				ToolStripMenuItem^									ContextMenuWikiLookup;
				ToolStripMenuItem^									ContextMenuOBSEDocLookup;
				ToolStripMenuItem^									ContextMenuDirectLink;
				ToolStripMenuItem^									ContextMenuJumpToScript;
				ToolStripMenuItem^									ContextMenuGoogleLookup;
				ToolStripMenuItem^									ContextMenuOpenImportFile;
				ToolStripMenuItem^									ContextMenuRefactorAddVariable;
				ToolStripMenuItem^									ContextMenuRefactorAddVariableInt;
				ToolStripMenuItem^									ContextMenuRefactorAddVariableFloat;
				ToolStripMenuItem^									ContextMenuRefactorAddVariableRef;
				ToolStripMenuItem^									ContextMenuRefactorAddVariableString;
				ToolStripMenuItem^									ContextMenuRefactorAddVariableArray;
				ToolStripMenuItem^									ContextMenuRefactorCreateUDFImplementation;

				AvalonEditTextEditorDeclareClickHandler(ContextMenuCopy);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuPaste);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuToggleComment);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuAddBookmark);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuWikiLookup);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuOBSEDocLookup);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuDirectLink);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuGoogleLookup);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuJumpToScript);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuOpenImportFile);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuRefactorAddVariable);
				AvalonEditTextEditorDeclareClickHandler(ContextMenuRefactorCreateUDFImplementation);

				CancelEventHandler^							TextEditorContextMenuOpeningHandler;
				void                                        TextEditorContextMenu_Opening(Object^ Sender, CancelEventArgs^ E);

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

				void										RoutePreprocessorMessages(int Line, String^ Message);

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
				int											PerformFindReplaceOperationOnSegment(System::Text::RegularExpressions::Regex^ ExpressionParser,
																								 IScriptTextEditor::FindReplaceOperation Operation,
																								 AvalonEdit::Document::DocumentLine^ Line,
																								 String^ Replacement,
																								 UInt32 Options);
				void										StartMiddleMouseScroll(System::Windows::Input::MouseButtonEventArgs^ E);
				void										StopMiddleMouseScroll();

				void										UpdateSemanticAnalysisCache(bool FillVariables, bool FillControlBlocks, bool FullValidation);
				void										UpdateCodeFoldings();
				void										UpdateSyntaxHighlighting(bool Regenerate);
				void										SynchronizeExternalScrollBars();

				void										MoveTextSegment(AvalonEdit::Document::ISegment^ Segment, MoveSegmentDirection Direction);

				RTBitmap^									RenderFrameworkElement(System::Windows::FrameworkElement^ Element);
				void										ClearFindResultIndicators(void);
				void										SearchBracesForHighlighting(int CaretPos);
				AvalonEditHighlightingDefinition^			CreateSyntaxHighlightDefinitions(bool UpdateStableDefs);
				String^										SanitizeUnicodeString(String^ In);			// removes unsupported characters

				void										SetFont(Font^ FontObject);
				void										SetTabCharacterSize(int PixelWidth);	// AvalonEdit uses character lengths

				String^										GetTextAtLine(int LineNumber);
				UInt32										GetTextLength(void);
				void										InsertText(String^ Text, int Index, bool PreventTextChangedEventHandling);			// performs bounds check

				void										SetSelectionStart(int Index);
				void										SetSelectionLength(int Length);
				bool										GetInSelection(int Index);

				int											GetLineNumberFromCharIndex(int Index);
				bool										GetCharIndexInsideCommentSegment(int Index);

				String^										GetTokenAtMouseLocation();
				array<String^>^								GetTokensAtMouseLocation();	// gets three of the closest tokens surrounding the mouse loc
				int											GetLastKnownMouseClickOffset(void);
				void										ToggleComment(int StartIndex);
				void										AddBookmark(int Index);

				void										UpdateIntelliSenseLocalDatabase(void);

				bool										GetLineVisible(UInt32 LineNumber);	// inside the text field's viewable area

				void                                        SerializeCaretPos(String^% Result);
				void                                        SerializeBookmarks(String^% Result);
				void                                        DeserializeCaretPos(String^ ExtractedBlock);
				void                                        DeserializeBookmarks(String^ ExtractedBlock);
			public:
				AvalonEditTextEditor(ScriptEditor::IWorkspaceModel^ ParentModel, JumpToScriptHandler^ JumpScriptDelegate, Font^ Font, int TabSize);
				~AvalonEditTextEditor();

				ObScriptSemanticAnalysis::AnalysisData^						GetSemanticAnalysisCache(bool UpdateVars, bool UpdateControlBlocks);

#pragma region Interfaces
				virtual event TextEditorScriptModifiedEventHandler^			ScriptModified;
				virtual event KeyEventHandler^								KeyDown;
				virtual event TextEditorMouseClickEventHandler^				MouseClick;

				property Control^							Container
				{
					virtual Control^ get() { return WinFormsContainer; }
					virtual void set(Control^ e) {}
				}
				property IntPtr								WindowHandle
				{
					virtual IntPtr get() { return WinFormsContainer->Handle; }
					virtual void set(IntPtr e) {}
				}
				property bool								Enabled
				{
					virtual bool get() { return WPFHost->Enabled; }
					virtual void set(bool e) { WPFHost->Enabled = e; }
				}
				property int								CurrentLine
				{
					virtual int get() { return TextField->TextArea->Caret->Line; }
					virtual void set(int e) {}
				}
				property int								LineCount
				{
					virtual int get() { return TextField->Document->LineCount; }
					virtual void set(int e) {}
				}
				property int								Caret
				{
					virtual int get() { return TextField->TextArea->Caret->Offset; }
					virtual void set(int Index)
					{
						TextField->SelectionLength = 0;
						if (Index > GetTextLength())
							Index = GetTextLength() - 1;

						if (Index > -1)
							TextField->TextArea->Caret->Offset = Index;
						else
							TextField->TextArea->Caret->Offset = 0;

						ScrollToCaret();
					}
				}
				property bool								Modified
				{
					virtual bool get() { return ModifiedFlag; }
					virtual void set(bool State)
					{
						ModifiedFlag = State;
						OnScriptModified(Modified);
					}
				}

				virtual void								Bind(ListView^ MessageList, ListView^ BookmarkList, ListView^ FindResultList);
				virtual void								Unbind();

				virtual String^								GetText();
				virtual String^								GetPreprocessedText(bool% OutPreprocessResult, bool SuppressErrors);
				virtual void								SetText(String^ Text, bool PreventTextChangedEventHandling, bool ResetUndoStack);

				virtual String^								GetSelectedText(void);
				virtual void								SetSelectedText(String^ Text, bool PreventTextChangedEventHandling);

				virtual int									GetCharIndexFromPosition(Point Position);
				virtual Point								GetPositionFromCharIndex(int Index, bool Absolute);

				virtual String^								GetTokenAtCharIndex(int Offset);
				virtual String^								GetTokenAtCaretPos();
				virtual void								SetTokenAtCaretPos(String^ Replacement);

				virtual void								ScrollToCaret();

				virtual void								FocusTextArea();
				virtual void								LoadFileFromDisk(String^ Path);
				virtual void								SaveScriptToDisk(String^ Path, bool PathIncludesFileName, String^ DefaultName, String^ DefaultExtension);

				virtual int									FindReplace(IScriptTextEditor::FindReplaceOperation Operation,
																		String^ Query,
																		String^ Replacement,
																		UInt32 Options);

				virtual void								ScrollToLine(UInt32 LineNumber);
				virtual Point								PointToScreen(Point Location);

				virtual void								BeginUpdate(void);
				virtual void								EndUpdate(bool FlagModification);

				virtual UInt32								GetIndentLevel(UInt32 LineNumber);
				virtual void								InsertVariable(String^ VariableName, ObScriptSemanticAnalysis::Variable::DataType VariableType);

				virtual String^								SerializeMetadata(bool AddPreprocessorSigil);
				virtual String^								DeserializeMetadata(String^ Input, bool SetText);
				virtual bool								CanCompile(bool% OutContainsPreprocessorDirectives);

				virtual void								ClearTrackedData(bool CompilerMessages,
																			 bool PreprocessorMessages,
																			 bool ValidatorMessages,
																			 bool Bookmarks,
																			 bool FindResults);
				virtual void								TrackCompilerError(int Line, String^ Message);
#pragma endregion
			};
		}
	}
}