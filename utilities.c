#include "definitions.h"
int iOpenLogFile( void )
{
   char cProjectPathName[1024];
   char cFileName[1024];
   GetProjectDir( cProjectPathName );
   sprintf( cFileName, "%s\\LogFile.txt", cProjectPathName );
   pLogFile = fopen( cFileName, "w" );
   return 0;
}

int iOpenApplicationIniFile (void)
{
	int iStatus;
	char cTextBuffer[1024];
	
	//Improves the performance of reset all gui resources
      if ( HIDEPANEL )
      {
         HidePanel( giMainPanelHandle );
      }
      if ( DIMMEDTABLE )
      {
         SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, TRUE );
      }
      //Make a copy with tmp extension
      sprintf( gcTempAppIniFileName, gcAppIniFileName );
      gcTempAppIniFileName[strlen( gcTempAppIniFileName ) - 1] = 'p';
      gcTempAppIniFileName[strlen( gcTempAppIniFileName ) - 2] = 'm';
      gcTempAppIniFileName[strlen( gcTempAppIniFileName ) - 3] = 't';
      iStatus = CopyFile( gcAppIniFileName, gcTempAppIniFileName );
      //Load benches from app ini into list box
      iStatus = iLoadBenches();
      if ( iStatus )
      {
         DeleteFile( gcTempAppIniFileName );
         DisplayPanel( giMainPanelHandle );
         return ;
      }
      //load bench data from first bench into table
      iStatus = iLoadBenchDataIntoTable();
      if ( iStatus )
      {
         DeleteFile( gcTempAppIniFileName );
         DisplayPanel( giMainPanelHandle );
         return ;
      }
      iStatus = iLoadFreeText();
      if ( iStatus )
      {
         DeleteFile( gcTempAppIniFileName );
         DisplayPanel( giMainPanelHandle );
         return ;
      }
      sprintf( cTextBuffer, "Selected application.ini: %s", gcAppIniFileName );
      SetCtrlVal( giMainPanelHandle, MAINPANEL_INF_APPINI, cTextBuffer );
      SetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, 0 );
      iResetAllResources( APP_LOADED );
      if ( DIMMEDTABLE )
      {
         SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, FALSE );
      }
      if ( HIDEPANEL )
      {
         DisplayPanel( giMainPanelHandle );
      }
      giTableDataModified = FALSE;
      giFreeTextDataModified = FALSE;
      giAppIniDataLoaded = TRUE;
      giAppIniChanged = FALSE;
	  iStatus = iCheckBenchItems( ORIGINAL, TRUE );
      if (iStatus)
      {
         return 0;
      }
	  return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int WriteToLogFile( char *cTextBuffer )
{
   fprintf( pLogFile, cTextBuffer );
   fprintf( pLogFile, "\n" );
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iCloseLogFile( void )
{
   fclose( pLogFile );
   return 0;
}
int iUpdateRegistrationText( void )
{
   char cName[1024];
   char cCompany[1024];
   char cPhoneNumber[1024];
   char cEMailAdress[1024];
   char cText[10000];
   GetCtrlVal( giRegistrationPanel, REGISTER_NAME, cName );
   GetCtrlVal( giRegistrationPanel, REGISTER_COMPANY, cCompany );
   GetCtrlVal( giRegistrationPanel, REGISTER_PHONE, cPhoneNumber );
   GetCtrlVal( giRegistrationPanel, REGISTER_EMAIL, cEMailAdress );
   sprintf( cText, "Here are my registration informations. Please send me the license file for AE-ITS ApplicationEditor\n\n" );
   strcat( cText, "My name: " );
   strcat( cText, cName );
   strcat( cText, "\nMy company: " );
   strcat( cText, cCompany );
   strcat( cText, "\nMy phone number: " );
   strcat( cText, cPhoneNumber );
   strcat( cText, "\nMy e-mail adress: " );
   strcat( cText, cEMailAdress );
   strcat( cText, "\nMy harddisc ID: " );
   strcat( cText, gcSystemID );
   ResetTextBox( giRegistrationPanel, REGISTER_TEXTBOX, cText );
   return 0;
}
short sCheckGTSLError( short sErrorOccurred, long lErrorCode, char *cErrorMessage, char *cFunctionName )
{
   char cTextMessage[1024];
   if ( sErrorOccurred )
   {
      sprintf( cTextMessage, "An error has occurred in function: %s\n\n""Error code: %d\n""Error message: %s\n", cFunctionName, lErrorCode, cErrorMessage );
      if ( DEBUG )
      {
         WriteToLogFile( cTextMessage );
      }
      MessagePopup( C_TITLE_MSG_POPUP, cTextMessage );
   }
   else
   {
      if ( DEBUG )
      {
         sprintf( cTextMessage, "Function %s finished with no errors", cFunctionName );
         WriteToLogFile( cTextMessage );
      }
   }
   return sErrorOccurred;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iResizeUserInterface( void )
{
   int iDisplayHeight;
   int iDisplayWidth;
   GetPanelAttribute( giMainPanelHandle, ATTR_HEIGHT, &iDisplayHeight );
   GetPanelAttribute( giMainPanelHandle, ATTR_WIDTH, &iDisplayWidth );
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, ATTR_WIDTH, iDisplayWidth - 23 );
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, ATTR_TOP, iDisplayHeight - 25 );
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_DECORATION, ATTR_WIDTH, iDisplayWidth - 18 );
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_DECORATION, ATTR_TOP, iDisplayHeight - 27 );
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_DECORATION_2, ATTR_WIDTH, iDisplayWidth - 18 );
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_TITEL2, ATTR_LEFT, iDisplayWidth - ( 178+8 ));
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_TEXTMSG_2, ATTR_LEFT, iDisplayWidth - ( 128+8 ));
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_TAB, ATTR_WIDTH, iDisplayWidth - 18 );
   SetCtrlAttribute( giMainPanelHandle, MAINPANEL_TAB, ATTR_HEIGHT, iDisplayHeight - 118 );
   SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_MODULES, ATTR_HEIGHT, iDisplayHeight - 176 );
   SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_HEIGHT, iDisplayHeight - 176 );
   SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_WIDTH, iDisplayWidth - 216 );
   SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, ATTR_LEFT, iDisplayWidth - 225 );
   SetCtrlAttribute( giTabPanelHandleFreeText, FREETEXT_FREETEXT, ATTR_HEIGHT, iDisplayHeight - 150 );
   SetCtrlAttribute( giTabPanelHandleFreeText, FREETEXT_FREETEXT, ATTR_WIDTH, iDisplayWidth - 22 );
   return 0;
}
