#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace UIComponents {

	/// <summary>
	/// Summary for TagBrowser
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class TagBrowser : public System::Windows::Forms::Form
	{
	public:
		TagBrowser(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TagBrowser()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  SearchBox;
	protected: 


	private: System::Windows::Forms::ListView^  FormList;
	private: System::Windows::Forms::ColumnHeader^  FormListHEditorID;
	private: System::Windows::Forms::ColumnHeader^  FormListHRefID;
	private: System::Windows::Forms::ColumnHeader^  FormListHType;
	private: System::Windows::Forms::ListView^  SelectionList;
	private: System::Windows::Forms::ColumnHeader^  SelectionListHEditorId;
	private: System::Windows::Forms::ColumnHeader^  SelectionListHRefID;
	private: System::Windows::Forms::ColumnHeader^  SelectionListHType;
	private: DevComponents::AdvTree::AdvTree^  TagTree;


	private: DevComponents::AdvTree::NodeConnector^  TagTreeNodeConnector;
	private: DevComponents::DotNetBar::ElementStyle^  TagTreeElementStyle1;


	private: System::Windows::Forms::Button^  AddObjectSelection;
	private: System::Windows::Forms::Button^  PlaceSelection;


	private: System::Windows::Forms::Label^  LabelSelectionList;
	private: System::Windows::Forms::CheckBox^  ClearSelectionOnInstantiation;

	private: System::Windows::Forms::CheckBox^  CustomPos;

	private: System::Windows::Forms::TextBox^  PositionX;
	private: System::Windows::Forms::TextBox^  PositionZ;

	private: System::Windows::Forms::TextBox^  PositionY;
	private: System::Windows::Forms::CheckBox^  CustomRot;
	private: System::Windows::Forms::TextBox^  RotationY;
	private: System::Windows::Forms::TextBox^  RotationZ;


	private: System::Windows::Forms::TextBox^  RotationX;
	private: DevComponents::DotNetBar::ElementStyle^  TagTreeElementStyle2;
	private: System::Windows::Forms::Button^  ShowSelectionControls;
	private: System::Windows::Forms::ContextMenuStrip^  TagTreeContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  TagTreeContextMenuAdd;
	private: System::Windows::Forms::ToolStripMenuItem^  TagTreeContextMenuRemove;

	private: System::Windows::Forms::ContextMenuStrip^  FormListContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  FormListContextMenuAdd;


	private: System::Windows::Forms::ContextMenuStrip^  SelectionListContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  SelectionListContextMenuRemove;
	private: System::Windows::Forms::Button^  SaveTags;
	private: System::Windows::Forms::Button^  LoadTags;













	private: System::ComponentModel::IContainer^  components;
















	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->SearchBox = (gcnew System::Windows::Forms::TextBox());
			this->FormList = (gcnew System::Windows::Forms::ListView());
			this->FormListHEditorID = (gcnew System::Windows::Forms::ColumnHeader());
			this->FormListHRefID = (gcnew System::Windows::Forms::ColumnHeader());
			this->FormListHType = (gcnew System::Windows::Forms::ColumnHeader());
			this->FormListContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->FormListContextMenuAdd = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SelectionList = (gcnew System::Windows::Forms::ListView());
			this->SelectionListHEditorId = (gcnew System::Windows::Forms::ColumnHeader());
			this->SelectionListHRefID = (gcnew System::Windows::Forms::ColumnHeader());
			this->SelectionListHType = (gcnew System::Windows::Forms::ColumnHeader());
			this->SelectionListContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->SelectionListContextMenuRemove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TagTree = (gcnew DevComponents::AdvTree::AdvTree());
			this->TagTreeContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->TagTreeContextMenuAdd = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TagTreeContextMenuRemove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TagTreeNodeConnector = (gcnew DevComponents::AdvTree::NodeConnector());
			this->TagTreeElementStyle2 = (gcnew DevComponents::DotNetBar::ElementStyle());
			this->TagTreeElementStyle1 = (gcnew DevComponents::DotNetBar::ElementStyle());
			this->AddObjectSelection = (gcnew System::Windows::Forms::Button());
			this->PlaceSelection = (gcnew System::Windows::Forms::Button());
			this->LabelSelectionList = (gcnew System::Windows::Forms::Label());
			this->ClearSelectionOnInstantiation = (gcnew System::Windows::Forms::CheckBox());
			this->CustomPos = (gcnew System::Windows::Forms::CheckBox());
			this->PositionX = (gcnew System::Windows::Forms::TextBox());
			this->PositionZ = (gcnew System::Windows::Forms::TextBox());
			this->PositionY = (gcnew System::Windows::Forms::TextBox());
			this->CustomRot = (gcnew System::Windows::Forms::CheckBox());
			this->RotationY = (gcnew System::Windows::Forms::TextBox());
			this->RotationZ = (gcnew System::Windows::Forms::TextBox());
			this->RotationX = (gcnew System::Windows::Forms::TextBox());
			this->ShowSelectionControls = (gcnew System::Windows::Forms::Button());
			this->SaveTags = (gcnew System::Windows::Forms::Button());
			this->LoadTags = (gcnew System::Windows::Forms::Button());
			this->FormListContextMenu->SuspendLayout();
			this->SelectionListContextMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TagTree))->BeginInit();
			this->TagTreeContextMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// SearchBox
			// 
			this->SearchBox->Location = System::Drawing::Point(245, 389);
			this->SearchBox->Multiline = true;
			this->SearchBox->Name = L"SearchBox";
			this->SearchBox->Size = System::Drawing::Size(219, 33);
			this->SearchBox->TabIndex = 1;
			// 
			// FormList
			// 
			this->FormList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->FormListHEditorID, 
				this->FormListHRefID, this->FormListHType});
			this->FormList->ContextMenuStrip = this->FormListContextMenu;
			this->FormList->FullRowSelect = true;
			this->FormList->Location = System::Drawing::Point(245, 12);
			this->FormList->Name = L"FormList";
			this->FormList->Size = System::Drawing::Size(384, 371);
			this->FormList->TabIndex = 2;
			this->FormList->UseCompatibleStateImageBehavior = false;
			this->FormList->View = System::Windows::Forms::View::Details;
			// 
			// FormListHEditorID
			// 
			this->FormListHEditorID->Text = L"EditorID";
			this->FormListHEditorID->Width = 198;
			// 
			// FormListHRefID
			// 
			this->FormListHRefID->Text = L"FormID";
			this->FormListHRefID->Width = 70;
			// 
			// FormListHType
			// 
			this->FormListHType->Text = L"Type";
			this->FormListHType->Width = 111;
			// 
			// FormListContextMenu
			// 
			this->FormListContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->FormListContextMenuAdd});
			this->FormListContextMenu->Name = L"FormListContextMenu";
			this->FormListContextMenu->Size = System::Drawing::Size(165, 26);
			// 
			// FormListContextMenuAdd
			// 
			this->FormListContextMenuAdd->Name = L"FormListContextMenuAdd";
			this->FormListContextMenuAdd->Size = System::Drawing::Size(164, 22);
			this->FormListContextMenuAdd->Text = L"Add To Selection";
			// 
			// SelectionList
			// 
			this->SelectionList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->SelectionListHEditorId, 
				this->SelectionListHRefID, this->SelectionListHType});
			this->SelectionList->ContextMenuStrip = this->SelectionListContextMenu;
			this->SelectionList->FullRowSelect = true;
			this->SelectionList->Location = System::Drawing::Point(692, 42);
			this->SelectionList->Name = L"SelectionList";
			this->SelectionList->Size = System::Drawing::Size(350, 236);
			this->SelectionList->TabIndex = 3;
			this->SelectionList->UseCompatibleStateImageBehavior = false;
			this->SelectionList->View = System::Windows::Forms::View::Details;
			// 
			// SelectionListHEditorId
			// 
			this->SelectionListHEditorId->Text = L"EditorID";
			this->SelectionListHEditorId->Width = 128;
			// 
			// SelectionListHRefID
			// 
			this->SelectionListHRefID->Text = L"FormID";
			this->SelectionListHRefID->Width = 70;
			// 
			// SelectionListHType
			// 
			this->SelectionListHType->Text = L"Type";
			this->SelectionListHType->Width = 111;
			// 
			// SelectionListContextMenu
			// 
			this->SelectionListContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->SelectionListContextMenuRemove});
			this->SelectionListContextMenu->Name = L"SelectionListContextMenu";
			this->SelectionListContextMenu->Size = System::Drawing::Size(200, 26);
			// 
			// SelectionListContextMenuRemove
			// 
			this->SelectionListContextMenuRemove->Name = L"SelectionListContextMenuRemove";
			this->SelectionListContextMenuRemove->Size = System::Drawing::Size(199, 22);
			this->SelectionListContextMenuRemove->Text = L"Remove From Selection";
			// 
			// TagTree
			// 
			this->TagTree->AccessibleRole = System::Windows::Forms::AccessibleRole::Outline;
			this->TagTree->AllowDrop = true;
			this->TagTree->BackColor = System::Drawing::SystemColors::Window;
			// 
			// 
			// 
			this->TagTree->BackgroundStyle->Class = L"TreeBorderKey";
			this->TagTree->CellEdit = true;
			this->TagTree->ColorSchemeStyle = DevComponents::AdvTree::eColorSchemeStyle::VS2005;
			this->TagTree->ColumnsVisible = false;
			this->TagTree->ContextMenuStrip = this->TagTreeContextMenu;
			this->TagTree->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->TagTree->GridRowLines = true;
			this->TagTree->HideSelection = true;
			this->TagTree->HotTracking = true;
			this->TagTree->Location = System::Drawing::Point(9, 12);
			this->TagTree->Name = L"TagTree";
			this->TagTree->NodesConnector = this->TagTreeNodeConnector;
			this->TagTree->NodeSpacing = 4;
			this->TagTree->NodeStyle = this->TagTreeElementStyle2;
			this->TagTree->PathSeparator = L";";
			this->TagTree->SelectionBoxStyle = DevComponents::AdvTree::eSelectionStyle::NodeMarker;
			this->TagTree->SelectionPerCell = true;
			this->TagTree->Size = System::Drawing::Size(225, 409);
			this->TagTree->Styles->Add(this->TagTreeElementStyle1);
			this->TagTree->Styles->Add(this->TagTreeElementStyle2);
			this->TagTree->TabIndex = 4;
			this->TagTree->Text = L"Tags";
			// 
			// TagTreeContextMenu
			// 
			this->TagTreeContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->TagTreeContextMenuAdd, 
				this->TagTreeContextMenuRemove});
			this->TagTreeContextMenu->Name = L"TagTreeContextMenu";
			this->TagTreeContextMenu->Size = System::Drawing::Size(141, 48);
			// 
			// TagTreeContextMenuAdd
			// 
			this->TagTreeContextMenuAdd->Name = L"TagTreeContextMenuAdd";
			this->TagTreeContextMenuAdd->Size = System::Drawing::Size(140, 22);
			this->TagTreeContextMenuAdd->Text = L"Add Tag";
			// 
			// TagTreeContextMenuRemove
			// 
			this->TagTreeContextMenuRemove->Name = L"TagTreeContextMenuRemove";
			this->TagTreeContextMenuRemove->Size = System::Drawing::Size(140, 22);
			this->TagTreeContextMenuRemove->Text = L"Remove Tag";
			// 
			// TagTreeNodeConnector
			// 
			this->TagTreeNodeConnector->DashStyle = System::Drawing::Drawing2D::DashStyle::Solid;
			this->TagTreeNodeConnector->LineColor = System::Drawing::SystemColors::ControlText;
			// 
			// TagTreeElementStyle2
			// 
			this->TagTreeElementStyle2->BackColor = System::Drawing::Color::White;
			this->TagTreeElementStyle2->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(228)), 
				static_cast<System::Int32>(static_cast<System::Byte>(228)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->TagTreeElementStyle2->BackColorGradientAngle = 90;
			this->TagTreeElementStyle2->BorderBottom = DevComponents::DotNetBar::eStyleBorderType::Solid;
			this->TagTreeElementStyle2->BorderBottomWidth = 1;
			this->TagTreeElementStyle2->BorderColor = System::Drawing::Color::DarkGray;
			this->TagTreeElementStyle2->BorderLeft = DevComponents::DotNetBar::eStyleBorderType::Solid;
			this->TagTreeElementStyle2->BorderLeftWidth = 1;
			this->TagTreeElementStyle2->BorderRight = DevComponents::DotNetBar::eStyleBorderType::Solid;
			this->TagTreeElementStyle2->BorderRightWidth = 1;
			this->TagTreeElementStyle2->BorderTop = DevComponents::DotNetBar::eStyleBorderType::Solid;
			this->TagTreeElementStyle2->BorderTopWidth = 1;
			this->TagTreeElementStyle2->CornerDiameter = 4;
			this->TagTreeElementStyle2->Description = L"Gray";
			this->TagTreeElementStyle2->Name = L"TagTreeElementStyle2";
			this->TagTreeElementStyle2->PaddingBottom = 1;
			this->TagTreeElementStyle2->PaddingLeft = 1;
			this->TagTreeElementStyle2->PaddingRight = 1;
			this->TagTreeElementStyle2->PaddingTop = 1;
			this->TagTreeElementStyle2->TextColor = System::Drawing::Color::Black;
			// 
			// TagTreeElementStyle1
			// 
			this->TagTreeElementStyle1->Name = L"TagTreeElementStyle1";
			this->TagTreeElementStyle1->TextColor = System::Drawing::SystemColors::ControlText;
			// 
			// AddObjectSelection
			// 
			this->AddObjectSelection->Location = System::Drawing::Point(471, 389);
			this->AddObjectSelection->Name = L"AddObjectSelection";
			this->AddObjectSelection->Size = System::Drawing::Size(157, 32);
			this->AddObjectSelection->TabIndex = 5;
			this->AddObjectSelection->Text = L"Add Object Window Selection";
			this->AddObjectSelection->UseVisualStyleBackColor = true;
			// 
			// PlaceSelection
			// 
			this->PlaceSelection->Location = System::Drawing::Point(692, 387);
			this->PlaceSelection->Name = L"PlaceSelection";
			this->PlaceSelection->Size = System::Drawing::Size(350, 32);
			this->PlaceSelection->TabIndex = 6;
			this->PlaceSelection->Text = L"Place Selection In Active Cell";
			this->PlaceSelection->UseVisualStyleBackColor = true;
			// 
			// LabelSelectionList
			// 
			this->LabelSelectionList->Font = (gcnew System::Drawing::Font(L"Lucida Grande", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LabelSelectionList->Location = System::Drawing::Point(692, 12);
			this->LabelSelectionList->Name = L"LabelSelectionList";
			this->LabelSelectionList->Size = System::Drawing::Size(350, 27);
			this->LabelSelectionList->TabIndex = 7;
			this->LabelSelectionList->Text = L"Selection";
			this->LabelSelectionList->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ClearSelectionOnInstantiation
			// 
			this->ClearSelectionOnInstantiation->Location = System::Drawing::Point(692, 354);
			this->ClearSelectionOnInstantiation->Name = L"ClearSelectionOnInstantiation";
			this->ClearSelectionOnInstantiation->Size = System::Drawing::Size(350, 32);
			this->ClearSelectionOnInstantiation->TabIndex = 8;
			this->ClearSelectionOnInstantiation->Text = L"Clear Selection After Reference Instantiation";
			this->ClearSelectionOnInstantiation->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->ClearSelectionOnInstantiation->UseVisualStyleBackColor = true;
			// 
			// CustomPos
			// 
			this->CustomPos->Location = System::Drawing::Point(692, 284);
			this->CustomPos->Name = L"CustomPos";
			this->CustomPos->Size = System::Drawing::Size(131, 32);
			this->CustomPos->TabIndex = 9;
			this->CustomPos->Text = L"Use Custom Position";
			this->CustomPos->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->CustomPos->UseVisualStyleBackColor = true;
			// 
			// PositionX
			// 
			this->PositionX->Location = System::Drawing::Point(692, 325);
			this->PositionX->Name = L"PositionX";
			this->PositionX->Size = System::Drawing::Size(55, 20);
			this->PositionX->TabIndex = 10;
			// 
			// PositionZ
			// 
			this->PositionZ->Location = System::Drawing::Point(804, 325);
			this->PositionZ->Name = L"PositionZ";
			this->PositionZ->Size = System::Drawing::Size(55, 20);
			this->PositionZ->TabIndex = 11;
			// 
			// PositionY
			// 
			this->PositionY->Location = System::Drawing::Point(748, 325);
			this->PositionY->Name = L"PositionY";
			this->PositionY->Size = System::Drawing::Size(55, 20);
			this->PositionY->TabIndex = 12;
			// 
			// CustomRot
			// 
			this->CustomRot->Location = System::Drawing::Point(911, 284);
			this->CustomRot->Name = L"CustomRot";
			this->CustomRot->Size = System::Drawing::Size(131, 32);
			this->CustomRot->TabIndex = 13;
			this->CustomRot->Text = L"Use Custom Rotation";
			this->CustomRot->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->CustomRot->UseVisualStyleBackColor = true;
			// 
			// RotationY
			// 
			this->RotationY->Location = System::Drawing::Point(931, 325);
			this->RotationY->Name = L"RotationY";
			this->RotationY->Size = System::Drawing::Size(55, 20);
			this->RotationY->TabIndex = 16;
			// 
			// RotationZ
			// 
			this->RotationZ->Location = System::Drawing::Point(987, 325);
			this->RotationZ->Name = L"RotationZ";
			this->RotationZ->Size = System::Drawing::Size(55, 20);
			this->RotationZ->TabIndex = 15;
			// 
			// RotationX
			// 
			this->RotationX->Location = System::Drawing::Point(875, 325);
			this->RotationX->Name = L"RotationX";
			this->RotationX->Size = System::Drawing::Size(55, 20);
			this->RotationX->TabIndex = 14;
			// 
			// ShowSelectionControls
			// 
			this->ShowSelectionControls->BackColor = System::Drawing::SystemColors::Control;
			this->ShowSelectionControls->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ShowSelectionControls->ForeColor = System::Drawing::Color::Black;
			this->ShowSelectionControls->Location = System::Drawing::Point(639, 186);
			this->ShowSelectionControls->Name = L"ShowSelectionControls";
			this->ShowSelectionControls->Size = System::Drawing::Size(40, 63);
			this->ShowSelectionControls->TabIndex = 17;
			this->ShowSelectionControls->Text = L"� �";
			this->ShowSelectionControls->UseVisualStyleBackColor = false;
			// 
			// SaveTags
			// 
			this->SaveTags->BackColor = System::Drawing::SystemColors::Control;
			this->SaveTags->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->SaveTags->ForeColor = System::Drawing::Color::Black;
			this->SaveTags->Location = System::Drawing::Point(639, 363);
			this->SaveTags->Name = L"SaveTags";
			this->SaveTags->Size = System::Drawing::Size(40, 27);
			this->SaveTags->TabIndex = 19;
			this->SaveTags->Text = L"Save";
			this->SaveTags->UseVisualStyleBackColor = false;
			// 
			// LoadTags
			// 
			this->LoadTags->BackColor = System::Drawing::SystemColors::Control;
			this->LoadTags->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LoadTags->ForeColor = System::Drawing::Color::Black;
			this->LoadTags->Location = System::Drawing::Point(639, 392);
			this->LoadTags->Name = L"LoadTags";
			this->LoadTags->Size = System::Drawing::Size(40, 27);
			this->LoadTags->TabIndex = 20;
			this->LoadTags->Text = L"Load";
			this->LoadTags->UseVisualStyleBackColor = false;
			this->LoadTags->Click += gcnew System::EventHandler(this, &TagBrowser::button1_Click);
			// 
			// TagBrowser
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1054, 434);
			this->Controls->Add(this->LoadTags);
			this->Controls->Add(this->SaveTags);
			this->Controls->Add(this->ShowSelectionControls);
			this->Controls->Add(this->RotationY);
			this->Controls->Add(this->RotationZ);
			this->Controls->Add(this->RotationX);
			this->Controls->Add(this->CustomRot);
			this->Controls->Add(this->PositionY);
			this->Controls->Add(this->PositionZ);
			this->Controls->Add(this->PositionX);
			this->Controls->Add(this->CustomPos);
			this->Controls->Add(this->ClearSelectionOnInstantiation);
			this->Controls->Add(this->LabelSelectionList);
			this->Controls->Add(this->PlaceSelection);
			this->Controls->Add(this->AddObjectSelection);
			this->Controls->Add(this->TagTree);
			this->Controls->Add(this->SelectionList);
			this->Controls->Add(this->FormList);
			this->Controls->Add(this->SearchBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"TagBrowser";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Tag Browser";
			this->FormListContextMenu->ResumeLayout(false);
			this->SelectionListContextMenu->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TagTree))->EndInit();
			this->TagTreeContextMenu->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
};
}
