#include <userint.h>
#include "AE.h"
#include "definitions.h"
//#include "lc.h"
#include "resmgr.h"


int main( int argc, char *argv[] )
{
   short sErrorOccurred;
   long lErrorCode;
   int iRestartGUI;
   char cDriveName[1024];
   char cDirectory[1024];
   char cFileName[1024];
   char cErrorMessage2[1024];
   char cProjectDirectory[1024];
   GetProjectDir( cProjectDirectory );
   SplitPath( cProjectDirectory, cDriveName, cDirectory, cFileName );
   /*strcat( cDriveName, "\\" );
   //Allocate the necessary memory
   lpVolumeNameBuffer = malloc( 256 );
   lpFileSystemNameBuffer = malloc( 256 );
   error = GetVolumeInformation( cDriveName,  // root directory
   lpVolumeNameBuffer,  // volume name buffer
   256,  // length of name buffer
    &lpVolumeSerialNumber,  // volume serial number
    &lpMaximumComponentLength,  // maximum file name length
    &lpFileSystemFlags,  // file system options
   lpFileSystemNameBuffer,  // file system name buffer
   256 );
   if ( lpVolumeSerialNumber != 0 )
   {
      sprintf( gcSystemID, "0x%X", lpVolumeSerialNumber );
   }
   else
   {
      if ( !DEBUG )
      {
         MessagePopup( C_TITLE_MSG_POPUP_ERROR, "The installation of AE-ITS ApplicationEditor is wrong. You cannot work on Flash Drives and so on." );
         return 0;
      }
   }	*/
   //Set standard values of globals variables
   giDefaultDataLoaded = FALSE;
   giAppIniDataLoaded = FALSE;
   giTableDataModified = FALSE;
   giTableDataChecked = FALSE;
   giFreeTextDataModified = FALSE;
   giChannelTableHasAnError = FALSE;
   giAppIniChanged = FALSE;
   cChannelTableCaseSensitive = FALSE;
   sprintf( gcAppIniFileName, "" );
   sprintf( gcTempAppIniFileName, "" );
   sprintf( gcErrorBuffer, "" );
   sprintf( gcSelectedBench, "" );
   sprintf( gcPhysicalIniFileName, "" );
   //Get path to standard physical.ini -> found in ApplicationEditor.ini
   //Get tracing flag
   iLoadAppEditIniFile();
   if ( giTracingEnabled )
   {
      iOpenLogFile();
   }
   //Check for license
   /*if ( !DEBUG )
   {
      //Check license
      if ( giTracingEnabled )
      {
         WriteToLogFile( "Check license over hard disc ..." );
      }
      if ( giTracingEnabled )
      {
         WriteToLogFile( "System ID (hard disc) is" );
      }
      if ( giTracingEnabled )
      {
         WriteToLogFile( gcSystemID );
      }
      //Try hard disc ID
      giCorrectLicenseFound = lc_CheckLicense( "AE-ITS", gcSystemID );
      //If Hard disc ID is not working, try resource manager ID
      if ( !giCorrectLicenseFound )
      {
         //Check license
         if ( giTracingEnabled )
         {
            WriteToLogFile( "Check license over resource manager ..." );
         }
         RESMGR_Setup( 0, "", "", &sErrorOccurred, &lErrorCode, cErrorMessage2 );
         //if (sCheckGTSLError(sErrorOccurred, lErrorCode, cErrorMessage2, "RESMGR_Setup")) goto GOTO_OUT_ERROR_TAG ;
         //Delay(0.1);
         RESMGR_Read_ROM( 0, gcSystemID, &sErrorOccurred, &lErrorCode, cErrorMessage2 );
         //if (sCheckGTSLError(sErrorOccurred, lErrorCode, cErrorMessage2, "RESMGR_Read_ROM")) goto GOTO_OUT_ERROR_TAG ;
         //Delay(0.1);
         RESMGR_Cleanup( 0, &sErrorOccurred, &lErrorCode, cErrorMessage2 );
         //if (sCheckGTSLError(sErrorOccurred, lErrorCode, cErrorMessage2, "RESMGR_Cleanup")) goto GOTO_OUT_ERROR_TAG ;
         if ( giTracingEnabled )
         {
            WriteToLogFile( "System ID (ResMgr) is" );
         }
         if ( giTracingEnabled )
         {
            WriteToLogFile( gcSystemID );
         }
         giCorrectLicenseFound = lc_CheckLicense( "SW-ITS", gcSystemID );
      }
      if ( !giCorrectLicenseFound )
      {
         MessagePopup( C_TITLE_MSG_POPUP, "No valid license found or Resource Manager is locked!\nAE-ITS ApplicationEditor is running in demo mode!" );
         sprintf( gcSystemID, "0x%X", lpVolumeSerialNumber );
      }
   }
   else
   {
      giCorrectLicenseFound = TRUE;
   }	*/
   giCorrectLicenseFound = TRUE;
   if ( InitCVIRTE( 0, argv, 0 ) == 0 )
   {
      return  - 1;
   }
   /* out of memory */
   if ( giTracingEnabled )
   {
      WriteToLogFile( "InitCVIRTE" );
   }
   if (( giMainPanelHandle = LoadPanel( 0, "AE.uir", MAINPANEL )) < 0 )
   {
      return  - 1;
   }
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Load main panel" );
   }
   
   if (( giDubPanelHandle = LoadPanel( 0, "AE.uir", DUBPLICATE )) < 0 )
   {
      return  - 1;
   }
   
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Load dub panel" );
   }
   
   if (( gSplash = LoadPanel( 0, "Splash.uir", SPLASH )) < 0 )
   {
      return  - 1;
   }
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Load error panel" );
   }
   if (( giErrorPanel = LoadPanel( 0, "AE.uir", ERRORS )) < 0 )
   {
      return  - 1;
   }
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Load registration panel" );
   }
   if (( giRegistrationPanel = LoadPanel( 0, "AE.uir", REGISTER )) < 0 )
   {
      return  - 1;
   }
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Load legend panel" );
   }
   if (( giLegendPanel = LoadPanel( 0, "AE.uir", LEGEND )) < 0 )
   {
      return  - 1;
   }
   
   giMenuBarHandle = GetPanelMenuBar( giMainPanelHandle );
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Get menu bar handle" );
   }
   
   GetPanelHandleFromTabPage( giMainPanelHandle, MAINPANEL_TAB, 0, &giTabPanelHandleLogicalNames );
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Get tab handle logical names" );
   }
   
   GetPanelHandleFromTabPage( giMainPanelHandle, MAINPANEL_TAB, 1, &giTabPanelHandleFreeText );
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Get tab free text" );
   }
   
   
   //Set standard layout of gui reosurces
   SetCtrlVal( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, "" );
   if ( giCorrectLicenseFound )
   {
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_HELP_REGISTER, ATTR_DIMMED, TRUE );
   }
   else
   {
      SetPanelAttribute( giMainPanelHandle, ATTR_TITLE, "AE-ITS ApplicationEditor (Demo mode)" );
   }
   
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION, ATTR_CMD_BUTTON_COLOR, VAL_WHITE);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION, ATTR_DISABLE_PANEL_THEME, TRUE);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_1, ATTR_CMD_BUTTON_COLOR, CELLBGCOLOUR_USED);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_1, ATTR_DISABLE_PANEL_THEME, TRUE);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_2, ATTR_CMD_BUTTON_COLOR, CELLBGCOLOUR_INDICATOR);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_2, ATTR_DISABLE_PANEL_THEME, TRUE);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_3, ATTR_CMD_BUTTON_COLOR, CELLBGCOLOUR_CHANGED);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_3, ATTR_DISABLE_PANEL_THEME, TRUE);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_4, ATTR_CMD_BUTTON_COLOR, CELLBGCOLOUR_CHECKED_OK);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_4, ATTR_DISABLE_PANEL_THEME, TRUE);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_5, ATTR_CMD_BUTTON_COLOR, CELLBGCOLOUR_CHECKED_NOK);
   SetCtrlAttribute (giLegendPanel, LEGEND_DECORATION_5, ATTR_DISABLE_PANEL_THEME, TRUE);
   
   
   //If path found, load default data into table
   if ( strlen( gcPhysicalIniFileName ))
   {
      if ( giTracingEnabled )
      {
         WriteToLogFile( "Load Default Data Into Table" );
      }
      iLoadDefaultDataIntoTable();
      giDefaultDataLoaded = TRUE;
   }
   
   
   if ( giTracingEnabled )
   {
      WriteToLogFile( "Resize user interface" );
   }
   iResizeUserInterface();
   
   DisplayPanel( giMainPanelHandle );
   
   if (argc == 2)
   {
	 	sprintf(gcAppIniFileName, argv[1]);
		iOpenApplicationIniFile();
   }
   
