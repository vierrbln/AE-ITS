/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  DUBPLICATE                       1
#define  DUBPLICATE_NEWBENCHNAME          2       /* control type: string, callback function: (none) */
#define  DUBPLICATE_DUBSTART_PMB_PIN      3       /* control type: ring, callback function: (none) */
#define  DUBPLICATE_DUBSTART_PMB          4       /* control type: ring, callback function: (none) */
#define  DUBPLICATE_START_PMB_PIN         5       /* control type: ring, callback function: (none) */
#define  DUBPLICATE_START_PMB             6       /* control type: ring, callback function: (none) */
#define  DUBPLICATE_CANCEL                7       /* control type: command, callback function: CancelDubplicate */
#define  DUBPLICATE_CONTINUE              8       /* control type: command, callback function: ContinueDublicate */
#define  DUBPLICATE_TEXTBOX               9       /* control type: textBox, callback function: (none) */

#define  ERRORS                           2       /* callback function: ErrorPanelCallback */
#define  ERRORS_TEXTBOX                   2       /* control type: textBox, callback function: (none) */
#define  ERRORS_CLOSE                     3       /* control type: command, callback function: CloseErrorWindow */

#define  LEGEND                           3       /* callback function: LegendCallBack */
#define  LEGEND_TEXTMSG                   2       /* control type: textMsg, callback function: (none) */
#define  LEGEND_TEXTMSG_2                 3       /* control type: textMsg, callback function: (none) */
#define  LEGEND_TEXTMSG_6                 4       /* control type: textMsg, callback function: (none) */
#define  LEGEND_TEXTMSG_3                 5       /* control type: textMsg, callback function: (none) */
#define  LEGEND_TEXTMSG_4                 6       /* control type: textMsg, callback function: (none) */
#define  LEGEND_TEXTMSG_5                 7       /* control type: textMsg, callback function: (none) */
#define  LEGEND_HIDE                      8       /* control type: command, callback function: HideLegend */
#define  LEGEND_DECORATION_5              9       /* control type: command, callback function: (none) */
#define  LEGEND_DECORATION_4              10      /* control type: command, callback function: (none) */
#define  LEGEND_DECORATION_3              11      /* control type: command, callback function: (none) */
#define  LEGEND_DECORATION_1              12      /* control type: command, callback function: (none) */
#define  LEGEND_DECORATION_2              13      /* control type: command, callback function: (none) */
#define  LEGEND_DECORATION                14      /* control type: command, callback function: (none) */

#define  MAINPANEL                        4       /* callback function: MainPanelCallback */
#define  MAINPANEL_INF_APPINI             2       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_INF_PHYINI             3       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_DECORATION             4       /* control type: deco, callback function: (none) */
#define  MAINPANEL_DECORATION_2           5       /* control type: deco, callback function: (none) */
#define  MAINPANEL_TAB                    6       /* control type: tab, callback function: MainTabCallBack */
#define  MAINPANEL_STATUS_TEXT_MSG        7       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_2              8       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TITEL2                 9       /* control type: textMsg, callback function: (none) */

#define  REGISTER                         5       /* callback function: RegisterPanelCallback */
#define  REGISTER_NAME                    2       /* control type: string, callback function: RegistrationValueChanged */
#define  REGISTER_COMPANY                 3       /* control type: string, callback function: RegistrationValueChanged */
#define  REGISTER_PHONE                   4       /* control type: string, callback function: RegistrationValueChanged */
#define  REGISTER_EMAIL                   5       /* control type: string, callback function: RegistrationValueChanged */
#define  REGISTER_COPYTOCLIPBOARD         6       /* control type: command, callback function: CopyTextToClipBoard */
#define  REGISTER_CLOSE                   7       /* control type: command, callback function: CloseRegisterPanel */
#define  REGISTER_INSTALLLIC              8       /* control type: command, callback function: InstallLicFile */
#define  REGISTER_TEXTBOX                 9       /* control type: textBox, callback function: (none) */

     /* tab page panel controls */
#define  FREETEXT_FREETEXT                2       /* control type: textBox, callback function: FreeTextBoxCallback */

     /* tab page panel controls */
