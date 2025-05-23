//---------------------------------------------------------------------------

#ifndef AdminH
#define AdminH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.FMXUI.Wait.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.IB.hpp>
#include <FireDAC.Phys.IBDef.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
//---------------------------------------------------------------------------
class TAdminForm : public TForm
{
__published:	// IDE-managed Components
	TTabControl *Tabs;
	TToolBar *ToolBar1;
	TLabel *LabelTitle;
	TTabItem *TabAbout;
	TTabItem *TabEvent;
	TTabItem *TabUsers;
	TTabItem *TabLogs;
	TTabItem *TabSettings;
	TButton *BtnLogout;
	TLabel *LabelSoftwareName;
	TLabel *LabelVersion;
	TLabel *LabelDevName;
	TListView *ListViewEvent;
	TButton *BtnAddEvent;
	TButton *BtnDeleteEvent;
	TButton *BtnEditEvent;
	TFDQuery *FDQuery1;
	TButton *BtnRefresh;
	void __fastcall BtnLogoutClick(TObject *Sender);
	void __fastcall TabsChange(TObject *Sender);
	void __fastcall BtnRefreshClick(TObject *Sender);
	void __fastcall BtnAddEventClick(TObject *Sender);
	void __fastcall BtnEditEventClick(TObject *Sender);
	void __fastcall BtnDeleteEventClick(TObject *Sender);
	void __fastcall ListViewEventItemClick(TObject * const Sender, TListViewItem * const Item);

private:	// User declarations
	void __fastcall LoadEventsToListView();
public:		// User declarations
	__fastcall TAdminForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAdminForm *AdminForm;
//---------------------------------------------------------------------------
#endif
