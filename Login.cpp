//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Login.h"
#include "Admin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TLoginForm *LoginForm;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLoginForm::BtnLoginClick(TObject *Sender)
{
	try
    {
		FDQuery1->Close();
		FDQuery1->SQL->Clear();
		FDQuery1->SQL->Add("SELECT USERPASS, USERTYPE FROM USERS WHERE USERNAME = :username");
		FDQuery1->ParamByName("username")->AsString = EditUsername->Text;
		FDQuery1->Open();

        if (!FDQuery1->Eof)
        {
			String storedPass = FDQuery1->FieldByName("USERPASS")->AsString;
			String userType = FDQuery1->FieldByName("USERTYPE")->AsString;

			if (storedPass == EditPassword->Text)  // Replace with hash check in real app
			{
                if (userType == "admin")
                {

					AdminForm->Show();
					Application->MainForm = AdminForm;
                    this->Hide();
                }
                else
                {
                    LabelMessage->Text = "Access denied: Not an admin.";
                }
            }
            else
            {
                LabelMessage->Text = "Incorrect password.";
            }
        }
        else
        {
            LabelMessage->Text = "Username not found.";
        }
    }
    catch (Exception &e)
    {
        LabelMessage->Text = "Database error: " + e.Message;
    }
}

//---------------------------------------------------------------------------
