#include "tinyxml.h"
#include "tinystr.h"
#include <cliext/utility>
#include <cliext/vector>
#pragma once


namespace Luncher {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace cliext;
	using namespace System::Diagnostics;
	/// <summary>
	/// Summary for Luncher
	/// </summary>
	public ref class Luncher : public System::Windows::Forms::Form
	{
	public:
		Luncher(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			TiXmlDocument doc;

			doc.LoadFile("Resource/Maps/Maps.svg");

			TiXmlElement* root = doc.FirstChildElement()->FirstChildElement();

			while (root)
			{
				if(root->ValueTStr() == "g"){
					String^ mapName = gcnew String(root->Attribute("id"));					
					comboBox1->Items->Add(mapName);

				}

				root = root->NextSiblingElement();
			}

			comboBox1->SelectedIndex = 0;

			m_ImageList.push_back(make_pair(gcnew String("Art"),gcnew String("Resource/Maps/textures/artText.gif")));
			m_ImageList.push_back(make_pair(gcnew String("Beach"),gcnew String("Resource/Maps/textures/beachText.gif")));
			m_ImageList.push_back(make_pair(gcnew String("Farm"),gcnew String("Resource/Maps/textures/farmText.gif")));
			m_ImageList.push_back(make_pair(gcnew String( "Manhattan"),gcnew String("Resource/Maps/textures/manhatenText.gif")));

			for (int i = 0; i < m_ImageList.size(); i++)
			{
				comboBox2->Items->Add(m_ImageList[i].first);
			}

			comboBox2->SelectedIndex = 0;
			//
			//panel1->BackgroundImage = Image::FromFile("Resource/Maps/textures/artText.gif");
		}

	private:


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Luncher()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: vector<pair<String^,String^> > m_ImageList;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Diagnostics::Process^  process1;
	private: System::DirectoryServices::DirectoryEntry^  directoryEntry1;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::LinkLabel^  linkLabel2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::LinkLabel^  linkLabel5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::LinkLabel^  linkLabel4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::LinkLabel^  linkLabel3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->linkLabel5 = (gcnew System::Windows::Forms::LinkLabel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->linkLabel4 = (gcnew System::Windows::Forms::LinkLabel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->linkLabel3 = (gcnew System::Windows::Forms::LinkLabel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->linkLabel2 = (gcnew System::Windows::Forms::LinkLabel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->process1 = (gcnew System::Diagnostics::Process());
			this->directoryEntry1 = (gcnew System::DirectoryServices::DirectoryEntry());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(286, 281);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(125, 48);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start game";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Luncher::button1_Click);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(19, 19);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(79, 20);
			this->numericUpDown1->TabIndex = 1;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->numericUpDown1);
			this->groupBox1->Location = System::Drawing::Point(286, 16);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(125, 52);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Number Of Players";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Luncher::groupBox1_Enter);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->comboBox1);
			this->groupBox2->Location = System::Drawing::Point(12, 19);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(256, 52);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Maps";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(4, 19);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(246, 21);
			this->comboBox1->TabIndex = 0;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(425, 361);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->groupBox6);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(417, 335);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Start Game";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->groupBox5);
			this->groupBox6->Controls->Add(this->groupBox2);
			this->groupBox6->Location = System::Drawing::Point(6, 16);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(274, 313);
			this->groupBox6->TabIndex = 7;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Map Settings";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->comboBox2);
			this->groupBox5->Controls->Add(this->panel1);
			this->groupBox5->Location = System::Drawing::Point(8, 79);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(260, 228);
			this->groupBox5->TabIndex = 6;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Map Texture";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(4, 21);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(250, 21);
			this->comboBox2->TabIndex = 5;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Luncher::comboBox2_SelectedIndexChanged);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(4, 48);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(250, 173);
			this->panel1->TabIndex = 4;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->richTextBox1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(417, 335);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Controls";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox4);
			this->tabPage3->Controls->Add(this->groupBox3);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(417, 335);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"About";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->linkLabel5);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Controls->Add(this->linkLabel4);
			this->groupBox4->Controls->Add(this->label5);
			this->groupBox4->Controls->Add(this->linkLabel3);
			this->groupBox4->Controls->Add(this->label4);
			this->groupBox4->Controls->Add(this->linkLabel2);
			this->groupBox4->Controls->Add(this->label3);
			this->groupBox4->Controls->Add(this->label2);
			this->groupBox4->Controls->Add(this->linkLabel1);
			this->groupBox4->Location = System::Drawing::Point(6, 54);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(338, 154);
			this->groupBox4->TabIndex = 1;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Tools used for development";
			// 
			// linkLabel5
			// 
			this->linkLabel5->AutoSize = true;
			this->linkLabel5->Location = System::Drawing::Point(151, 125);
			this->linkLabel5->Name = L"linkLabel5";
			this->linkLabel5->Size = System::Drawing::Size(34, 13);
			this->linkLabel5->TabIndex = 9;
			this->linkLabel5->TabStop = true;
			this->linkLabel5->Text = L"Spine";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(9, 125);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(97, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Skeletal Animation:";
			// 
			// linkLabel4
			// 
			this->linkLabel4->AutoSize = true;
			this->linkLabel4->Location = System::Drawing::Point(151, 98);
			this->linkLabel4->Name = L"linkLabel4";
			this->linkLabel4->Size = System::Drawing::Size(49, 13);
			this->linkLabel4->TabIndex = 7;
			this->linkLabel4->TabStop = true;
			this->linkLabel4->Text = L"TinyXML";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 98);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 13);
			this->label5->TabIndex = 6;
			this->label5->Text = L"XML Parser:";
			// 
			// linkLabel3
			// 
			this->linkLabel3->AutoSize = true;
			this->linkLabel3->Location = System::Drawing::Point(151, 71);
			this->linkLabel3->Name = L"linkLabel3";
			this->linkLabel3->Size = System::Drawing::Size(53, 13);
			this->linkLabel3->TabIndex = 5;
			this->linkLabel3->TabStop = true;
			this->linkLabel3->Text = L"ClipperLib";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 71);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(88, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Polygon Clipping:";
			// 
			// linkLabel2
			// 
			this->linkLabel2->AutoSize = true;
			this->linkLabel2->Location = System::Drawing::Point(151, 45);
			this->linkLabel2->Name = L"linkLabel2";
			this->linkLabel2->Size = System::Drawing::Size(45, 13);
			this->linkLabel2->TabIndex = 3;
			this->linkLabel2->TabStop = true;
			this->linkLabel2->Text = L"Poly2Tri";
			this->linkLabel2->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Luncher::linkLabel2_LinkClicked);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 45);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(112, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Polygon Triangulation:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Physics Engien:";
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(151, 20);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(39, 13);
			this->linkLabel1->TabIndex = 0;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"Box2D";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Luncher::linkLabel1_LinkClicked);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label1);
			this->groupBox3->Location = System::Drawing::Point(6, 6);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(190, 42);
			this->groupBox3->TabIndex = 0;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Team";
			this->groupBox3->Enter += gcnew System::EventHandler(this, &Luncher::groupBox3_Enter);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(177, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Lead Developer: Leon Rosengarten";
			// 
			// process1
			// 
			this->process1->StartInfo->Domain = L"";
			this->process1->StartInfo->LoadUserProfile = false;
			this->process1->StartInfo->Password = nullptr;
			this->process1->StartInfo->StandardErrorEncoding = nullptr;
			this->process1->StartInfo->StandardOutputEncoding = nullptr;
			this->process1->StartInfo->UserName = L"";
			this->process1->SynchronizingObject = this;
			this->process1->Exited += gcnew System::EventHandler(this, &Luncher::process1_Exited);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Enabled = false;
			this->richTextBox1->Location = System::Drawing::Point(6, 6);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(123, 103);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"Move Left: Left\nMove Right: Right\nJump: LShift\nAim Up: Up\nAim Down: Down\nMove scr" 
				L"ee: W A S D\nZoom in/out: Q Z";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &Luncher::richTextBox1_TextChanged);
			// 
			// Luncher
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(449, 385);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Luncher";
			this->Text = L"Luncher";
			this->Load += gcnew System::EventHandler(this, &Luncher::Luncher_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion



	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 String^ args = numericUpDown1->Value.ToString();

				 args += " " + comboBox1->SelectedItem->ToString();

				 args += " " + m_ImageList[this->comboBox2->SelectedIndex].second->ToString();

				 this->process1->Start("Worms.exe",args);
				 // Process::Start("Worms.exe",args);

			 }
	private: System::Void Luncher_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void process1_Exited(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void groupBox3_Enter(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("http://www.box2d.org");

			 }
	private: System::Void linkLabel2_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("https://code.google.com/p/poly2tri");

			 }
	private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 panel1->BackgroundImage = Image::FromFile(m_ImageList[this->comboBox2->SelectedIndex].second);
			 }

private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