#define  LOGICAL_SELECTBENCCH             2       /* control type: ring, callback function: SelectBench */
#define  LOGICAL_LOGICAL_NAMES            3       /* control type: table, callback function: TableCallBack */
#define  LOGICAL_MODULES                  4       /* control type: tree, callback function: ModulTreeCallBack */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_FILE                     2
#define  MENUBAR_FILE_SETPHYINI           3       /* callback function: SetPhyIni */
#define  MENUBAR_FILE_SEPARATOR           4
#define  MENUBAR_FILE_OPENAPPINI          5       /* callback function: OpenAppIni */
#define  MENUBAR_FILE_SEPARATOR_6         6
#define  MENUBAR_FILE_SAVEAPPINI          7       /* callback function: SaveAppIni */
#define  MENUBAR_FILE_SAVEAPPINIAS        8       /* callback function: SaveAppIniAs */
#define  MENUBAR_FILE_CLOSEAPPINI         9       /* callback function: CloseAppIni */
#define  MENUBAR_FILE_SEPARATOR_2         10
#define  MENUBAR_FILE_Exit                11      /* callback function: Exit */
#define  MENUBAR_EDIT                     12
#define  MENUBAR_EDIT_RESET               13
#define  MENUBAR_EDIT_RESET_SUBMENU       14
#define  MENUBAR_EDIT_RESET_DEFAULCELLVAL 15      /* callback function: SetDefaultCellValue */
#define  MENUBAR_EDIT_RESET_DEFAULTVALUEALLDCELLS 16 /* callback function: SetAllDefaultCellValues */
#define  MENUBAR_EDIT_RESET_SEPARATOR_3   17
#define  MENUBAR_EDIT_RESET_ORIGINALCELLVAL 18    /* callback function: SetOriginalCellValue */
#define  MENUBAR_EDIT_RESET_ORIGINAVALUEALLDCELLS 19 /* callback function: SetAllOriginalCellValues */
#define  MENUBAR_EDIT_SEPARATOR_4         20
#define  MENUBAR_EDIT_CHECKTABLE          21      /* callback function: CheckTable */
#define  MENUBAR_EDIT_SHOWERROR           22      /* callback function: ShowErrorList */
#define  MENUBAR_EDIT_SEPARATOR_5         23
#define  MENUBAR_EDIT_APPLYTABLE          24      /* callback function: ApplyChanges */
#define  MENUBAR_EDIT_SEPARATOR_8         25
#define  MENUBAR_EDIT_DUBPLICATE          26      /* callback function: DublicateBench */
#define  MENUBAR_EDITFREETEXT             27
#define  MENUBAR_EDITFREETEXT_APPLYTABLE  28      /* callback function: ApplyChangesText */
#define  MENUBAR_HELP                     29
#define  MENUBAR_HELP_HELP                30      /* callback function: OpenOnlineHelp */
#define  MENUBAR_HELP_LEGEND              31      /* callback function: ShowLegend */
#define  MENUBAR_HELP_SEPARATOR_7         32
#define  MENUBAR_HELP_ABOUT               33      /* callback function: ShowSplash */
#define  MENUBAR_HELP_REGISTER            34      /* callback function: ShowRegistorPanel */


     /* Callback Prototypes: */

void CVICALLBACK ApplyChanges(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK ApplyChangesText(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK CancelDubplicate(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK CheckTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CloseAppIni(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK CloseErrorWindow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CloseRegisterPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ContinueDublicate(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CopyTextToClipBoard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK DublicateBench(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ErrorPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Exit(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK FreeTextBoxCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK HideLegend(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK InstallLicFile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LegendCallBack(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MainPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MainTabCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModulTreeCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK OpenAppIni(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OpenOnlineHelp(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK RegisterPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RegistrationValueChanged(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK SaveAppIni(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK SaveAppIniAs(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK SelectBench(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK SetAllDefaultCellValues(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK SetAllOriginalCellValues(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK SetDefaultCellValue(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK SetOriginalCellValue(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK SetPhyIni(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK ShowErrorList(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK ShowLegend(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK ShowRegistorPanel(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK ShowSplash(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK TableCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