GOTO_RUN_USER_INTERFACE_TAG:
   
   RunUserInterface();
   
   iRestartGUI = iCheckVariableBeforeClosing();
   if ( iRestartGUI )
   {
      goto GOTO_RUN_USER_INTERFACE_TAG;
   }
   
   if ( giTracingEnabled )
   {
      WriteToLogFile( "discard all panel handles" );
   }
   
   DiscardPanel( giMainPanelHandle );
   DiscardPanel( gSplash );
   DiscardPanel( giErrorPanel );
   DiscardPanel( giRegistrationPanel );
   DiscardPanel(giLegendPanel);
			
   if ( giTracingEnabled )
   {
      WriteToLogFile( "dispose app ini handle if nessecary" );
   }
   if ( gAppIniFileHandle )
   {
      Ini_Dispose( gAppIniFileHandle );
   }
   gAppIniFileHandle = NULL;
   if ( giTracingEnabled )
   {
      WriteToLogFile( "delete temp file if nessecary" );
   }
   if ( strlen( gcTempAppIniFileName ))
   {
      DeleteFile( gcTempAppIniFileName );
   }
   GOTO_OUT_ERROR_TAG:
   free( lpVolumeNameBuffer );
   free( lpFileSystemNameBuffer );
   if ( giTracingEnabled )
   {
      iCloseLogFile();
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iLoadAppEditIniFile( void )
{
   IniText iniFileHandle;
   char cProjectPathName[1024];
   char cIniFileName[1024];
   int iIniFileStatus, iSectionExists;
   if ( giTracingEnabled )
   {
      WriteToLogFile( "BEGIN iLoadAppEditIniFile" );
   }
   if ( giTracingEnabled )
   {
      WriteToLogFile( "get project directory" );
   }
   sprintf( cProjectPathName, "C:\\Users\\Public\\Documents\\SW-ITS\\Configuration"); 
   sprintf( cIniFileName, "%s\\ApplicationEditor.ini", cProjectPathName );
   if ( giTracingEnabled )
   {
      WriteToLogFile( cProjectPathName );
   }
   iniFileHandle = Ini_New( 0 );
   if ( giTracingEnabled )
   {
      WriteToLogFile( "read ini file application editor" );
   }
   iIniFileStatus = Ini_ReadFromFile( iniFileHandle, cIniFileName );
   if ( iIniFileStatus != SUCCESS )
   {
      if ( giTracingEnabled )
      {
         WriteToLogFile( "an error occurrred" );
      }
      return 0;
   }
   iSectionExists = Ini_SectionExists( iniFileHandle, "ApplicationEditor" );
   if ( iSectionExists )
   {
      iIniFileStatus = Ini_GetRawStringIntoBuffer( iniFileHandle, "ApplicationEditor", "PhysicalIniFile", gcPhysicalIniFileName, 1024 );
      iIniFileStatus = Ini_GetRawStringIntoBuffer( iniFileHandle, "ApplicationEditor", "LastUsedAppIniFile", gcLastUsedAppIniFileName, 1024 );
      iIniFileStatus = Ini_GetInt( iniFileHandle, "ApplicationEditor", "TracingEnabled", &giTracingEnabled );
      if ( iIniFileStatus != TRUE )
      {
         giTracingEnabled = FALSE;
      }
      iIniFileStatus = Ini_GetInt( iniFileHandle, "ApplicationEditor", "ShowOnlyApplicationModules", &giShowOnlyApplicationModules );
      if ( iIniFileStatus != TRUE )
      {
         giShowOnlyApplicationModules = FALSE;
      }
   }
   Ini_Dispose( iniFileHandle );
   if ( giTracingEnabled )
   {
      WriteToLogFile( "END iLoadAppEditIniFile" );
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iSaveAppEditIniFile( void )
{
   IniText iniFileHandle;
   char cProjectPathName[1024];
   char cIniFileName[1024];
   int iIniFileStatus, iSectionExists;
   sprintf( cProjectPathName, "C:\\Users\\Public\\Documents\\SW-ITS\\Configuration"); 
   sprintf( cIniFileName, "%s\\ApplicationEditor.ini", cProjectPathName );
   iniFileHandle = Ini_New( 0 );
   iIniFileStatus = Ini_ReadFromFile( iniFileHandle, cIniFileName );
   if ( iIniFileStatus != SUCCESS )
   {
      return 0;
   }
   iSectionExists = Ini_SectionExists( iniFileHandle, "ApplicationEditor" );
   if ( iSectionExists )
   {
      iIniFileStatus = Ini_PutRawString( iniFileHandle, "ApplicationEditor", "PhysicalIniFile", gcPhysicalIniFileName );
   }
   iIniFileStatus = Ini_WriteToFile( iniFileHandle, cIniFileName );
   if ( iIniFileStatus != SUCCESS )
   {
      MessagePopup( C_TITLE_MSG_POPUP_ERROR, "An error occurred while writing ApplicationEditor.ini" );
   }
   Ini_Dispose( iniFileHandle );
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iLoadDefaultDataIntoTable( void )
{
   int iIniFileStatus;
   int iSelectionStatus;
   int iNumSections;
   int iTypeItemExits;
   int iFrameItemExits;
   int iSlotItemExits;
   int iFrameNumber;
   int iSlotNumber;
   int iFrameIndex;
   int iSlotIndex;
   int idx, idy, idz, iCopyEnabled;
   int iFileExists;
   int iFileSize;
   int iModules;
   int iTreeStatus;
   int iTreeItemIndex;
   char *cSectionName;
   char *cTempValue;
   char cTypeValue[1024];
   char cFrameNumber[1024];
   char cDeviceName[1024];
   char cTextBuffer[1024];
   Point pCell;
   //Check if file exists
   iFileExists = FileExists( gcPhysicalIniFileName, &iFileSize );
   if ( iFileExists != TRUE )
   {
      iSelectionStatus = FileSelectPopup( "", "*.ini", "ini", "Please select a physical.ini file", VAL_LOAD_BUTTON, 0, 1, 1, 0, gcPhysicalIniFileName );
      if ( iSelectionStatus == 1 )
      {
         iSaveAppEditIniFile();
      }
      else
      {
         return 0;
      }
   }
   if ( giDefaultDataLoaded )
   {
      iResetAllResources( RESET_GUI_FULL );
   }
   iModules = 0;
   giTableDataModified = FALSE;
   pFirstPhyStructure = NULL;
   sprintf( cTextBuffer, "Selected physical.ini: %s", gcPhysicalIniFileName );
   SetCtrlVal( giMainPanelHandle, MAINPANEL_INF_PHYINI, cTextBuffer );
   if ( gPhysicalIniFileHandle )
   {
      Ini_Dispose( gPhysicalIniFileHandle );
   }
   //Reset frame settings
   for ( idx = 0; idx < 5; idx++ )
   for ( idy = 0; idy < 17; idy++ )
   {
      giFrameSettings[idx][idy] =  - 1;
   }
   //Open phsyical ini file
   gPhysicalIniFileHandle = Ini_New( 0 );
   iIniFileStatus = Ini_ReadFromFile( gPhysicalIniFileHandle, gcPhysicalIniFileName );
   //Get Number of sections
   iNumSections = Ini_NumberOfSections( gPhysicalIniFileHandle );
   for ( idx = 1; idx <= iNumSections; idx++ )
   {
      Ini_NthSectionName( gPhysicalIniFileHandle, idx, &cSectionName );
      iTypeItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Type" );
      iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
      iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
      if ( iTypeItemExits && iFrameItemExits && iSlotItemExits )
      {
         iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
         iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
		 iIniFileStatus = Ini_GetRawStringCopy (gPhysicalIniFileHandle, cSectionName, "Type", &cTempValue);

         //Set section index
         if ((stricmp (cTempValue, "PSYS1")) && (stricmp (cTempValue, "PSYS2"))) giFrameSettings[iFrameNumber][iSlotNumber] = idx;
      }
   }
   for ( iFrameIndex = 1; iFrameIndex <= 4; iFrameIndex++ )
   {
      for ( iSlotIndex = 1; iSlotIndex <= 16; iSlotIndex++ )
      {
         idx = giFrameSettings[iFrameIndex][iSlotIndex];
         if ( idx !=  - 1 )
         {
            Ini_NthSectionName( gPhysicalIniFileHandle, idx, &cSectionName );
            iTypeItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Type" );
            if ( iTypeItemExits )
            {
               idz = 0;
               iCopyEnabled = 0;
               for ( idy = 0; idy < strlen( cSectionName ); idy++ )
               {
                  if ( iCopyEnabled )
                  {
                     cDeviceName[idz] = cSectionName[idy];
                     idz++;
                  }
                  if ( cSectionName[idy] == '>' )
                  {
                     iCopyEnabled++;
                  }
               }
               cDeviceName[idz] = '\0';
               iIniFileStatus = Ini_GetStringIntoBuffer( gPhysicalIniFileHandle, cSectionName, "Type", cTypeValue, 1024 );
               if ( !stricmp( cTypeValue, "PAM" ) && !giShowOnlyApplicationModules )
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABA1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABB1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABC1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABD1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA1_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA2_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA3_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA4_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB1_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB2_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB3_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB4_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA1_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA2_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA3_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA4_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB1_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB2_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB3_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB4_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABA2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABB2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABC2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABD2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA1_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA2_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA3_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHA4_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB1_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB2_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB3_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CHB4_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHB_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
               if ( !stricmp( cTypeValue, "PSAM" ) && !giShowOnlyApplicationModules )
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABA1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABB1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABC1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABD1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "IL1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "RACH1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "RACH2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "RACH3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "RACH4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "RACOM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "AUX1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABA2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABB2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABC2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABD2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "IL2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "RBCH1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "RBCH2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "RBCH3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "RBCH4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "RBCOM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "AUX2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
               if ( !stricmp( cTypeValue, "PSU" ) && !giShowOnlyApplicationModules )
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABA1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABB1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABC1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABD1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SHI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SHI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SHI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SHI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SHI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SHI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SHI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SHI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_MHI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_MLO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_MHI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_MLO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABA2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABB2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABC2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "LABD2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SLO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SLO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SLO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_SLO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SLO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SLO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SLO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_SLO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
               if ( !stricmp( cTypeValue, "PMB" ))
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
					 
					 InsertListItem (giDubPanelHandle, DUBPLICATE_START_PMB, -1, cDeviceName, cDeviceName);
					 InsertListItem (giDubPanelHandle, DUBPLICATE_DUBSTART_PMB, -1, cDeviceName, cDeviceName);
					 
						 
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "P8", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "P10", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "P11", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "P12", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "P13", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "P14", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "P15", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "P16", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "P17", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "P18", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "P19", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "P20", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "P21", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "P22", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "P23", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "P24", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "P25", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "P26", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "P27", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "P28", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_HOT, "P29", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_HOT, "P30", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_HOT, "P31", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_HOT, "P32", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "P33", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "P34", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "P35", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "P36", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "P37", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "P38", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "P39", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "P40", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "P41", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "P42", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "P43", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "P44", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "P45", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "P46", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "P47", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "P48", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "P49", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "P50", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "P51", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "P52", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "P53", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "P54", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "P55", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "P56", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "P57", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "P58", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "P59", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "P60", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_HOT, "P61", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_HOT, "P62", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_HOT, "P63", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_HOT, "P64", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "P65", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "P66", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "P67", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "P68", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "P69", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "P70", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "P71", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "P72", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "P73", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "P74", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "P75", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "P76", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "P77", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "P78", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "P79", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "P80", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "P81", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "P82", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "P83", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "P84", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "P85", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "P86", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "P87", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "P88", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "P89", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "P90", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GNDNO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GNDNO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GNDNO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
               if ( !stricmp( cTypeValue, "PSM1" ))
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH9_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH9_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH12_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH12_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH15_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH15_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_HOT, "IL1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_HOT, "IL1_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH10_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH10_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH13_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH13_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH16_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH16_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_HOT, "IL2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_HOT, "IL2_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH11_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH11_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH14_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH14_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
               if ( !stricmp( cTypeValue, "PSM2" ))
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH3_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH6_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH2_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH5_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH8_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH1_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH1_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH2_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH3_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH4_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH4_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH5_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_LO1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_LO2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_HI4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH6_LO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CH7_THRU", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_HI3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH7_LO4", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_HI1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_HI2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_LO3", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_HOT, "CH8_HI", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
               if ( !stricmp( cTypeValue, "PDFT" ))
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX1A_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX2A_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX3A_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX4A_NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT9", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN9", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT12", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN12", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT15", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN15", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT17", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN17", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT20", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN20", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT23", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN23", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT25", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN25", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT28", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN28", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT31", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN31", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTO", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "XTI", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CAN_L", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CAN_H", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX1A_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX2A_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX3A_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "AUX4A_COM", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT8", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN8", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT10", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN10", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT13", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN13", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT16", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN16", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT18", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN18", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT21", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN21", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT24", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN24", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT26", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN26", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT29", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN29", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT32", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN32", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "RS232_TX", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "RS232_RX", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "VCAN_L", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "VCAN_H", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "PO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "PO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "PO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "PO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND-NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT11", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN11", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT14", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN14", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND-NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT19", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN19", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT22", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN22", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND-NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT27", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN27", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_HOT, "OUT30", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "IN30", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND-NO", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "VBAT", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "KBUS", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
               if ( !stricmp( cTypeValue, "PIO3B" ))
               {
                  iFrameItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Frame" );
                  iSlotItemExits = Ini_ItemExists( gPhysicalIniFileHandle, cSectionName, "Slot" );
                  if ( iFrameItemExits && iSlotItemExits )
                  {
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Frame", &iFrameNumber );
                     iIniFileStatus = Ini_GetUInt( gPhysicalIniFileHandle, cSectionName, "Slot", &iSlotNumber );
                     sprintf( cFrameNumber, "Frame %i", iFrameNumber );
                     iTreeStatus = GetTreeItemFromLabel( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_ALL, 0, VAL_FIRST, VAL_NEXT, 0, cFrameNumber, &iTreeItemIndex );
                     sprintf( cTextBuffer, "%s (Slot %i)", cDeviceName, iSlotNumber );
                     iModules++;
                     InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, iTreeItemIndex, VAL_LAST, cTextBuffer, "", NULL, iModules );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     iTreeStatus = InsertTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES,  - 1, 1, VAL_CELL_STRING );
                     ProcessDrawEvents();
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_USE_LABEL_TEXT, 1 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_USE_LABEL_TEXT, 1 );
                     sprintf( cTextBuffer, "%s | C", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | B", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_LABEL_TEXT, cTextBuffer );
                     sprintf( cTextBuffer, "%s | A", cDeviceName );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_LABEL_TEXT, cTextBuffer );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 0, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 1, ATTR_COLUMN_WIDTH, 100 );
                     iTreeStatus = SetTableColumnAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ( iModules *3 ) - 2, ATTR_COLUMN_WIDTH, 100 );
                     pCell = MakePoint(( iModules *3 ) - 2, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "P0IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "P1IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "P2IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 2, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "P10AIN7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "P5IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "P6IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "P7IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "SCLK", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 26 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "MISO", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "MOSI", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "AUX1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "AUX2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "+5V", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "+12V", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 1, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 1 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 2 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 3 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 4 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 5 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 6 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 7 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 8 );
                     iSetTableCellValue( pCell, VAL_HOT, "P3IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 9 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 10 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 11 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 12 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 13 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 14 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 15 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 16 );
                     iSetTableCellValue( pCell, VAL_HOT, "P4IO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 17 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO0", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 18 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO1", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 19 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO2", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 20 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO3", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 21 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO4", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 22 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO5", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 23 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO6", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 24 );
                     iSetTableCellValue( pCell, VAL_HOT, "P9TIO7", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 25 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CFG_AIN", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 26 );
                     iSetTableCellValue( pCell, VAL_HOT, "INH", cDeviceName, cTypeValue, TRUE );
                     pCell = MakePoint(( iModules *3 ) - 0, 27 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "AUX1", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 28 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "AUX2", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 29 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "+5V", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 30 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "+12V", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 31 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "GND", cDeviceName, cTypeValue, FALSE );
                     pCell = MakePoint(( iModules *3 ) - 0, 32 );
                     iSetTableCellValue( pCell, VAL_INDICATOR, "CHA-GND", cDeviceName, cTypeValue, FALSE );
                  }
               }
            }
         }
      }
   }

   for (idx = 1; idx <= 90; idx++)
   {
	   sprintf(cTextBuffer, "P%d", idx);
	   InsertListItem (giDubPanelHandle, DUBPLICATE_START_PMB_PIN, -1, cTextBuffer, cTextBuffer);
	   InsertListItem (giDubPanelHandle, DUBPLICATE_DUBSTART_PMB_PIN, -1, cTextBuffer, cTextBuffer);
   }
   iResetAllResources( PHY_LOADED );
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iLoadBenches( void )
{
   int iSectionExists;
   int iCountOfLogicalNames;
   int idx;
   int iIniFileStatus;
   char *cBenchName;
   char cBenchTag[1024];
   if ( gAppIniFileHandle )
   {
      Ini_Dispose( gAppIniFileHandle );
   }
   gAppIniFileHandle = Ini_New( 0 );
   iIniFileStatus = Ini_ReadFromFile( gAppIniFileHandle, gcTempAppIniFileName );
   iSectionExists = Ini_SectionExists( gAppIniFileHandle, "LogicalNames" );
   if ( iSectionExists )
   {
      iCountOfLogicalNames = Ini_NumberOfItems( gAppIniFileHandle, "LogicalNames" );
      for ( idx = 1; idx <= iCountOfLogicalNames; idx++ )
      {
         Ini_NthItemName( gAppIniFileHandle, "LogicalNames", idx, &cBenchName );
         Ini_GetRawStringIntoBuffer( gAppIniFileHandle, "LogicalNames", cBenchName, cBenchTag, 1024 );
         if ( strlen( cBenchName ) && strlen( cBenchTag ))
         {
            InsertListItem( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH,  - 1, cBenchName, cBenchTag );
         }
         if ( idx == 1 )
         {
            sprintf( gcSelectedBench, cBenchTag );
         }
      }
   }
   else
   {
      MessagePopup( C_TITLE_MSG_POPUP_ERROR, "The section \"LogicalNames\" does not existst. This is not a valid application.ini" );
      return  - 1;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iLoadBenchDataIntoTable( void )
{
   int idx, idy, idz;
   int iSectionExists;
   int iItemExists;
   int iCountOfLogicalNames;
   int SwitchCopy;
   char cBenchTag[1024];
   char cAppChannelTag[1024];
   char *cLogicalPinName;
   char cPhysicalResource[1024];
   char cDeviceName[1024];
   char cDefaultPinName[1024];
   GetCtrlVal( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, cBenchTag );
   iSectionExists = Ini_SectionExists( gAppIniFileHandle, cBenchTag );
   if ( iSectionExists )
   {
      iItemExists = Ini_ItemExists( gAppIniFileHandle, cBenchTag, "ChannelTableCaseSensitive" );
      if ( iItemExists )
      {
         Ini_GetUInt( gAppIniFileHandle, cBenchTag, "ChannelTableCaseSensitive", &cChannelTableCaseSensitive );
      }
      else
      {
         cChannelTableCaseSensitive = FALSE;
      }
      if ( cChannelTableCaseSensitive )
      {
         SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_LABEL_TEXT, "Logical Names (Content is case sensitive!)" );
      }
      else
      {
         SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_LABEL_TEXT, "Logical Names (Content is case not sensitive!)" );
      }
      iItemExists = Ini_ItemExists( gAppIniFileHandle, cBenchTag, "AppChannelTable" );
      if ( iItemExists )
      {
         Ini_GetRawStringIntoBuffer( gAppIniFileHandle, cBenchTag, "AppChannelTable", cAppChannelTag, 1024 );
         if ( strlen( cAppChannelTag ))
         {
            iSectionExists = Ini_SectionExists( gAppIniFileHandle, cAppChannelTag );
            if ( iSectionExists )
            {
               iSetChannelSection( cAppChannelTag, "" );
               iCountOfLogicalNames = Ini_NumberOfItems( gAppIniFileHandle, cAppChannelTag );
               for ( idx = 1; idx <= iCountOfLogicalNames; idx++ )
               {
                  Ini_NthItemName( gAppIniFileHandle, cAppChannelTag, idx, &cLogicalPinName );
                  Ini_GetRawStringIntoBuffer( gAppIniFileHandle, cAppChannelTag, cLogicalPinName, cPhysicalResource, 1024 );
                  SwitchCopy = 0;
                  idz = 0;
                  for ( idy = 0; idy < strlen( cPhysicalResource ); idy++ )
                  {
                     if ( cPhysicalResource[idy] == '!' )
                     {
                        cDeviceName[idy] = '\0';
                        SwitchCopy++;
                        idy++;
                     }
                     if ( !SwitchCopy )
                     {
                        cDeviceName[idy] = cPhysicalResource[idy];
                     }
                     if ( SwitchCopy )
                     {
                        cDefaultPinName[idz] = cPhysicalResource[idy];
                        idz++;
                     }
                  }
                  cDefaultPinName[idz] = '\0';
                  iSetAppChannelTable( cLogicalPinName, cDeviceName, cDefaultPinName );
               }
            }
         }
      }
      iItemExists = Ini_ItemExists( gAppIniFileHandle, cBenchTag, "DIOChannelTable" );
      if ( iItemExists )
      {
         Ini_GetRawStringIntoBuffer( gAppIniFileHandle, cBenchTag, "DIOChannelTable", cAppChannelTag, 1024 );
         if ( strlen( cAppChannelTag ))
         {
            iSectionExists = Ini_SectionExists( gAppIniFileHandle, cAppChannelTag );
            if ( iSectionExists )
            {
               iSetChannelSection( "", cAppChannelTag );
               iCountOfLogicalNames = Ini_NumberOfItems( gAppIniFileHandle, cAppChannelTag );
               for ( idx = 1; idx <= iCountOfLogicalNames; idx++ )
               {
                  Ini_NthItemName( gAppIniFileHandle, cAppChannelTag, idx, &cLogicalPinName );
                  Ini_GetRawStringIntoBuffer( gAppIniFileHandle, cAppChannelTag, cLogicalPinName, cPhysicalResource, 1024 );
                  SwitchCopy = 0;
                  idz = 0;
                  for ( idy = 0; idy < strlen( cPhysicalResource ); idy++ )
                  {
                     if ( cPhysicalResource[idy] == '!' )
                     {
                        cDeviceName[idy] = '\0';
                        SwitchCopy++;
                        idy++;
                     }
                     if ( !SwitchCopy )
                     {
                        cDeviceName[idy] = cPhysicalResource[idy];
                     }
                     if ( SwitchCopy )
                     {
                        cDefaultPinName[idz] = cPhysicalResource[idy];
                        idz++;
                     }
                  }
                  cDefaultPinName[idz] = '\0';
                  iSetAppChannelTable( cLogicalPinName, cDeviceName, cDefaultPinName );
               }
            }
         }
      }
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iLoadFreeText( void )
{
   FILE *pFile;
   int iFileSize;
   int idx;
   char *cTextBuffer;
   FileExists( gcTempAppIniFileName, &iFileSize );
   cTextBuffer = malloc( iFileSize );
   idx = 0;
   pFile = fopen( gcTempAppIniFileName, "r" );
   while ( !feof( pFile ))
   {
      cTextBuffer[idx] = fgetc( pFile );
      if ( cTextBuffer[idx] == 0x09 )
      {
         cTextBuffer[idx] = ' ';
      }
      idx++;
   }
   cTextBuffer[idx - 1] = '\0';
   ResetTextBox( giTabPanelHandleFreeText, FREETEXT_FREETEXT, cTextBuffer );
   free( cTextBuffer );
   fclose( pFile );
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iSaveFreeText( void )
{
   FILE *pFile;
   int iFileSize;
   int idx;
   char *cTextBuffer;
   GetCtrlAttribute( giTabPanelHandleFreeText, FREETEXT_FREETEXT, ATTR_STRING_TEXT_LENGTH, &iFileSize );
   cTextBuffer = malloc( iFileSize + 1 );
   GetCtrlVal( giTabPanelHandleFreeText, FREETEXT_FREETEXT, cTextBuffer );
   pFile = fopen( gcTempAppIniFileName, "w" );
   fprintf( pFile, cTextBuffer );
   free( cTextBuffer );
   fclose( pFile );
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iResetAllResources( int iType )
{
   char cTextBuffer[1024];
   if ( iType == RESET_GUI_FULL )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_MODULES, ATTR_DIMMED, 1 );
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, 1 );
      SetCtrlAttribute( giTabPanelHandleFreeText, FREETEXT_FREETEXT, ATTR_DIMMED, 1 );
      DeleteTableColumns( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, 1,  - 1 );
      DeleteListItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, 0,  - 1 );
      InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, 0, VAL_LAST, "TSVP", "", NULL, 0 );
      InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, 0, VAL_LAST, "Frame 1", "", NULL, 0 );
      InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, 0, VAL_LAST, "Frame 2", "", NULL, 0 );
      InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, 0, VAL_LAST, "Frame 3", "", NULL, 0 );
      InsertTreeItem( giTabPanelHandleLogicalNames, LOGICAL_MODULES, VAL_CHILD, 0, VAL_LAST, "Frame 4", "", NULL, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SETPHYINI, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_OPENAPPINI, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINI, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINIAS, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_CLOSEAPPINI, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULCELLVAL, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINALCELLVAL, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_CHECKTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_APPLYTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
	  SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_DUBPLICATE, ATTR_DIMMED, 1 ); 
   }
   else if ( iType == PHY_LOADED )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_MODULES, ATTR_DIMMED, 1 );
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, 1 );
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, ATTR_DIMMED, 1 );
      DeleteListItem( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, 0,  - 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SETPHYINI, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_OPENAPPINI, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINI, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINIAS, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_CLOSEAPPINI, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULCELLVAL, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINALCELLVAL, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_CHECKTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_SHOWERROR, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_APPLYTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
	  SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_DUBPLICATE, ATTR_DIMMED, 1 );
   }
   else if ( iType == APP_LOADED )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_MODULES, ATTR_DIMMED, 0 );
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, 0 );
      SetCtrlAttribute( giTabPanelHandleFreeText, FREETEXT_FREETEXT, ATTR_DIMMED, 1 );
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_SELECTBENCCH, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SETPHYINI, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINIAS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_CLOSEAPPINI, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINALCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_CHECKTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_SHOWERROR, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_APPLYTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
	  SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_DUBPLICATE, ATTR_DIMMED, 0 );   
   }
   else if ( iType == TABLE_DATA_MODIFIED )
   {
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINI, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINALCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_CHECKTABLE, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_SHOWERROR, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_APPLYTABLE, ATTR_DIMMED, 1 );
      GetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 0, ATTR_LABEL_TEXT, cTextBuffer );
      strcat( cTextBuffer, " *" );
      SetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 0, ATTR_LABEL_TEXT, cTextBuffer );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
   }
   else if ( iType == TABLE_DATA_CHECKED )
   {
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINALCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_CHECKTABLE, ATTR_DIMMED, 0 );
      if ( giChannelTableHasAnError )
      {
         SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_SHOWERROR, ATTR_DIMMED, 0 );
      }
      if ( !giChannelTableHasAnError )
      {
         SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_SHOWERROR, ATTR_DIMMED, 1 );
      }
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_APPLYTABLE, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
   }
   else if ( iType == TABLE_DATA_APPLIED )
   {
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINALCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_CHECKTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_SHOWERROR, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_APPLYTABLE, ATTR_DIMMED, 1 );
      GetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 0, ATTR_LABEL_TEXT, cTextBuffer );
      cTextBuffer[strlen( cTextBuffer ) - 2] = '\0';
      SetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 0, ATTR_LABEL_TEXT, cTextBuffer );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
      iResetAllResources( APP_INI_CHANGED );
   }
   else if ( iType == TABLE_DATA_RESET )
   {
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINALCELLVAL, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS, ATTR_DIMMED, 0 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_CHECKTABLE, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_SHOWERROR, ATTR_DIMMED, 1 );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDIT_APPLYTABLE, ATTR_DIMMED, 1 );
      GetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 0, ATTR_LABEL_TEXT, cTextBuffer );
      cTextBuffer[strlen( cTextBuffer ) - 2] = '\0';
      SetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 0, ATTR_LABEL_TEXT, cTextBuffer );
      SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT, ATTR_DIMMED, 1 );
   }
   else if ( iType == FREE_TEXT_MODIFIED )
   {
      if ( !giFreeTextDataModified )
      {
         GetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 1, ATTR_LABEL_TEXT, cTextBuffer );
         strcat( cTextBuffer, " *" );
         SetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 1, ATTR_LABEL_TEXT, cTextBuffer );
         SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT_APPLYTABLE, ATTR_DIMMED, 0 );
         SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINI, ATTR_DIMMED, 0 );
      }
   }
   else if ( iType == FREE_TEXT_RESET )
   {
      if ( giFreeTextDataModified )
      {
         GetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 1, ATTR_LABEL_TEXT, cTextBuffer );
         cTextBuffer[strlen( cTextBuffer ) - 2] = '\0';
         SetTabPageAttribute( giMainPanelHandle, MAINPANEL_TAB, 1, ATTR_LABEL_TEXT, cTextBuffer );
         SetMenuBarAttribute( giMenuBarHandle, MENUBAR_EDITFREETEXT_APPLYTABLE, ATTR_DIMMED, 1 );
         iResetAllResources( APP_INI_CHANGED );
      }
   }
   else if ( iType == APP_INI_CHANGED )
   {
      if ( !giAppIniChanged )
      {
         GetCtrlVal( giMainPanelHandle, MAINPANEL_INF_APPINI, cTextBuffer );
         strcat( cTextBuffer, " *" );
         SetCtrlVal( giMainPanelHandle, MAINPANEL_INF_APPINI, cTextBuffer );
         SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINI, ATTR_DIMMED, 0 );
      }
   }
   else if ( iType == APP_INI_SAVED )
   {
      if ( giAppIniChanged )
      {
         GetCtrlVal( giMainPanelHandle, MAINPANEL_INF_APPINI, cTextBuffer );
         cTextBuffer[strlen( cTextBuffer ) - 2] = '\0';
         SetCtrlVal( giMainPanelHandle, MAINPANEL_INF_APPINI, cTextBuffer );
         SetMenuBarAttribute( giMenuBarHandle, MENUBAR_FILE_SAVEAPPINI, ATTR_DIMMED, 1 );
      }
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iSetTableCellValue( Point pCell, int iHotOrIndicator, char *cDefaultName, char *cDeviceName, char *cTypeValue, char cIsDigital )
{
   if ( iHotOrIndicator == VAL_HOT )
   {
      SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, cDefaultName );
      SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_STR_CELL_DFLT_VALUE, cDefaultName );
      iAppendPinToPinList( cTypeValue, cDeviceName, cDefaultName, cIsDigital, pCell.x, pCell.y );
   }
   else if ( iHotOrIndicator == VAL_INDICATOR )
   {
      SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, cDefaultName );
      SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_INDICATOR );
      SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_CELL_MODE, VAL_INDICATOR );
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iAppendPinToPinList( char *cType, char *cDeviceName, char *cDefaultName, char cIsDigital, int iColumn, int iRow )
{
   PHYSCIALSTRUCTURE *pLast;
   if ( !pFirstPhyStructure )
   {
      pFirstPhyStructure = malloc( sizeof( *pFirstPhyStructure ));
      if ( !pFirstPhyStructure )
      {
         return  - 1;
      }
      sprintf( pFirstPhyStructure->cIniSection, "" );
      sprintf( pFirstPhyStructure->cType, cType );
      sprintf( pFirstPhyStructure->cDeviceName, cDeviceName );
      sprintf( pFirstPhyStructure->cDefaultName, cDefaultName );
      sprintf( pFirstPhyStructure->cActualName, "" );
      sprintf( pFirstPhyStructure->cOriginalName, "" );
      pFirstPhyStructure->iColumn = iColumn;
      pFirstPhyStructure->iRow = iRow;
      pFirstPhyStructure->cIsChanged = FALSE;
      pFirstPhyStructure->cIsDefault = TRUE;
      pFirstPhyStructure->cIsDigital = cIsDigital;
      pFirstPhyStructure->pNext = NULL;
   }
   else
   {
      pLast = pFirstPhyStructure;
      while ( pLast->pNext != NULL )
      {
         pLast = pLast->pNext;
      }
      pLast->pNext = malloc( sizeof( *pFirstPhyStructure ));
      if ( !pLast->pNext )
      {
         return  - 1;
      }
      sprintf( pLast->pNext->cIniSection, "" );
      sprintf( pLast->pNext->cType, cType );
      sprintf( pLast->pNext->cDeviceName, cDeviceName );
      sprintf( pLast->pNext->cDefaultName, cDefaultName );
      sprintf( pLast->pNext->cActualName, "" );
      sprintf( pLast->pNext->cOriginalName, "" );
      pLast->pNext->iColumn = iColumn;
      pLast->pNext->iRow = iRow;
      pLast->pNext->cIsChanged = FALSE;
      pLast->pNext->cIsDefault = TRUE;
      pLast->pNext->cIsDigital = cIsDigital;
      pLast->pNext->pNext = NULL;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iResetPinList( void )
{
   PHYSCIALSTRUCTURE *pNext;
   if ( pFirstPhyStructure )
   {
      pNext = pFirstPhyStructure;
      while ( pNext )
      {
         sprintf( pNext->cActualName, "" );
         sprintf( pNext->cOriginalName, "" );
         pNext->cIsChanged = FALSE;
         pNext = pNext->pNext;
      }
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iFreePinList( void )
{
   PHYSCIALSTRUCTURE *pNext,  *pFree;
   if ( pFirstPhyStructure )
   {
      pFree = pFirstPhyStructure;
      pNext = pFirstPhyStructure->pNext;
      free( pFree );
      while ( pNext )
      {
         pFree = pNext;
         pNext = pNext->pNext;
         free( pFree );
      }
      pFirstPhyStructure = NULL;
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iSetAppChannelTable( char *cLogicalPinName, char *cDeviceName, char *cDefaultPinName )
{
   PHYSCIALSTRUCTURE *pPointer;
   Point pCell;
   if ( !pFirstPhyStructure )
   {
      return  - 1;
   }
   pPointer = pFirstPhyStructure;
   while ( stricmp( pPointer->cDeviceName, cDeviceName ) || stricmp( pPointer->cDefaultName, cDefaultPinName ))
   {
      pPointer = pPointer->pNext;
      if ( !pPointer )
      {
         return  - 1;
      }
   }
   pCell = MakePoint( pPointer->iColumn, pPointer->iRow );
   SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, cLogicalPinName );
   SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_USED );
   sprintf( pPointer->cOriginalName, cLogicalPinName );
   sprintf( pPointer->cActualName, cLogicalPinName );
   pPointer->cIsDefault = FALSE;
   pPointer->cIsChanged = FALSE;
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iResetAppChannelTable( int iDefaultOrOriginal )
{
   PHYSCIALSTRUCTURE *pPointer;
   Point pCell;
   pPointer = pFirstPhyStructure;
   if ( iDefaultOrOriginal == RESET )
   {
      while ( pPointer )
      {
         pCell = MakePoint( pPointer->iColumn, pPointer->iRow );
         SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cDefaultName );
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, VAL_WHITE );
         sprintf( pPointer->cActualName, "" );
         pPointer->cIsDefault = TRUE;
         pPointer->cIsChanged = FALSE;
         pPointer = pPointer->pNext;
      }
   }
   else if ( iDefaultOrOriginal == DEFAULT_RESET )
   {
      while ( pPointer )
      {
         pCell = MakePoint( pPointer->iColumn, pPointer->iRow );
         SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cDefaultName );
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, VAL_WHITE );
         sprintf( pPointer->cActualName, pPointer->cDefaultName );
         pPointer->cIsDefault = TRUE;
         pPointer->cIsChanged = TRUE;
         pPointer = pPointer->pNext;
      }
   }
   else if ( iDefaultOrOriginal == ORIGINAL )
   {
      while ( pPointer )
      {
         if ( strlen( pPointer->cOriginalName ))
         {
            pCell = MakePoint( pPointer->iColumn, pPointer->iRow );
            SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cOriginalName );
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_USED );
            sprintf( pPointer->cActualName, pPointer->cOriginalName );
            pPointer->cIsDefault = FALSE;
            pPointer->cIsChanged = FALSE;
         }
         else
         {
            pCell = MakePoint( pPointer->iColumn, pPointer->iRow );
            SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cDefaultName );
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, VAL_WHITE );
            sprintf( pPointer->cActualName, pPointer->cDefaultName );
            pPointer->cIsDefault = TRUE;
            pPointer->cIsChanged = FALSE;
         }
         pPointer = pPointer->pNext;
      }
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iResetCellValue( int iColumn, int iRow, int iDefaultOrOriginal )
{
   char cActualCellValue[85];
   char TextMsg[1024];
   PHYSCIALSTRUCTURE *pPointer;
   Point pCell;
   pPointer = pFirstPhyStructure;
   while (( pPointer->iRow != iRow ) || ( pPointer->iColumn != iColumn ))
   {
      pPointer = pPointer->pNext;
      if ( !pPointer )
      {
         return  - 1;
      }
   }
   pCell = MakePoint( pPointer->iColumn, pPointer->iRow );
   GetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_CTRL_VAL, cActualCellValue );
   switch ( iDefaultOrOriginal )
   {
      case RESET:
         SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cDefaultName );
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, VAL_WHITE );
         sprintf( TextMsg, "Cell value was set from \"%s\" to default name \"%s\"", cActualCellValue, pPointer->cDefaultName );
         sprintf( pPointer->cActualName, pPointer->cDefaultName );
         pPointer->cIsDefault = TRUE;
         pPointer->cIsChanged = FALSE;
         break;
      case DEFAULT_RESET:
         SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cDefaultName );
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, VAL_WHITE );
         sprintf( TextMsg, "Cell value was set from \"%s\" to default name \"%s\"", cActualCellValue, pPointer->cDefaultName );
         sprintf( pPointer->cActualName, pPointer->cDefaultName );
         pPointer->cIsDefault = TRUE;
         pPointer->cIsChanged = TRUE;
         break;
      case ORIGINAL:
         if ( pPointer->cIsChanged )
         {
            if ( strlen( pPointer->cOriginalName ))
            {
               SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cOriginalName );
               SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_USED );
               sprintf( TextMsg, "Cell value was set from \"%s\" to original name \"%s\"", cActualCellValue, pPointer->cOriginalName );
               sprintf( pPointer->cActualName, pPointer->cOriginalName );
               pPointer->cIsDefault = FALSE;
               pPointer->cIsChanged = FALSE;
            }
            else
            {
               SetTableCellVal( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, pPointer->cDefaultName );
               SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, pCell, ATTR_TEXT_BGCOLOR, VAL_WHITE );
               sprintf( TextMsg, "Cell value was set from \"%s\" to original (default) name \"%s\"", cActualCellValue, pPointer->cDefaultName );
               sprintf( pPointer->cActualName, pPointer->cOriginalName );
               pPointer->cIsDefault = TRUE;
               pPointer->cIsChanged = FALSE;
            }
         }
         break;
   }
   SetCtrlVal( giMainPanelHandle, MAINPANEL_STATUS_TEXT_MSG, TextMsg );
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iGetCellValues( int iColumn, int iRow, char *cDefaultName, char *cOriginalName, int *iIsDefault )
{
   PHYSCIALSTRUCTURE *pPointer;
   pPointer = pFirstPhyStructure;
   while (( pPointer->iRow != iRow ) || ( pPointer->iColumn != iColumn ))
   {
      pPointer = pPointer->pNext;
      if ( !pPointer )
      {
         return  - 1;
      }
   }
   sprintf( cOriginalName, pPointer->cOriginalName );
   sprintf( cDefaultName, pPointer->cDefaultName );
   *iIsDefault = pPointer->cIsDefault;
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
PHYSCIALSTRUCTURE *pGetNextValue( PHYSCIALSTRUCTURE *pPointer, int iAllOrChanged )
{
   pPointer = pPointer->pNext;
   if ( pPointer )
   {
      if ( iAllOrChanged == ALL )
      {
         while ( !strlen( pPointer->cActualName ))
         {
            pPointer = pPointer->pNext;
            if ( !pPointer )
            {
               return NULL;
            }
         }
      }
      else if ( iAllOrChanged == CHANGED )
      {
         while ( pPointer->cIsChanged != TRUE )
         {
            pPointer = pPointer->pNext;
            if ( !pPointer )
            {
               return NULL;
            }
         }
      }
   }
   return pPointer;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iSetCellValues( int iColumn, int iRow, char *cActualName )
{
   PHYSCIALSTRUCTURE *pPointer;
   pPointer = pFirstPhyStructure;
   while (( pPointer->iRow != iRow ) || ( pPointer->iColumn != iColumn ))
   {
      pPointer = pPointer->pNext;
      if ( !pPointer )
      {
         return  - 1;
      }
   }
   sprintf( pPointer->cActualName, cActualName );
   if ( cChannelTableCaseSensitive )
   {
      //Actual == Default (White)
      if ( !strcmp( pPointer->cActualName, pPointer->cDefaultName ) && pPointer->cIsDefault )
      {
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( iColumn, iRow ), ATTR_TEXT_BGCOLOR, VAL_WHITE );
         //Actual != Original (CELLBGCOLOUR_CHANGED -> Blue)
      }
      else if ( strcmp( pPointer->cActualName, pPointer->cOriginalName ))
      {
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( iColumn, iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_CHANGED );
         pPointer->cIsChanged = TRUE;
         pPointer->cIsDefault = FALSE;
         //Other conditions  (Yellow)
      }
      else
      {
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( iColumn, iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_USED );
      }
   }
   else
   {
      if ( !stricmp( pPointer->cActualName, pPointer->cDefaultName ) && pPointer->cIsDefault )
      {
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( iColumn, iRow ), ATTR_TEXT_BGCOLOR, VAL_WHITE );
      }
      else if ( stricmp( pPointer->cActualName, pPointer->cOriginalName ))
      {
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( iColumn, iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_CHANGED );
         pPointer->cIsChanged = TRUE;
         pPointer->cIsDefault = FALSE;
      }
      else
      {
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( iColumn, iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_USED );
      }
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iCheckBenchItems( int iAllOrChanged, int AutoApply )
{
   PHYSCIALSTRUCTURE *pPointerToCheck;
   PHYSCIALSTRUCTURE *pStartPointer;
   int iError, iIndex, iConfirm;
   int iDubColumn, iDubRow;
   int iFirst;
   char cTextBuffer[1024];
   pPointerToCheck = pFirstPhyStructure;
   giChannelTableHasAnError = FALSE;
   iFirst = 1;
   sprintf( gcErrorBuffer, "" );
   //pPointer = pGetNextValue (pPointer, iAllOrChanged);
   while ( pPointerToCheck )
   {
      iError = iCheckName( pPointerToCheck->cActualName, &iIndex );
      if ( iError )
      {
         giChannelTableHasAnError = TRUE;
         if ( iFirst )
         {
            sprintf( gcErrorBuffer, "The following logical names are not corresponding to character set of GTSL:\n\n" );
         }
         iFirst = 0;
         if ( pPointerToCheck->cIsChanged )
         {
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pPointerToCheck->iColumn, pPointerToCheck->iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_CHECKED_NOK );
         }
         sprintf( cTextBuffer, "Column: %i, Row: %i, Value: %s, Index: %i\n", pPointerToCheck->iColumn, pPointerToCheck->iRow, pPointerToCheck->cActualName, iIndex );
         strcat( gcErrorBuffer, cTextBuffer );
      }
      else
      {
         if ( pPointerToCheck->cIsChanged )
         {
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pPointerToCheck->iColumn, pPointerToCheck->iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_CHECKED_OK );
         }
      }
      pPointerToCheck = pGetNextValue( pPointerToCheck, iAllOrChanged );
   }
   pPointerToCheck = pFirstPhyStructure;
   pStartPointer = pPointerToCheck->pNext;
   while ( pPointerToCheck && pStartPointer )
   {
      iError = iCheckForDublicates( pPointerToCheck, pPointerToCheck->cActualName, &iDubColumn, &iDubRow, pStartPointer );
      if ( iError )
      {
         if ( iFirst == 0 )
         {
            strcat( gcErrorBuffer, "\n\n" );
            strcat( gcErrorBuffer, "Duplicate names:\n\n" );
            iFirst =  - 1;
         }
         else if ( iFirst == 1 )
         {
            strcat( gcErrorBuffer, "Duplicate names:\n\n" );
            iFirst =  - 1;
         }
         giChannelTableHasAnError = TRUE;
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pPointerToCheck->iColumn, pPointerToCheck->iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_CHECKED_NOK );
         SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( iDubColumn, iDubRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_CHECKED_NOK );
         sprintf( cTextBuffer, "Column: %i, Row: %i, Value: %s\n", pPointerToCheck->iColumn, pPointerToCheck->iRow, pPointerToCheck->cActualName );
         strcat( gcErrorBuffer, cTextBuffer );
         sprintf( cTextBuffer, "Column: %i, Row: %i, Value: %s\n", iDubColumn, iDubRow, pPointerToCheck->cActualName );
         strcat( gcErrorBuffer, cTextBuffer );
      }
      pPointerToCheck = pGetNextValue( pPointerToCheck, ALL );
      if ( pPointerToCheck )
      {
         pStartPointer = pPointerToCheck->pNext;
      }
   }
   giTableDataModified = FALSE;
   giTableDataChecked = TRUE;
   
   if ( giChannelTableHasAnError )
   {
      ResetTextBox( giErrorPanel, ERRORS_TEXTBOX, gcErrorBuffer );
      DisplayPanel( giErrorPanel );
      return  - 1;
   }
   else if ( !giChannelTableHasAnError && AutoApply )
   {
      iApplyChanges();
   }
   else if ( !giChannelTableHasAnError && !AutoApply )
   {
      iConfirm = ConfirmPopup( C_TITLE_MSG_POPUP, "There are no errors in changed logical names. Do want apply all changes to the current bench?" );
      if ( iConfirm )
      {
         iApplyChanges();
      }
      else
      {
         iResetAllResources( TABLE_DATA_CHECKED );
      }
   }
   
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iApplyChanges( void )
{
   int iItemExists, iStatus;
   char cTextBuffer[1024];
   PHYSCIALSTRUCTURE *pPointer;
   pPointer = pFirstPhyStructure;
   while ( pPointer )
   {
      if ( pPointer->cIsChanged )
      {
         //Delete logical name
         if ( pPointer->cIsDefault && strlen( pPointer->cOriginalName ))
         {
            iItemExists = Ini_ItemExists( gAppIniFileHandle, pPointer->cIniSection, pPointer->cOriginalName );
            if ( iItemExists )
            {
               Ini_RemoveItem( gAppIniFileHandle, pPointer->cIniSection, pPointer->cOriginalName );
            }
            sprintf( pPointer->cOriginalName, "" );
            sprintf( pPointer->cActualName, "" );
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pPointer->iColumn, pPointer->iRow ), ATTR_TEXT_BGCOLOR, VAL_WHITE );
            pPointer->cIsChanged = FALSE;
         }
         else if ( pPointer->cIsDefault && !strlen( pPointer->cOriginalName ))
         {
            sprintf( pPointer->cOriginalName, "" );
            sprintf( pPointer->cActualName, "" );
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pPointer->iColumn, pPointer->iRow ), ATTR_TEXT_BGCOLOR, VAL_WHITE );
            pPointer->cIsChanged = FALSE;
            //Insert logical name
         }
         else if ( !pPointer->cIsDefault && !strlen( pPointer->cOriginalName ))
         {
            iItemExists = Ini_ItemExists( gAppIniFileHandle, pPointer->cIniSection, pPointer->cOriginalName );
            sprintf( cTextBuffer, "%s!%s", pPointer->cDeviceName, pPointer->cDefaultName );
            iStatus = Ini_PutRawString( gAppIniFileHandle, pPointer->cIniSection, pPointer->cActualName, cTextBuffer );
            sprintf( pPointer->cOriginalName, pPointer->cActualName );
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pPointer->iColumn, pPointer->iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_USED );
            pPointer->cIsChanged = FALSE;
            //Change logical name
         }
         else if ( !pPointer->cIsDefault && strlen( pPointer->cOriginalName ))
         {
            iItemExists = Ini_ItemExists( gAppIniFileHandle, pPointer->cIniSection, pPointer->cOriginalName );
            if ( iItemExists )
            {
               Ini_RemoveItem( gAppIniFileHandle, pPointer->cIniSection, pPointer->cOriginalName );
            }
            sprintf( cTextBuffer, "%s!%s", pPointer->cDeviceName, pPointer->cDefaultName );
            iStatus = Ini_PutRawString( gAppIniFileHandle, pPointer->cIniSection, pPointer->cActualName, cTextBuffer );
            sprintf( pPointer->cOriginalName, pPointer->cActualName );
            SetTableCellAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pPointer->iColumn, pPointer->iRow ), ATTR_TEXT_BGCOLOR, CELLBGCOLOUR_USED );
            pPointer->cIsChanged = FALSE;
         }
      }
      pPointer = pPointer->pNext;
   }
   iResetAllResources( TABLE_DATA_APPLIED );
   if ( !giCorrectLicenseFound )
   {
      MessagePopup( C_TITLE_MSG_POPUP, "This software works in demo mode. You cannot apply changes to your application.ini" );
   }
   else
   {
      iStatus = Ini_WriteToFile( gAppIniFileHandle, gcTempAppIniFileName );
   }
   giAppIniChanged = TRUE;
   giTableDataChecked = FALSE;
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iCheckName( char *cName, int *iIndex )
{
   int idx, iPass;
   int iLength;
   iLength = strlen( cName );
   for ( idx = 0; idx < iLength; idx++ )
   {
      *iIndex = idx;
      iPass = isalnum( cName[idx] );
      if ( !iPass )
      {
         iPass = 0;
         if ( cName[idx] == '_' )
         {
            iPass++;
         }
         if ( cName[idx] == '.' )
         {
            iPass++;
         }
         if ( cName[idx] == '!' )
         {
            iPass++;
         }
         if ( cName[idx] == '#' )
         {
            iPass++;
         }
         if ( cName[idx] == '$' )
         {
            iPass++;
         }
         if ( cName[idx] == '%' )
         {
            iPass++;
         }
         if ( cName[idx] == '&' )
         {
            iPass++;
         }
         if ( cName[idx] == '*' )
         {
            iPass++;
         }
         if ( cName[idx] == '+' )
         {
            iPass++;
         }
         if ( cName[idx] == '-' )
         {
            iPass++;
         }
         if ( cName[idx] == '/' )
         {
            iPass++;
         }
         if ( cName[idx] == '\\' )
         {
            iPass++;
         }
         if ( cName[idx] == ':' )
         {
            iPass++;
         }
         if ( cName[idx] == '?' )
         {
            iPass++;
         }
         if ( cName[idx] == '@' )
         {
            iPass++;
         }
         if ( cName[idx] == '^' )
         {
            iPass++;
         }
         if ( cName[idx] == '|' )
         {
            iPass++;
         }
         if ( cName[idx] == '~' )
         {
            iPass++;
         }
         if ( cName[idx] == '(' )
         {
            iPass++;
         }
         if ( cName[idx] == ')' )
         {
            iPass++;
         }
         if ( cName[idx] == '{' )
         {
            iPass++;
         }
         if ( cName[idx] == '}' )
         {
            iPass++;
         }
         if ( cName[idx] == '[' )
         {
            iPass++;
         }
         if ( cName[idx] == ']' )
         {
            iPass++;
         }
         if ( cName[idx] == '<' )
         {
            iPass++;
         }
         if ( cName[idx] == '>' )
         {
            iPass++;
         }
         if ( !iPass )
         {
            return  - 1;
         }
      }
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iCheckForDublicates( PHYSCIALSTRUCTURE *pPointerToCheck, char *cName, int *iDubColumn, int *iDubRow, PHYSCIALSTRUCTURE *pStartPointer )
{
   PHYSCIALSTRUCTURE *pPointer;
   pPointer = pStartPointer;
   if ( cChannelTableCaseSensitive )
   {
      while ( pPointer )
      {
         if ( !strlen( pPointer->cActualName ))
         {
            pPointer = pPointer->pNext;
         }
         else
         {
            if ( !strcmp( cName, pPointer->cActualName ))
            {
               *iDubColumn = pPointer->iColumn;
               *iDubRow = pPointer->iRow;
               return  - 1;
            }
            pPointer = pPointer->pNext;
         }
      }
   }
   else
   {
      while ( pPointer )
      {
         if ( !strlen( pPointer->cActualName ))
         {
            pPointer = pPointer->pNext;
         }
         else
         {
            if ( !stricmp( cName, pPointer->cActualName ))
            {
               *iDubColumn = pPointer->iColumn;
               *iDubRow = pPointer->iRow;
               return  - 1;
            }
            pPointer = pPointer->pNext;
         }
      }
   }
   return 0;
}
/**************************************************************************/
/*                                                                        */
/**************************************************************************/
int iSetChannelSection( char *cAnalogSection, char *cDioSection )
{
   PHYSCIALSTRUCTURE *pPointer;
   pPointer = pFirstPhyStructure;
   while ( pPointer )
   {
      if ( !strcmp( pPointer->cType, "PDFT" ) && strlen( cDioSection ) && pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cDioSection );
      }
      else if ( !strcmp( pPointer->cType, "PDFT" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      else if ( !strcmp( pPointer->cType, "PIO3B" ) && strlen( cDioSection ) && pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cDioSection );
      }
      else if ( !strcmp( pPointer->cType, "PIO3B" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      else if ( !strcmp( pPointer->cType, "PMB" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      else if ( !strcmp( pPointer->cType, "PSM1" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      else if ( !strcmp( pPointer->cType, "PSM2" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      else if ( !strcmp( pPointer->cType, "PAM" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      else if ( !strcmp( pPointer->cType, "PSAM" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      else if ( !strcmp( pPointer->cType, "PSU" ) && strlen( cAnalogSection ) && !pPointer->cIsDigital )
      {
         sprintf( pPointer->cIniSection, cAnalogSection );
      }
      pPointer = pPointer->pNext;
   }
   return 0;
}

/**************************************************************************/
/*                                                                        */
/**************************************************************************/

int iSaveAppIni( char *cSavingPathName )
{
   int iConfirm, iError;
   if ( !giCorrectLicenseFound )
   {
      MessagePopup( C_TITLE_MSG_POPUP, "This software works in demo mode. You cannot save your application.ini" );
      return 0;
   }
   if ( giTableDataModified )
   {
      iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "You have changed the values for the logical names. Would you apply the changes?", "Yes", "No", "Cancel", NULL, 0, 0, VAL_GENERIC_POPUP_BTN1,
         VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
      //User clicked "YES"
      if ( iConfirm == 1 )
      {
         iError = iCheckBenchItems( CHANGED, TRUE );
         if ( iError )
         {
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
         return 0;
      }
      iResetAllResources( TABLE_DATA_RESET );
   }
   if ( giFreeTextDataModified )
   {
      iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "You have changed the text of your application.ini. Would you apply the changes?", "Yes", "No", "Cancel", NULL, 0, 0, VAL_GENERIC_POPUP_BTN1,
         VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
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
         return 0;
      }
   }
   CopyFile( gcTempAppIniFileName, cSavingPathName );
   giAppIniChanged = TRUE;
   return 0;
}

/**************************************************************************/
/*                                                                        */
/**************************************************************************/

int iCheckVariableBeforeClosing( void )
{
   char cTextBuffer[1024];
   int iConfirm, iError;
   if ( giCorrectLicenseFound )
   {
    if ( giTableDataModified )
      {
         iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "You have changed the values for the logical names. Would you apply the changes and save application.ini?", "Yes", "No", "Cancel", NULL, 0,
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
               RunUserInterface();
               return 0;
            }
            if ( giTracingEnabled )
            {
               WriteToLogFile( "copy temp file" );
            }
            CopyFile( gcTempAppIniFileName, gcAppIniFileName );
            if ( giTracingEnabled )
            {
               WriteToLogFile( "dispose app ini handle" );
            }
            Ini_Dispose( gAppIniFileHandle );
            gAppIniFileHandle = NULL;
            if ( giTracingEnabled )
            {
               WriteToLogFile( "delete temp file" );
            }
            DeleteFile( gcTempAppIniFileName );
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
            return  - 1;
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
		 return  - 1;
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
         iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "The content of your application.ini was checked but not applied. Would you apply and save the application.ini?", "Yes", "No", "Cancel",
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
            CopyFile( gcTempAppIniFileName, gcAppIniFileName );
            if ( giTracingEnabled )
            {
               WriteToLogFile( "dispose app ini handle" );
            }
            Ini_Dispose( gAppIniFileHandle );
            gAppIniFileHandle = NULL;
            if ( giTracingEnabled )
            {
               WriteToLogFile( "delete temp file" );
            }
            DeleteFile( gcTempAppIniFileName );
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
            return  - 1;
         }
      }
      else if ( giAppIniChanged )
      {
         iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "The content of your application.ini was changed. Would you save the application.ini?", "Yes", "No", "Cancel", NULL, 0, 0,
            VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
         //User clicked "YES"
         if ( iConfirm == 1 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "app ini is changed and user clicked yes" );
            }
            if ( giTracingEnabled )
            {
               WriteToLogFile( "copy temp file" );
            }
            CopyFile( gcTempAppIniFileName, gcAppIniFileName );
            if ( giTracingEnabled )
            {
               WriteToLogFile( "dispose app ini handle" );
            }
            Ini_Dispose( gAppIniFileHandle );
            gAppIniFileHandle = NULL;
            if ( giTracingEnabled )
            {
               WriteToLogFile( "delete temp file" );
            }
            DeleteFile( gcTempAppIniFileName );
            //User clicked "No"
         }
         else if ( iConfirm == 2 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "app ini is changed and user clicked no" );
            }
            //Do nothing
            iResetAllResources( APP_INI_SAVED );
            Delay( 0.1 );
            //User clicked "Cancel"
         }
         else if ( iConfirm == 3 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "app ini is changed and user clicked cancel" );
            }
            return  - 1;
         }
      }
      else if ( giFreeTextDataModified )
      {
         iConfirm = GenericMessagePopup( C_TITLE_MSG_POPUP, "You have changed the text of your application.ini. Would you apply the changes?", "Yes", "No", "Cancel", NULL, 0, 0,
            VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3 );
         //User clicked "YES"
         if ( iConfirm == 1 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "free text of app ini is changed and user clicked yes" );
            }
            iSaveFreeText();
            if ( giTracingEnabled )
            {
               WriteToLogFile( "copy temp file" );
            }
            CopyFile( gcTempAppIniFileName, gcAppIniFileName );
            if ( giTracingEnabled )
            {
               WriteToLogFile( "dispose app ini handle" );
            }
            Ini_Dispose( gAppIniFileHandle );
            gAppIniFileHandle = NULL;
            if ( giTracingEnabled )
            {
               WriteToLogFile( "delete temp file" );
            }
            DeleteFile( gcTempAppIniFileName );
            //User clicked "Cancel"
            iResetAllResources( FREE_TEXT_RESET );
         }
         else if ( iConfirm == 2 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "free text of app ini is changed and user clicked no" );
            }
            //Do nothing
            iResetAllResources( FREE_TEXT_RESET );
            Delay( 0.1 );
            //User clicked "Cancel"
         }
         else if ( iConfirm == 3 )
         {
            if ( giTracingEnabled )
            {
               WriteToLogFile( "free text of app ini is changed and user clicked cancel" );
            }
            return  - 1;
         }
      }
   }
   
   
   iResetAllResources( PHY_LOADED );
   if ( HIDEPANEL )
   {
      HidePanel( giMainPanelHandle );
   }
   if ( DIMMEDTABLE )
   {
      SetCtrlAttribute( giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, ATTR_DIMMED, TRUE );
   }
   ProcessDrawEvents();
   iResetAppChannelTable(RESET);
   sprintf( cTextBuffer, "Selected application.ini:" );
   SetCtrlVal( giMainPanelHandle, MAINPANEL_INF_APPINI, cTextBuffer );
   if (gAppIniFileHandle) Ini_Dispose( gAppIniFileHandle );
   gAppIniFileHandle = NULL;
   if (strlen(gcTempAppIniFileName)) DeleteFile( gcTempAppIniFileName );
   
   giDefaultDataLoaded = TRUE;
   giAppIniDataLoaded = FALSE;
   giTableDataModified = FALSE;
   giTableDataChecked = FALSE;
   giFreeTextDataModified = FALSE;
   giChannelTableHasAnError = FALSE;
   giAppIniChanged = FALSE;
   cChannelTableCaseSensitive = FALSE;
   sprintf( gcAppIniFileName, "" );
   sprintf( gcTempAppIniFileName, "" );
   sprintf( gcErrorBuffer, "" );
   sprintf( gcSelectedBench, "" );
   ResetTextBox( giTabPanelHandleFreeText, FREETEXT_FREETEXT, "..." );
   SetActiveTabPage( giMainPanelHandle, MAINPANEL_TAB, 0 );
   
   
   
   
   
   return 0;
}

int CVICALLBACK ContinueDublicate (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char cNewBenchName[1024];
	char cStartPMB[1024];
	char cStartPin[1024];
	char cDubStartPMB[1024];
	char cDubStartPin[1024];
	
	char cTextBuffer[1024];
	
	//PHYSCIALSTRUCTURE *pFirstPhyStructure;
	PHYSCIALSTRUCTURE *pStartPMB;
	PHYSCIALSTRUCTURE *pStartDubPMB;

	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal(giDubPanelHandle, DUBPLICATE_NEWBENCHNAME, cNewBenchName);
			GetCtrlVal(giDubPanelHandle, DUBPLICATE_START_PMB, cStartPMB);
			GetCtrlVal(giDubPanelHandle, DUBPLICATE_START_PMB_PIN, cStartPin);
			GetCtrlVal(giDubPanelHandle, DUBPLICATE_DUBSTART_PMB, cDubStartPMB);
			GetCtrlVal(giDubPanelHandle, DUBPLICATE_DUBSTART_PMB_PIN, cDubStartPin);
			
			pStartPMB = pFirstPhyStructure;
			while (strcmp(pStartPMB->cDeviceName, cStartPMB) || strcmp(pStartPMB->cDefaultName, cStartPin))
				pStartPMB = pStartPMB->pNext;	
			
			pStartDubPMB = pFirstPhyStructure;
			while (strcmp(pStartDubPMB->cDeviceName, cDubStartPMB) || strcmp(pStartDubPMB->cDefaultName, cDubStartPin))
				pStartDubPMB = pStartDubPMB->pNext;	
			
			while (strcmp(pStartPMB->cDeviceName, cDubStartPMB) || strcmp(pStartPMB->cDefaultName, cDubStartPin))
			{
				//sprintf(pStartDubPMB->cActualName, pStartPMB->cOriginalName);
				//sprintf(pStartDubPMB->cIniSection, cNewBenchName);    
				//SetTableCellVal (giTabPanelHandleLogicalNames, LOGICAL_LOGICAL_NAMES, MakePoint( pStartDubPMB->iColumn, pStartDubPMB->iRow ), pStartDubPMB->cActualName);
				//iSetCellValues( pStartDubPMB->iColumn, pStartDubPMB->iRow, pStartDubPMB->cActualName );     
				
				sprintf(cTextBuffer,  "%s = %s!%s\n", pStartPMB->cOriginalName,  pStartDubPMB->cDeviceName, pStartDubPMB->cDefaultName);
				SetCtrlVal(panel, DUBPLICATE_TEXTBOX, cTextBuffer);
				pStartPMB = pStartPMB->pNext;
				pStartDubPMB = pStartDubPMB->pNext;	
			}
			
			
			
			break;
	}
	return 0;
}

int CVICALLBACK CancelDubplicate (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			RemovePopup(giDubPanelHandle);
			break;
	}
	return 0;
}
