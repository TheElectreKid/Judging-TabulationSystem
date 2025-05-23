#ifndef CategoryH
#define CategoryH

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ListView.hpp>
#include <FMX.StdCtrls.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.Types.hpp>
#include <FireDAC.FMXUI.Wait.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.IB.hpp>
#include <FireDAC.Phys.IBDef.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>

class TCategoryForm : public TForm
{
__published:
    TListView *ListViewCategory;
    TButton *BtnAddCategory;
    TButton *BtnEditCategory;
    TButton *BtnDeleteCategory;
	TFDQuery *FDQuery1;
	TButton *BtnRefresh;
	TLabel *LabelEventTitle;

    void __fastcall BtnAddCategoryClick(TObject *Sender);
	void __fastcall BtnEditCategoryClick(TObject *Sender);
	void __fastcall BtnRefreshClick(TObject *Sender);
	void __fastcall BtnDeleteCategoryClick(TObject *Sender);

private:
    int currentEventID;

public:
	__fastcall TCategoryForm(TComponent* Owner);
	void __fastcall LoadCategoriesToListView(int eventID);
    void SetEventID(int eventID) ;
};

extern PACKAGE TCategoryForm *CategoryForm;

#endif

