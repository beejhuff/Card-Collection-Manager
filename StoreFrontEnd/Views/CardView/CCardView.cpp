#include "CCardView.h"
#include "VCardView.h"

CCardView::CCardView( VCardView* apView )
   : m_pView(apView)
{
  
}

CCardView::~CCardView()
{

}

void 
CCardView::SetModel( CardInterface* apModel )
{
   m_pModel = apModel;
   m_pView->ViewCard( apModel );
}