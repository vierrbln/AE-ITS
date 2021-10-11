#include <userint.h>
#include "AE.h"
#include "definitions.h"

void CVICALLBACK SetPhyIni( int menuBar, int menuItem, void *callbackData, int panel )
{
   int iSelectionStatus;
   //User have to select a file
   iSelectionStatus = FileSelectPopup( "", "*.ini", "ini", "Please select a physical.ini file", VAL_LOAD_BUTTON, 0, 1, 1, 0, gcPhysicalIniFileName );
   if ( iSelectionStatus == 1 )
   {
      //Improves the performance of reset all gui resources
      if ( HIDEPANEL )
      {
         HidePanel( giMainPanelHandle );
      }
      if ( DIMMEDTABLE )
      {
         SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, TRUE );
      }
      ProcessDrawEvents();
      iLoadDefaultDataIntoTable();
      iSaveAppEditIniFile();
      if ( HIDEPANEL )
      {
         DisplayPanel( giMainPanelHandle );
      }
   }
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK OpenAppIni( int menuBar, int menuItem, void *callbackData, int panel )
{
   int iSelectionStatus;
   int iStatus;
   int iRestartGUI;
   char cTextBuffer[1024];
   char cLW[10];
   char cDirectory[1024];
   char cFileName[1024];
   char cTempDir[1024]; 
   
   SplitPath (gcLastUsedAppIniFileName, cLW, cDirectory, cFileName);
   sprintf(cTempDir, "%s%s", cLW, cDirectory);
   
   iRestartGUI = iCheckVariableBeforeClosing();
   if ( iRestartGUI )
   {
      return ;
   }
   //User have sele a file
   iSelectionStatus = FileSelectPopup( cTempDir, "*.ini", "ini", "Please select a application.ini file", VAL_LOAD_BUTTON, 0, 1, 1, 0, gcAppIniFileName );
   if ( iSelectionStatus == 1 )
   {
      iOpenApplicationIniFile();
   }
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK SaveAppIni( int menuBar, int menuItem, void *callbackData, int panel )
{
   iSaveAppIni( gcAppIniFileName );
   iResetAllResources( APP_INI_SAVED );
   giTableDataModified = FALSE;
   giTableDataChecked = FALSE;
   giFreeTextDataModified = FALSE;
   giChannelTableHasAnError = FALSE;
   giAppIniChanged = FALSE;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK Exit( int menuBar, int menuItem, void *callbackData, int panel )
{
   QuitUserInterface( 0 );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK OpenOnlineHelp( int menuBar, int menuItem, void *callbackData, int panel )
{
   MessagePopup( C_TITLE_MSG_POPUP, "Help comes later. Sorry, it's a beta version!\n\n""A short description:\n"
      "Set and load a physical.ini. This tool supports TS-PSAM, TS-PAM, TS-PSU, TS-PMB, TS-PSM1, TS-PSM2, TS-PDFT\n"
      "and TS-PIO3B. Edit the application.ini over the table view to set all logical channel names for the analog and\n""digital modules.\n\n"
      "Change to free text view and edit all settings that are not corresponding to analog and digital channels.\n\n"
      "Change ApplicationEditor.ini to show all modules or only application modules (TS-PMB...)." );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK ShowSplash( int menuBar, int menuItem, void *callbackData, int panel )
{
   char cTextMessage[1024];
   sprintf( cTextMessage, "AE-ITS ApplicationEditor - Version %s ", VERSION );
   SetCtrlVal( gSplash, SPLASH_SELECTEDSEQ, cTextMessage );
   SetCtrlAttribute( gSplash, SPLASH_SELECTEDSEQ, ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT );
   SetCtrlAttribute( gSplash, SPLASH_LABEL, ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT );
   SetCtrlAttribute( gSplash, SPLASH_PRODUCT, ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT );
   DisplayPanel( gSplash );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK CheckTable( int menuBar, int menuItem, void *callbackData, int panel )
{
   iCheckBenchItems( CHANGED, FALSE );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK ShowErrorList( int menuBar, int menuItem, void *callbackData, int panel )
{
   ResetTextBox( giErrorPanel, ERRORS_TEXTBOX, gcErrorBuffer );
   DisplayPanel( giErrorPanel );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK ApplyChanges( int menuBar, int menuItem, void *callbackData, int panel )
{
   iApplyChanges();
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK SetDefaultCellValue( int menuBar, int menuItem, void*callbackData, int panel )
{
   Point CellPoint;
   GetActiveTableCell( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  &CellPoint );
   iResetCellValue( CellPoint.x, CellPoint.y, DEFAULT_RESET );
   if ( !giTableDataModified )
   {
      iResetAllResources( TABLE_DATA_MODIFIED );
      giTableDataModified = TRUE;
   }
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK SetOriginalCellValue( int menuBar, int menuItem, void*callbackData, int panel )
{
   Point CellPoint;
   GetActiveTableCell( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  &CellPoint );
   iResetCellValue( CellPoint.x, CellPoint.y, ORIGINAL );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK SetAllDefaultCellValues( int menuBar, int menuItem, void*callbackData, int panel )
{
   int iConfirm;
   iConfirm = ConfirmPopup( C_TITLE_MSG_POPUP, "Do you want reset all cells to their default cell values? All entries in application.ini will be deleted!" );
   if ( !iConfirm )
   {
      return ;
   }
   if ( HIDEPANEL )
   {
      HidePanel( giMainPanelHandle );
   }
   if ( DIMMEDTABLE )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, TRUE );
   }
   iResetAppChannelTable( DEFAULT_RESET );
   if ( !giTableDataModified )
   {
      iResetAllResources( TABLE_DATA_MODIFIED );
      giTableDataModified = TRUE;
   }
   if ( DIMMEDTABLE )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, FALSE );
   }
   if ( HIDEPANEL )
   {
      DisplayPanel( giMainPanelHandle );
   }
   SetCtrlVal( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, "Reset all cell values to default value complete" );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK SetAllOriginalCellValues( int menuBar, int menuItem, void*callbackData, int panel )
{
   int iConfirm;
   if ( giTableDataModified )
   {
      iConfirm = ConfirmPopup( C_TITLE_MSG_POPUP, "Do you want reset all cells to their original cell values?" );
      if ( !iConfirm )
      {
         return ;
      }
   }
   else
   {
      return ;
   }
   if ( HIDEPANEL )
   {
      HidePanel( giMainPanelHandle );
   }
   if ( DIMMEDTABLE )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, TRUE );
   }
   iResetAppChannelTable( ORIGINAL );
   if ( giTableDataModified )
   {
      iResetAllResources( TABLE_DATA_RESET );
      giTableDataModified = FALSE;
   }
   if ( DIMMEDTABLE )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, FALSE );
   }
   if ( HIDEPANEL )
   {
      DisplayPanel( giMainPanelHandle );
   }
   SetCtrlVal( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, "Reset all cell values to original value complete" );
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK ApplyChangesText( int menuBar, int menuItem, void *callbackData, int panel )
{
   if ( !giCorrectLicenseFound )
   {
      MessagePopup( C_TITLE_MSG_POPUP, "This software works in demo mode. You cannot apply changes to your application.ini" );
   }
   else
   {
      iSaveFreeText();
   }
   iResetAllResources( FREE_TEXT_RESET );
   giFreeTextDataModified = FALSE;
   giAppIniChanged = TRUE;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK SaveAppIniAs( int menuBar, int menuItem, void *callbackData, int panel )
{
   int iSelectionStatus;
   char cTextBuffer[1024];
   iSelectionStatus = FileSelectPopup( "", "*.ini", "ini", "Please select a application.ini file", VAL_SAVE_BUTTON, 0, 1, 1, 1, gcAppIniFileName );
   if ( iSelectionStatus > 0 )
   {
      iSaveAppIni( gcAppIniFileName );
      sprintf( cTextBuffer, "Selected application.ini: %s", gcAppIniFileName );
      SetCtrlVal( giMainPanelHandle, MAINPANEL_INF_APPINI, cTextBuffer );
	  giTableDataModified = FALSE;
	   giTableDataChecked = FALSE;
	   giFreeTextDataModified = FALSE;
	   giChannelTableHasAnError = FALSE;
	   giAppIniChanged = FALSE;
      giAppIniChanged = FALSE;
   }
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
void CVICALLBACK CloseAppIni( int menuBar, int menuItem, void *callbackData, int panel )
{
   int iRestartGUI;
   iRestartGUI = iCheckVariableBeforeClosing();
   if ( iRestartGUI )
   {
      return ;
   }
   
}
void CVICALLBACK ShowRegistorPanel( int menuBar, int menuItem, void *callbackData, int panel )
{
   InstallPopup( giRegistrationPanel );
}


void CVICALLBACK ShowLegend (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	DisplayPanel(giLegendPanel);
}

void CVICALLBACK DublicateBench (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	
	InstallPopup (giDubPanelHandle);	
}


