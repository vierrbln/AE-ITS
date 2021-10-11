#include <windows.h>
#include <ansi_c.h>
#include <winbase.h>
#include <cvirte.h>		
#include <userint.h>
#include "AE.h"
#include "Splash.h"
#include <utility.h>
#include "inifile.h"


#define DEBUG 0

#define VERSION "0.1.0.0"

#define TRUE 1
#define FALSE 0

#define SUCCESS 0

#define HIDEPANEL 0
#define DIMMEDTABLE 1

#define RESET 0
#define DEFAULT_RESET 1
#define ORIGINAL 2
#define CHANGED 3
#define ALL 4

#define RESET_GUI_FULL 1000
#define PHY_LOADED 1001
#define APP_LOADED 1002
#define TABLE_DATA_RESET 1003
#define TABLE_DATA_MODIFIED 1004
#define TABLE_DATA_CHECKED 1005
#define TABLE_DATA_APPLIED 1006
#define FREE_TEXT_MODIFIED 1007
#define FREE_TEXT_RESET 1008
#define APP_INI_CHANGED 1009
#define APP_INI_SAVED 1010

#define C_TITLE_MSG_POPUP_ERROR "AE-ITS ApplicationEditor - Error"
#define C_TITLE_MSG_POPUP "AE-ITS ApplicationEditor"

#define CELLBGCOLOUR_USED 0xFFFD9C
#define CELLBGCOLOUR_CHANGED 0xB8FEFF 
#define CELLBGCOLOUR_CHECKED_OK 0xA6FFA7
#define CELLBGCOLOUR_CHECKED_NOK 0xFFD6D6
#define CELLBGCOLOUR_INDICATOR 0xE8E8E8


typedef struct PhysicalStructure
{
   char cIniSection[256];
   char cType[10];
   char cDeviceName[82];
   char cDefaultName[82];
   char cOriginalName[82];
   char cActualName[82];
   int iColumn;
   int iRow;
   char cIsChanged;
   char cIsDefault;
   char cIsDigital;
   struct PhysicalStructure *pNext;
} PHYSCIALSTRUCTURE;


LPTSTR lpVolumeNameBuffer; // volume name buffer
DWORD nVolumeNameSize; // length of name buffer
DWORD lpVolumeSerialNumber; // volume serial number
DWORD lpMaximumComponentLength; // maximum file name length
DWORD lpFileSystemFlags; // file system options
LPTSTR lpFileSystemNameBuffer; // file system name buffer
DWORD nFileSystemNameSize;
BOOL error;
DWORD errorCode;


FILE *pLogFile;


int giMainPanelHandle;
int giDubPanelHandle;
int giTabPanelHandleLogicalNames;
int giTabPanelHandleFreeText;
int giMenuBarHandle;
int gSplash;
int giErrorPanel;
int giRegistrationPanel;
int giLegendPanel;

int giDefaultDataLoaded;
int giAppIniDataLoaded;
int giTableDataModified;
int giFreeTextDataModified;
int giTableDataChecked;
int giAppIniChanged;
int giChannelTableHasAnError;
int giCorrectLicenseFound;
int giTracingEnabled;
int giShowOnlyApplicationModules;
unsigned int cChannelTableCaseSensitive;

char gcPhysicalIniFileName[1024];
char gcAppIniFileName[1024];
char gcLastUsedAppIniFileName[1024];
char gcTempAppIniFileName[1024];
char gcErrorBuffer[200000];
char gcSelectedBench[1024];
char gcSystemID[1024];
int giFrameSettings[5][17];

PHYSCIALSTRUCTURE *pFirstPhyStructure;

IniText gPhysicalIniFileHandle;
IniText gAppIniFileHandle;

int iLoadAppEditIniFile( void );
int iSaveAppEditIniFile( void );
int iLoadDefaultDataIntoTable( void );
int iLoadBenchDataIntoTable( void );
int iLoadFreeText( void );
int iSaveFreeText( void );
int iLoadBenches( void );
int iResetAllResources( int iType );
int iSetTableCellValue( Point pCell, int iHotOrIndicator, char *cDefaultName, char *cDeviceName, char *cTypeValue, char cIsDigital );
int iAppendPinToPinList( char *cType, char *cDeviceSection, char *cDefaultName, char cIsDigital, int iColumn, int iRow );
int iSetChannelSection( char *cAnalogSection, char *cDioSection );
int iSetAppChannelTable( char *cLogicalPinName, char *cDeviceName, char*cDefaultPinName );
int iResetAppChannelTable( int iDefaultOrOriginal );
int iResetCellValue( int iColumn, int iRow, int iDefaultOrOriginal );
int iGetCellValues( int iColumn, int iRow, char *cDefaultName, char*cOriginalName, int *iIsDefault );
PHYSCIALSTRUCTURE *pGetNextValue( PHYSCIALSTRUCTURE *pPointer, int iAllOrChanged );
int iSetCellValues( int iColumn, int iRow, char *cActualName );
int iResetPinList( void );
int iFreePinList( void );
int iCheckBenchItems( int iOriginalOrChanged, int iAutoApply );
int iApplyChanges( void );
int iCheckName( char *cName, int *iIndex );
int iCheckForDublicates( PHYSCIALSTRUCTURE *pPointerToCheck, char *cName, int*iDubColumn, int *iDubRow, PHYSCIALSTRUCTURE *pStartPointer );
int iSaveAppIni( char *cSavingPathName );
int iCheckVariableBeforeClosing( void );

//utility.c
int iOpenLogFile( void );
int iOpenApplicationIniFile(void);
int WriteToLogFile( char *cTextBuffer );
int iCloseLogFile( void );
int iUpdateRegistrationText( void );
short sCheckGTSLError( short sErrorOccurred, long lErrorCode, char *cErrorMessage, char *cFunctionName );
int iResizeUserInterface( void );
