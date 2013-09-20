#include "Luncher.h"


using namespace System;
using namespace System ::Windows::Forms;

[STAThread]
void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Luncher::Luncher form;
	Application::Run(%form);
}