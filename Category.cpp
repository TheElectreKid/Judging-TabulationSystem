//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Category.h"
#include "Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TCategoryForm *CategoryForm;
//---------------------------------------------------------------------------
__fastcall TCategoryForm::TCategoryForm(TComponent* Owner)
	: TForm(Owner)
{

	FDQuery1->Connection = LoginForm->FDConnection1;
}
//---------------------------------------------------------------------------
void __fastcall TCategoryForm::SetEventID(int eventID)
{
    currentEventID = eventID;

    try
    {
        // Query event name by eventID
        FDQuery1->Close();
        FDQuery1->SQL->Text = "SELECT EVENTNAME FROM EVENTS WHERE EVENTID = :eid";
        FDQuery1->ParamByName("eid")->AsInteger = eventID;
        FDQuery1->Open();

        if (!FDQuery1->Eof)
        {
            // Set the label caption to the event name
            LabelEventTitle->Text = "Event: " + FDQuery1->FieldByName("EVENTNAME")->AsString;
        }
        else
        {
            LabelEventTitle->Text = "Event: (Unknown)";
        }
    }
    catch (Exception &e)
    {
        ShowMessage("Error loading event title: " + e.Message);
        LabelEventTitle->Text = "Event: (Error)";
    }

    // Load categories for the event
    LoadCategoriesToListView(eventID);
}


//---------------------------------------------------------------------------

void __fastcall TCategoryForm::LoadCategoriesToListView(int eventID)
{
    try
    {
		FDQuery1->Close();
		FDQuery1->SQL->Text = "SELECT CATEGORYID, CATEGORYNAME FROM CATEGORIES WHERE EVENTID = :eid ORDER BY CATEGORYNAME";
		FDQuery1->ParamByName("eid")->AsInteger = eventID;
		FDQuery1->Open();

		ListViewCategory->Items->Clear();

		while (!FDQuery1->Eof)
        {
			TListViewItem *item = ListViewCategory->Items->Add();
			item->Text = FDQuery1->FieldByName("CATEGORYNAME")->AsString;
			item->Tag = FDQuery1->FieldByName("CATEGORYID")->AsInteger;
			FDQuery1->Next();
        }
    }
    catch (Exception &e)
    {
        ShowMessage("Error loading categories: " + e.Message);
    }
}

//----------------------------------------------------------------------------

void __fastcall TCategoryForm::BtnAddCategoryClick(System::TObject* Sender)
{
    // Show input box to get new category name
    String newCategoryName = InputBox("Add Category", "Enter the category name:", "");

    // Validate input
    if (newCategoryName.Trim().IsEmpty())
    {
        ShowMessage("Category name cannot be empty.");
        return;
    }

    try
    {
		FDQuery1->Close();
        FDQuery1->SQL->Text =
			"INSERT INTO CATEGORIES (CATEGORYNAME, EVENTID) VALUES (:catname, :eventID)";
		FDQuery1->ParamByName("catname")->AsString = newCategoryName;
		FDQuery1->ParamByName("eventID")->AsInteger = currentEventID; // Use the event ID passed/set earlier
        FDQuery1->ExecSQL();

        ShowMessage("Category added successfully.");

        // Reload the categories list to show the new one
		LoadCategoriesToListView(currentEventID);
    }
    catch (Exception &e)
    {
        ShowMessage("Error adding category: " + e.Message);
    }
}

//----------------------------------------------------------------------------
void __fastcall TCategoryForm::BtnEditCategoryClick(System::TObject* Sender)
{
	// Your code here
}

//---------------------------------------------------------------------------
void __fastcall TCategoryForm::BtnRefreshClick(TObject *Sender)
{
    LoadCategoriesToListView(currentEventID);
}
//---------------------------------------------------------------------------
void __fastcall TCategoryForm::BtnDeleteCategoryClick(TObject *Sender)
{
    // Check if an item is selected in the ListView
    if (ListViewCategory->Selected == nullptr)
    {
        ShowMessage("Please select a category to delete.");
        return;
    }

    // Confirm deletion with the user
	if (MessageDlg("Are you sure you want to delete the selected category?",
				   TMsgDlgType::mtConfirmation,
				   TMsgDlgButtons() << TMsgDlgBtn::mbYes << TMsgDlgBtn::mbNo, 0) != mrYes)
	{
		return; // User cancelled deletion
	}

    try
    {
        int categoryIDToDelete = ListViewCategory->Selected->Tag;

        FDQuery1->Close();
        FDQuery1->SQL->Text = "DELETE FROM CATEGORIES WHERE CATEGORYID = :catid";
        FDQuery1->ParamByName("catid")->AsInteger = categoryIDToDelete;
        FDQuery1->ExecSQL();

        ShowMessage("Category deleted successfully.");

        // Reload the list after deletion
        LoadCategoriesToListView(currentEventID);
    }
    catch (Exception &e)
    {
        ShowMessage("Error deleting category: " + e.Message);
    }
}
//---------------------------------------------------------------------------

