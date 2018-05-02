#pragma once

class VCardView;
class CardInterface;

class CCardView
{
public:
   CCardView( VCardView* apView, CardInterface* apModel );
   ~CCardView();

   void SetModel( CardInterface* apModel );

private:
   VCardView* m_pView;
   CardInterface* m_pModel;
};