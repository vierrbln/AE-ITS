#include <userint.h>
#include "AE.h"
#include "definitions.h"

int CVICALLBACK SelectBench( int panel, int control, int event, void*callbackData, int eventData1, int eventData2 )
{
   int iConfirm;
   int iError;
   switch ( event )
   {
      case EVENT_VAL_CHANGED:
         if ( giTableDataModified )
         {
            iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "You have changed the values for the logical names. Would you apply the changes?", "Yes", "No", "Cancel", NULL, 0, 0,
               VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
            //User clicked "YES"
            if ( iConfirm == 1 )
            {
               iError = iCheckBenchItems( CHANGED, TRUE );
               if ( iError )
               {
                  SetCtrlVal( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, gcSelectedBench );
                  return 0;
               }
               //User clicked "No"
            }
            else if ( iConfirm == 2 )
            {
               //Do nothing
               Delay( 0.1 );
               //User clicked "Cancel"
            }
            else if ( iConfirm == 3 )
            {
               SetCtrlVal( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, gcSelectedBench );
               return 0;
            }
            iResetAllResources( TABLE_DATA_RESET );
         }
         iResetAllResources( APP_LOADED );
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
         GetCtrlVal( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, gcSelectedBench );
         iResetAppChannelTable( RESET );
         iLoadBenchDataIntoTable();
         giTableDataModified = FALSE;
         if ( DIMMEDTABLE )
         {
            SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, FALSE );
         }
         if ( HIDEPANEL )
         {
            DisplayPanel( giMainPanelHandle );
         }
         break;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int CVICALLBACK ModulTreeCallBack( int panel, int control, int event, void*callbackData, int eventData1, int eventData2 )
{
   int iActiveModuleIndex;
   switch ( event )
   {
      case EVENT_LEFT_DOUBLE_CLICK:
         GetCtrlVal( giTabPanelHandleLogicalNames, LOGICAL_MODULES,  &iActiveModuleIndex );
         SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_HSCROLL_OFFSET, ( iActiveModuleIndex *300 ) - 300 );
         break;
      case EVENT_LEFT_CLICK:
         SetCtrlVal( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, "Make a double click on a module for jumping table view to this module." );
         break;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int CVICALLBACK TableCallBack( int panel, int control, int event, void*callbackData, int eventData1, int eventData2 )
{
   int iIsDefault;
   Point CellPoint;
   int iCellMode;
   char cDefaultCellValue[85];
   char cOriginalCellValue[85];
   char cActualCellValue[85];
   char ColumLabelText[85];
   char cTextBuffer[1024];
   switch ( event )
   {
      case EVENT_VAL_CHANGED:
         GetActiveTableCell( panel, control, &CellPoint );
         GetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, CellPoint, ATTR_CTRL_VAL, cActualCellValue );
         iSetCellValues( CellPoint.x, CellPoint.y, cActualCellValue );
         if ( !giTableDataModified )
         {
            iResetAllResources( TABLE_DATA_MODIFIED );
            giTableDataModified = TRUE;
         }
         break;
      case EVENT_ACTIVE_CELL_CHANGE:
         GetActiveTableCell( panel, control, &CellPoint );
         iGetCellValues( CellPoint.x, CellPoint.y, cDefaultCellValue, cOriginalCellValue, &iIsDefault );
         GetTableCellAttribute( panel, control, CellPoint, ATTR_CELL_MODE, &iCellMode );
         GetTableColumnAttribute( panel, control, CellPoint.x, ATTR_LABEL_TEXT, ColumLabelText );
         if ( iCellMode == VAL_INDICATOR )
         {
            sprintf( cTextBuffer, "You cannot edit this cell value." );
         }
         else
         {
            if ( giAppIniDataLoaded && strlen( cOriginalCellValue ))
            {
               sprintf( cTextBuffer, "Press F2 to edit the selected cell. (Original name: %s | Default name: %s | Device: %s%i)", cOriginalCellValue, cDefaultCellValue, ColumLabelText, CellPoint.y );
            }
            else if ( giAppIniDataLoaded && !strlen( cOriginalCellValue ))
            {
               sprintf( cTextBuffer, "Press F2 to edit the selected cell. (Original name: - | Default name: %s | Device: %s%i)", cDefaultCellValue, ColumLabelText, CellPoint.y );
            }
            else
            {
               sprintf( cTextBuffer, "Press F2 to edit the selected cell." );
            }
         }
         SetCtrlVal( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, cTextBuffer );
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int CVICALLBACK FreeTextBoxCallback( int panel, int control, int event, void*callbackData, int eventData1, int eventData2 )
{
   char cTextBuffer[1024];
   switch ( event )
   {
      case EVENT_VAL_CHANGED:
         if ( giFreeTextDataModified == FALSE )
         {
            iResetAllResources( FREE_TEXT_MODIFIED );
            giFreeTextDataModified = TRUE;
         }
         break;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int CVICALLBACK MainTabCallBack( int panel, int control, int event, void*callbackData, int eventData1, int eventData2 )
{
   int iConfirm;
   int iSelectedTab;
   int iError;
   switch ( event )
   {
      case EVENT_ACTIVE_TAB_CHANGE:
         if ( !giAppIniDataLoaded )
         {
            return 0;
         }
         GetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, &iSelectedTab );
         if (( iSelectedTab == 1 ) && giAppIniDataLoaded )
         {
            if ( giTableDataModified )
      {
         iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "You have changed the values for the logical names. Would you apply the changes?", "Yes", "No", "Cancel", NULL, 0,
            0, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
         //User clicked "YES"
         if ( iConfirm == 1 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "table data is modified and user clicked yes" );
            }
            iError = iCheckBenchItems( CHANGED, TRUE );
            if ( iError )
            {
               SetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, 0 ); 
               return 0;
            }
            if ( giTracingEnabled )
            {
               WriteToLogFile( "copy temp file" );
            }
            //User clicked "No"
         }
         else if ( iConfirm == 2 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "table data is modified and user clicked no" );
            }
            //Do nothing
            iResetAllResources( TABLE_DATA_APPLIED );
            Delay( 0.1 );
            //User clicked "Cancel"
         }
         else if ( iConfirm == 3 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "table data is modified and user clicked cancel" );
            }
            SetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, 0 );
                  return 0;
         }
      }
	  else if ( giChannelTableHasAnError )
   {
      iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "The channel table have min. one error and the changes could not applied. Would you correct the entries?", "Yes", "No (loose changes)", 0, NULL, 0, 0,
         VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1 );
      //User clicked "YES"
      if ( iConfirm == 1 )
      {
         if ( giTracingEnabled )
         {
            WriteToLogFile( "channel table has an error and user clicked yes" );
         }
		 SetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, 0 );
                  return 0;
         //User clicked "No"
      }
      else if ( iConfirm == 2 )
      {
         //Do nothing
         if ( giTracingEnabled )
         {
            WriteToLogFile( "channel table has an error and user clicked no" );
         }
         Delay( 0.1 );
         if (giTableDataModified) iResetAllResources (TABLE_DATA_APPLIED);
         //User clicked "No"
      }
   }
    
      else if ( giTableDataChecked )
      {
         iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "The content of your application.ini was checked but not applied. Would you apply the changes now?", "Yes", "No", "Cancel",
            NULL, 0, 0, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
         //User clicked "YES"
         if ( iConfirm == 1 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "table data is checked and user clicked yes" );
            }
            iApplyChanges();
            if ( giTracingEnabled )
            {
               WriteToLogFile( "copy temp file" );
            }
            //User clicked "No"
         }
         else if ( iConfirm == 2 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "table data is checked and user clicked no" );
            }
            //Do nothing
            iResetAllResources( TABLE_DATA_APPLIED );
            Delay( 0.1 );
            //User clicked "Cancel"
         }
         else if ( iConfirm == 3 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "table data is checked and user clicked cancel" );
            }
           SetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, 0 );
                  return 0;
         }
      }
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
            ResetTextBox( giTabPanelHandleFreeText, FREETEXT_FREETEXT, "" );
            giTableDataModified = FALSE;
            iLoadFreeText();
            SetCtrlAttribute( giTabPanelHandleFreeText, FREETEXT_FREETEXT, ATTR_DIMMED, FALSE );
            SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 1 );
            SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 0 );
            if ( HIDEPANEL )
            {
               DisplayPanel( giMainPanelHandle );
            }
         }
         else
         {
            if ( giFreeTextDataModified )
            {
               iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "You have changed the text of your application.ini. Would you apply the changes?", "Yes", "No", "Cancel", NULL, 0, 0,
                  VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
               //User clicked "YES"
               if ( iConfirm == 1 )
               {
                  iSaveFreeText();
                  iResetAllResources( FREE_TEXT_RESET );
                  giFreeTextDataModified = FALSE;
                  //User clicked "Cancel"
               }
               else if ( iConfirm == 3 )
               {
                  SetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, 0 );
                  return 0;
               }
            }
            SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 0 );
            SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
            if ( HIDEPANEL )
            {
               HidePanel( giMainPanelHandle );
            }
            ProcessDrawEvents();
            iResetAppChannelTable( RESET );
            DeleteListItem( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, 0,  - 1 );
            iLoadBenches();
            iLoadBenchDataIntoTable();
            giTableDataModified = FALSE;
            GetCtrlVal( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, gcSelectedBench );
            if ( DIMMEDTABLE )
            {
               SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, FALSE );
            }
            if ( HIDEPANEL )
            {
               DisplayPanel( giMainPanelHandle );
            }
            iResetAllResources( APP_LOADED );
         }
         break;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int CVICALLBACK CloseErrorWindow( int panel, int control, int event, void*callbackData, int eventData1, int eventData2 )
{
   switch ( event )
   {
      case EVENT_COMMIT:
         HidePanel( giErrorPanel );
         break;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int CVICALLBACK MainPanelCallback( int panel, int event, void *callbackData, int eventData1, int eventData2 )
{
   switch ( event )
   {
      case EVENT_GOT_FOCUS:
         break;
      case EVENT_LOST_FOCUS:
         break;
      case EVENT_CLOSE:
         QuitUserInterface( 0 );
         break;
      case EVENT_PANEL_SIZE:
         iResizeUserInterface();
         break;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int CVICALLBACK ErrorPanelCallback( int panel, int event, void *callbackData, int eventData1, int eventData2 )
{
   switch ( event )
   {
      case EVENT_GOT_FOCUS:
         break;
      case EVENT_LOST_FOCUS:
         break;
      case EVENT_CLOSE:
         HidePanel( giErrorPanel );
         break;
   }
   return 0;
}
int CVICALLBACK RegistrationValueChanged( int panel, int control, int event, void *callbackData, int eventData1, int eventData2 )
{
   switch ( event )
   {
      case EVENT_VAL_CHANGED:
         iUpdateRegistrationText();
         break;
   }
   return 0;
}
int CVICALLBACK InstallLicFile( int panel, int control, int event, void *callbackData, int eventData1, int eventData2 )
{
   int iSelStatus, iError;
   FILE *pFile;
   char cProjectDir[1024];
   char cSourcePathName[1024];
   char cTargetPathName[1024];
   switch ( event )
   {
      case EVENT_COMMIT:
         GetProjectDir( cProjectDir );
         iSelStatus = FileSelectPopup( cProjectDir, "*.lic", "", "Specify path and file name", VAL_SELECT_BUTTON, 0, 1, 1, 0, cSourcePathName );
         if ( iSelStatus == 1 )
         {
            sprintf( cTargetPathName, cProjectDir );
            while ( cTargetPathName[strlen( cTargetPathName ) - 1] != '\\' )
            {
               cTargetPathName[strlen( cTargetPathName ) - 1] = '\0';
            }
            strcat( cTargetPathName, "License\\" );
            strcat( cTargetPathName, gcSystemID );
            strcat( cTargetPathName, "\\" );
            iError = MakeDir( cTargetPathName );
            if ( iError )
            {
               MessagePopup( C_TITLE_MSG_POPUP_ERROR, "Could not create directory for .lic file in license directory." );
               return 0;
            }
            strcat( cTargetPathName, "AE-ITS.lic" );
            iError = CopyFile( cSourcePathName, cTargetPathName );
            if ( iError )
            {
               MessagePopup( C_TITLE_MSG_POPUP_ERROR, "Could not copy file .lic file in license directory." );
               return 0;
            }
            RemovePopup( giRegistrationPanel );
            MessagePopup( C_TITLE_MSG_POPUP, "License file was succesfully installed. Please restart AE-ITS ApplicationEditor to use the complete functionality!" );
            return 0;
         }
         break;
   }
   return 0;
}
int CVICALLBACK CopyTextToClipBoard( int panel, int control, int event, void *callbackData, int eventData1, int eventData2 )
{
   int iTextLength;
   char *cTextBoxValue;
   switch ( event )
   {
      case EVENT_COMMIT:
         GetCtrlAttribute( giRegistrationPanel, REGISTER_TEXTBOX, ATTR_STRING_TEXT_LENGTH, &iTextLength );
         cTextBoxValue = malloc( sizeof( char )*( iTextLength + 1 ));
         GetCtrlVal( giRegistrationPanel, REGISTER_TEXTBOX, cTextBoxValue );
         ClipboardPutText( cTextBoxValue );
         free( cTextBoxValue );
         break;
   }
   return 0;
}
int CVICALLBACK CloseRegisterPanel( int panel, int control, int event, void *callbackData, int eventData1, int eventData2 )
{
   switch ( event )
   {
      case EVENT_COMMIT:
         RemovePopup( giRegistrationPanel );
         break;
   }
   return 0;
}
int CVICALLBACK RegisterPanelCallback( int panel, int event, void *callbackData, int eventData1, int eventData2 )
{
   switch ( event )
   {
      case EVENT_GOT_FOCUS:
         break;
      case EVENT_LOST_FOCUS:
         break;
      case EVENT_CLOSE:
         RemovePopup( giRegistrationPanel );
         break;
   }
   return 0;
}

int CVICALLBACK HideLegend (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(giLegendPanel);
			break;
	}
	return 0;
}

int CVICALLBACK LegendCallBack (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel(giLegendPanel);
			break;
	}
	return 0;
}
