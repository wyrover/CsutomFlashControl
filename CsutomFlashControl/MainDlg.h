// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "FlashControl.h"
#include <atltypes.h>
#include <string>
#include <atlstr.h>


class CMainDlg : public CAxDialogImpl<CMainDlg>
{
private:
    CFlashControl    m_FlashCtrl;
public:
    enum { IDD = IDD_MAINDLG };
    
    BEGIN_MSG_MAP( CMainDlg )
    MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
    COMMAND_ID_HANDLER( ID_APP_ABOUT, OnAppAbout )
    COMMAND_ID_HANDLER( IDOK, OnOK )
    COMMAND_ID_HANDLER( IDCANCEL, OnCancel )
    END_MSG_MAP()
    
    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
    
    LRESULT OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
    {
        // center the dialog on the screen
        CenterWindow();
        
        // set icons
        HICON hIcon = AtlLoadIconImage( IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics( SM_CXICON ), ::GetSystemMetrics( SM_CYICON ) );
        SetIcon( hIcon, TRUE );
        HICON hIconSmall = AtlLoadIconImage( IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics( SM_CXSMICON ), ::GetSystemMetrics( SM_CYSMICON ) );
        SetIcon( hIconSmall, FALSE );
        
        CRect rcClient;
        GetClientRect( &rcClient );
        
        if ( m_FlashCtrl.Create( m_hWnd, rcClient ) )
        {
            TCHAR sCurDir[MAX_PATH] = {0};
            GetCurrentDirectory( MAX_PATH, sCurDir );
            CString strCurDir = sCurDir;
            strCurDir.Append( _T( "\\Test.swf" ) );
            ATLASSERT( ::PathFileExists( strCurDir ) );
            if ( m_FlashCtrl.LoadFlash( strCurDir.GetBuffer() ) )
            {
                m_FlashCtrl.Start();
            }
        }
        
        return TRUE;
    }
    
    LRESULT OnAppAbout( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
    {
        m_FlashCtrl.Rewind();
        CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
        dlg.DoModal();
        return 0;
    }
    
    LRESULT OnOK( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
    {
        // TODO: Add validation code
        EndDialog( wID );
        return 0;
    }
    
    LRESULT OnCancel( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
    {
        m_FlashCtrl.Destroy();
        EndDialog( wID );
        return 0;
    }
};
