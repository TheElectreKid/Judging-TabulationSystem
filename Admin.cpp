//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Admin.h"
#include "Login.h"
#include "Category.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TAdminForm *AdminForm;
//---------------------------------------------------------------------------

__fastcall TAdminForm::TAdminForm(TComponent* Owner)
	: TForm(Owner)
{
	FDQuery1->Connection = LoginForm->FDConnection1;

    ListViewEvent->OnItemClick = ListViewEventItemClick;
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BtnLogoutClick(TObject *Sender)
{
	if (MessageDlg("Are you sure you want to log out?", TMsgDlgType::mtConfirmation,
	               TMsgDlgButtons() << TMsgDlgBtn::mbYes << TMsgDlgBtn::mbNo, 0) == mrYes)
	{
		LoginForm->Show();
		Application->MainForm = LoginForm;
		this->Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::TabsChange(TObject *Sender)
{
	if (Tabs->ActiveTab == TabEvent)
	{
		LoadEventsToListView();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::LoadEventsToListView()
{
    try
    {
        FDQuery1->Close();
        FDQuery1->SQL->Text = "SELECT EVENTID, EVENTNAME FROM EVENTS ORDER BY EVENTNAME";
        FDQuery1->Open();

        ListViewEvent->Items->Clear();

        while (!FDQuery1->Eof)
        {
            TListViewItem *item = ListViewEvent->Items->Add();
            item->Text = FDQuery1->FieldByName("EVENTNAME")->AsString;
            item->Tag = FDQuery1->FieldByName("EVENTID")->AsInteger;
            FDQuery1->Next();
        }
    }
    catch (Exception &e)
    {
        ShowMessage("Error loading events: " + e.Message);
    }
}

//---------------------------------------------------------------------------

void __fastcall TAdminForm::BtnRefreshClick(TObject *Sender)
{
	LoadEventsToListView();
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BtnAddEventClick(TObject *Sender)
{
    String newEventName = InputBox("Add Event", "Enter the event name:", "");

    if (newEventName.Trim().IsEmpty())
    {
        ShowMessage("Event name cannot be empty.");
        return;
    }

    try
    {
        FDQuery1->Close();
        FDQuery1->SQL->Text = "INSERT INTO EVENTS (EVENTNAME) VALUES (:eventname)";
        FDQuery1->ParamByName("eventname")->AsString = newEventName;
        FDQuery1->ExecSQL();

        ShowMessage("Event added successfully.");
        LoadEventsToListView();
    }
    catch (Exception &e)
    {
        ShowMessage("Error adding event: " + e.Message);
    }
}

//---------------------------------------------------------------------------

void __fastcall TAdminForm::BtnEditEventClick(TObject *Sender)
{
    if (ListViewEvent->Selected == nullptr)
    {
        ShowMessage("Please select an event to edit.");
        return;
    }

    TListViewItem *selectedItem = dynamic_cast<TListViewItem*>(ListViewEvent->Selected);
    if (!selectedItem)
    {
        ShowMessage("Invalid selection.");
        return;
    }

	int selectedEventID = selectedItem->Tag;
	String currentName = selectedItem->Text;

    String newEventName = InputBox("Edit Event", "Edit the event name:", currentName);

    if (newEventName.Trim().IsEmpty())
    {
        ShowMessage("Event name cannot be empty.");
        return;
    }

    try
    {
        FDQuery1->Close();
        FDQuery1->SQL->Text = "UPDATE EVENTS SET EVENTNAME = :eventname WHERE EVENTID = :eventid";
        FDQuery1->ParamByName("eventname")->AsString = newEventName;
        FDQuery1->ParamByName("eventid")->AsInteger = selectedEventID;
        FDQuery1->ExecSQL();

        ShowMessage("Event updated successfully.");

        if (Tabs->ActiveTab == TabEvent)
            LoadEventsToListView();
    }
    catch (Exception &e)
    {
        ShowMessage("Error updating event: " + e.Message);
    }
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BtnDeleteEventClick(TObject *Sender)
{
    TListViewItem *selectedItem = dynamic_cast<TListViewItem*>(ListViewEvent->Selected);

    if (!selectedItem)
    {
        ShowMessage("Please select an event to delete.");
        return;
    }

    int eventID = selectedItem->Tag;
    String eventName = selectedItem->Text;  // If this works for you, it's fine

    if (MessageDlg("Are you sure you want to delete the event: \"" + eventName + "\"?",
                   TMsgDlgType::mtConfirmation,
                   TMsgDlgButtons() << TMsgDlgBtn::mbYes << TMsgDlgBtn::mbNo,
                   0) == mrYes)
    {
        try
        {
            FDQuery1->Close();
            FDQuery1->SQL->Text = "DELETE FROM EVENTS WHERE EVENTID = :id";
            FDQuery1->ParamByName("id")->AsInteger = eventID;
            FDQuery1->ExecSQL();

            ShowMessage("Event deleted successfully.");
            LoadEventsToListView();
        }
        catch (Exception &e)
        {
            ShowMessage("Error deleting event: " + e.Message);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::ListViewEventItemClick(TObject * const Sender, TListViewItem * const Item)
{
    if (Item == nullptr)
        return;

    int selectedEventID = Item->Tag;

    // Use the existing CategoryForm instance
    CategoryForm->SetEventID(selectedEventID);

    // Show modally or non-modally as needed
    CategoryForm->ShowModal();  // or Show() if you prefer

    // No need to delete — it's managed by the app
}

