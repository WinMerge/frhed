#ifndef __midl
#include <windows.h>
#include <commctrl.h>
#define IDC_STATIC (-1)
#endif

#define IDC_UP                          100
#define IDC_DOWN                        101
#define IDR_MAINMENU                    102
#define IDR_ACCELERATOR1                103
#define IDR_CONTEXTMENU                 104
#define IDD_REVERSE_BYTES_DIALOG        105
#define IDD_GOTODIALOG                  106
#define IDD_MULTIDND_DIALOG             107
#define IDD_FINDDIALOG                  108
#define IDI_FRHED                       109
#define IDD_ABOUTDIALOG                 111
#define IDD_DELETEDIALOG                112
#define IDD_HEXDUMPDIALOG               113
#define IDD_DECIMALDIALOG               115
#define IDD_PASTEDIALOG                 116
#define IDD_CUTDIALOG                   117
#define IDD_COPYDIALOG                  118
#define IDD_VIEWSETTINGSDIALOG          119
#define IDD_APPENDDIALOG                120
#define IDD_MANIPBITSDIALOG             121
#define IDD_CHARACTERSETDIALOG          122
#define IDD_CHOOSEDIFFDIALOG            123
#define IDD_BINARYMODEDIALOG            124
#define IDD_SELECT_BLOCK_DIALOG         125
#define IDD_ADDBMK_DIALOG               126
#define IDD_REMOVEBMK_DIALOG            127
#define IDD_OPEN_PARTIAL_DIALOG         128
#define IDD_FASTPASTE_DIALOG            129
#define IDD_TMPL_RESULT_DIALOG          130
#define IDD_MOVE_COPY                   131
#define IDD_REPLACEDIALOG               132
#define IDD_DRAGDROP                    133
#define IDD_DRAG_DROP                   133
#define IDD_FILL_WITH                   134
#define IDD_ENCODE_DECODE_DIALOG        135
#define IDD_OPEN_DRIVE_DIALOG           136
#define IDD_GOTO_TRACK_DIALOG           137
#define IDD_SHORTCUTS                   138
#define IDD_CHANGEINST                  140
#define IDB_TOOLBAR                     141
#define IDC_REPLACEWITH_EDIT            142
#define IDD_DRAG_DROP_OPTIONS           143
#define IDM_ZOOMIN                      144
#define IDM_ZOOMOUT                     145
#define IDM_ZOOMNORMAL                  146
#define IDC_DRAG_CF_TEXT                147
#define IDC_TEXT_SPECIAL                148
#define IDC_DRAG_RTF                    149
#define IDC_AND                         151
#define IDC_DROP_CF_TEXT                152
#define IDC_ES                          154
#define IDC_EXPORTRTF                   155
#define IDC_SS                          156
#define IDC_EN_SD_DD                    156
#define IDC_EN_SD_SEL                   157
#define IDC_SI                          158
#define IDC_DROP_CF_HDROP               158
#define IDC_IFS                         161
#define IDC_R                           163
#define IDC_LEN                         164
#define IDC_XOR                         165
#define IDC_FORWARD                     166
#define IDC_ABOUT_VER                   167
#define IDC_FINDNEXT_BUTTON             171
#define IDC_TYPE                        172
#define IDC_FINDPREVIOUS_BUTTON         173
#define IDC_BROWSE                      174
#define IDC_MATCHCASE_CHECK             175
#define IDC_FN                          176
#define IDC_REPLACE_BUTTON              177
#define IDC_HEXSTAT                     178
#define IDC_FOLLOCC_BUTTON              179
#define IDC_PREVOCC_BUTTON              180
#define IDC_STS                         181
#define IDC_TO_REPLACE_EDIT             182
#define IDC_USETRANSLATION_CHECK        183
#define IDC_INSTS                       184
#define IDCOPY                          185
#define IDC_LINKS                       186
#define IDC_INSTDATA                    187
#define IDC_MRU                         188
#define IDC_OTHEREND                    189
#define IDC_FPOS                        190
#define IDC_HEX                         191
#define IDC_LPOS                        192
#define IDC_FILESTAT                    193
#define IDC_EQ                          194
#define IDC_OR                          195
#define IDC_EXPORTDISPLAY               196
#define IDC_LINST                       197
#define IDC_EDIT0                       198
#define IDC_SINST                       199
#define IDC_ADD                         200
#define IDC_DELETE                      201
#define IDC_MOVE                        202
#define IDC_UPDATE                      203
#define IDC_FIND_AND_FIX                204
#define IDC_SENDTO                      205
#define IDC_DESKTOP                     206
#define IDC_START                       207
#define IDC_RELOAD                      208
#define IDC_PROGRAMS                    209
#define IDC_DISPLAY                     211
#define IDC_VERS                        212
#define IDC_READ                        213
#define IDC_COPY                        214
#define IDC_1STOFFSET                   215
#define IDC_2NDDELIM                    216
#define IDC_MOVEMENT                    217
#define IDC_REFRESH                     218
#define IDM_OPEN                        219
#define IDM_NEW                         220
#define IDM_SCROLL_LEFT                 221
#define IDM_SCROLL_RIGHT                222
#define IDM_SCROLL_UP                   223
#define IDM_SCROLL_DOWN                 224
#define IDM_SAVE                        225
#define IDM_SAVE_AS                     226
#define IDM_EXIT                        227
#define IDM_CHANGE_MODE                 228
#define IDM_FIND                        229
#define IDM_GO_TO                       230
#define IDM_ABOUT                       231
#define IDM_EDIT_COPY                   232
#define IDM_EDIT_PASTE                  233
#define IDM_COPY_HEXDUMP                234
#define IDM_EDIT_ENTERDECIMALVALUE      235
#define IDM_HELP_TOPICS                 236
#define IDM_EDIT_CUT                    237
#define IDM_INTERNALSTATUS              238
#define IDM_VIEW_SETTINGS               239
#define IDM_TEXT_COLOR                  240
#define IDM_BK_COLOR                    241
#define IDM_EDIT_APPEND                 242
#define IDM_EDIT_MANIPULATEBITS         243
#define IDM_CHARACTER_SET               244
#define IDA_DELETEKEY                   245
#define IDA_INSERTMODETOGGLE            246
#define IDA_BACKSPACE                   247
#define IDM_SELECT_ALL                  248
#define IDM_PROPERTIES                  249
#define IDM_READFLOAT                   250
#define IDM_COMPARE                     251
#define IDM_BINARYMODE                  252
#define IDM_SCROLL_NEXT                 253
#define IDM_SCROLL_PRIOR                254
#define IDM_SELECT_BLOCK                255
#define IDM_SEP_COLOR                   256
#define IDM_ADDBOOKMARK                 257
#define IDM_BOOKMARK1                   258
#define IDM_BOOKMARK2                   259
#define IDM_BOOKMARK3                   260
#define IDM_BOOKMARK4                   261
#define IDM_BOOKMARK5                   262
#define IDM_BOOKMARK6                   263
#define IDM_BOOKMARK7                   264
#define IDM_BOOKMARK8                   265
#define IDM_BOOKMARK9                   266
#define IDM_REMOVE_BKM                  267
#define IDM_CLEARALL_BMK                268
#define IDM_PARTIAL_OPEN                269
#define IDM_PASTE_WITH_DLG              270
#define IDM_MRU1                        271
#define IDM_MRU2                        272
#define IDM_MRU3                        273
#define IDM_MRU4                        274
#define IDM_MRU5                        275
#define IDM_MRU6                        276
#define IDM_MRU7                        277
#define IDM_MRU8                        278
#define IDM_MRU9                        279
#define IDM_APPLYTEMPLATE               280
#define IDM_EDIT_READONLYMODE           281
#define IDM_RESET_COLORS                282
#define IDM_SELTEXT_COLOR               283
#define IDM_SELBACK_COLOR               284
#define IDM_BMK_COLOR                   285
#define IDM_FINDNEXT                    286
#define IDM_FINDPREV                    287
#define IDM_OPEN_TEXT                   288
#define IDM_ADOPT_COLOURS               289
#define IDM_EXPLORERSETTINGS            290
#define IDM_REPLACE                     291
#define IDM_FILL_WITH                   292
#define IDM_EDIT_REVERSE                293
#define IDM_SAVESELAS                   294
#define IDM_EDIT_MOVE_COPY              295
#define IDM_REVERT                      296
#define IDM_INSERTFILE                  297
#define IDM_DELETEFILE                  298
#define ID_MISC_GOTO_DLL_EXPORTS        299
#define ID_MISC_GOTO_DLL_IMPORTS        300
#define ID_PE_SHOW_DEPENDENCIES         301
#define ID_MISC_ENCODEDECODE            302
#define ID_MISC_XOR1                    303
#define ID_DISK_OPEN_DRIVE              304
#define ID_DISK_GOTONEXTTRACK           305
#define ID_DISK_GOTOPREVIOUSTRACK       306
#define ID_DISK_GOTOTRACK               307
#define ID_DISK_READMFT                 308
#define ID_DISK_GOTOFIRSTTRACK          309
#define ID_DISK_GOTOLASTTRACK           310
#define IDM_OPEN_HEXDUMP                311
#define IDM_MAKE_BACKUPS                312
#define IDM_CHANGEINST                  313
#define IDM_CONTEXT                     314
#define IDM_UNKNOWN                     315
#define IDM_DEFAULT                     316
#define IDM_SAVEINI                     317
#define IDM_SHORTCUTS                   320
#define ID_DISK_CLOSEDRIVE              321
#define IDC_MANIPBITS                   322
#define IDC_NUMDIFFS                    323
#define IDC_ABOUTCONTRIBS               324
#define IDC_ABOUT_URL                   325
#define IDC_ABOUT_OPENURL               326
#define IDC_GOTO_OFFSET                 327
#define IDC_FIND_TEXT                   328
#define IDC_FIND_MATCHCASE              329
#define IDC_FIND_UNICODE                330
#define IDC_FIND_UP                     331
#define IDC_FIND_DOWN                   332
#define IDC_HEXDUMP_OFFSET              333
#define IDC_HEXDUMP_OFFSET2             334
#define IDC_HEXDUMP_EXPORTFILE          335
#define IDC_HEXDUMP_EXPORTCLIPB         336
#define IDC_DECIMAL_VALUE               337
#define IDC_DECIMAL_OFFSET              338
#define IDC_DECIMAL_TIMES               339
#define IDC_DECIMAL_BYTE                340
#define IDC_DECIMAL_WORD                341
#define IDC_DECIMAL_DWORD               342
#define IDC_PASTE_CLIPBOARD             343
#define IDC_PASTE_OVERWRITE             344
#define IDC_PASTE_INSERT                345
#define IDC_PASTE_TIMES                 346
#define IDC_PASTE_BINARY                347
#define IDC_PASTE_SKIPBYTES             348
#define IDC_CUT_STARTOFFSET             349
#define IDC_CUT_INCLUDEOFFSET           350
#define IDC_CUT_NUMBYTES                351
#define IDC_CUT_NUMBEROFBYTES           352
#define IDC_CUT_ENDOFFSET               353
#define IDC_COPY_STARTOFFSET            355
#define IDC_COPY_OFFSET                 356
#define IDC_COPY_BYTES                  357
#define IDC_COPY_OFFSETEDIT             358
#define IDC_COPY_BYTECOUNT              359
#define IDC_SETTINGS_BYTESPERLINE       360
#define IDC_SETTINGS_ADJUST_BYTELINE    361
#define IDC_SETTINGS_OFFSETLEN          362
#define IDC_SETTINGS_ADJOFFSET          363
#define IDC_SETTINGS_CARETUNSIGN        364
#define IDC_SETTINGS_CARETSIGN          365
#define IDC_SETTINGS_OPENRO             366
#define IDC_SETTINGS_EDITOR             367
#define IDC_SETTINGS_LANGUAGE           368
#define IDC_APPEND_BYTES                369
#define IDC_CHSET_ANSI                  370
#define IDC_CHSET_OEM                   371
#define IDC_CHSET_FONTSIZE              372
#define IDC_CHOOSEDIFF_FSIZES           373
#define IDC_CHOOSEDIFF_DIFFLIST         374
#define IDC_BINMODE_LITTLEEND           375
#define IDC_BINMODE_BIGEND              376
#define IDC_BLOCKSEL_OFFSET             377
#define IDC_BLOCKSEL_OFFSETEND          378
#define IDC_MANIPBITS_BIT1              379
#define IDC_MANIPBITS_BIT2              380
#define IDC_MANIPBITS_BIT3              381
#define IDC_MANIPBITS_BIT4              382
#define IDC_MANIPBITS_BIT5              383
#define IDC_MANIPBITS_BIT6              384
#define IDC_MANIPBITS_BIT7              385
#define IDC_MANIPBITS_BIT8              386
#define IDC_MANIPBITS_VALUE             387
#define IDC_BMKADD_OFFSET               388
#define IDC_BMKADD_NAME                 389
#define IDC_REMOVEBMK_LIST              390
#define IDC_OPENPARTIAL_BEGINOFF        391
#define IDC_OPENPARTIAL_ENDBYTES        392
#define IDC_OPENPARTIAL_OFFSET          393
#define IDC_OPENPARTIAL_BYTES           394
#define IDC_OPENPARTIAL_RELOFFSET       395
#define IDC_OPENPARTIAL_BYTECOUNT       396
#define IDC_FPASTE_OWERWRITE            397
#define IDC_FPASTE_INSERT               398
#define IDC_FPASTE_PASTETIMES           399
#define IDC_FPASTE_SKIPS                400
#define IDC_FPASTE_CFORMAT              401
#define IDC_FPASTE_REFRESH              402
#define IDC_TMPLRESULT_RESULT           403
#define IDC_REVERSE_OFFSET              404
#define IDC_REVERSE_OFFSETEND           405
#define IDC_CHINST_INSTANCE             406
#define IDC_CHINST_NEWINSTANCE          407
#define IDC_DRIVE_LIST                  408
#define IDC_DRIVE_INFO                  409
#define IDC_DRIVE_TRACK                 410
#define IDC_SHORTCUT_LINKS              411
#define IDC_DAND_LIST                   412
#define IDC_ENCODE_LIST                 413
#define IDC_ENCODE_ARGS                 414
#define IDC_ENCODE_ENC                  415
#define IDC_ENCODE_DEC                  416
#define IDC_DROPPED_FILES               417
#define IDC_FPASTE_TXT                  418
#define IDC_SETTINGS_EDITORSELECT       419
#define IDC_DELETE_STARTOFFSET          420
#define IDC_DELETE_INCLUDEOFFSET        421
#define IDC_DELETE_NUMBEROFBYTES        422
#define IDC_DELETE_ENDOFFSET            423
#define IDC_DELETE_NUMBYTES             424
#define IDM_EDIT_UNDO                   425
#define IDM_EDIT_REDO                   426
#define IDC_ENABLE_DRAG                 1074
#define IDC_ALWAYS_CHOOSE               1075
#define IDC_DROP_BIN_DATA               1076
#define IDC_DRAG_BIN_DATA               1077
#define IDC_TEXT_HEXDUMP                1078
#define IDC_TEXT_DISPLAY                1079
#define IDC_ENABLE_DROP                 1080
#define IDC_EXPORTDIGITS                1081
#define IDC_APPICON                     1082
#define IDC_COMBO1                      1083
#define IDS_APPNAME                     10000
#define IDS_DIFFLISTITEMFORMAT          10001
#define IDS_ABOUTFRHEDVER               10002
#define IDS_OPEN_ALL_FILES              10003
#define IDS_UNTITLED                    10004
#define IDS_FONT_ANSI                   10005
#define IDS_FONT_OEM                    10006
#define IDS_MODE_READONLY               10007
#define IDS_MODE_OVERWRITE              10008
#define IDS_MODE_INSERT                 10009
#define IDS_STATUS_LITTLE_ENDIAN        10010
#define IDS_STATUS_BIG_ENDIAN           10011
#define IDS_OPEN_SHORTCUT               10012
#define IDS_OFFSET_START_ERROR          10016
#define IDS_OFFSET_END_ERROR            10017
#define IDS_OFFSET_ERROR                10018
#define IDS_ERR_READING_FILE            10032
#define IDS_NO_MEMORY                   10033
#define IDS_BYTES_NOT_KNOWN             10034
#define IDS_ERR_OPENING_FILE            10035
#define IDS_NO_MEM_FOR_FILE             10036
#define IDS_FILE_SAVE_ERROR             10037
#define IDS_FILE_BACKUP_ERROR           10038
#define IDS_ERR_SAVE_PARTIAL            10039
#define IDS_ERR_MOVE_DATA               10040
#define IDS_ERR_RESIZE_FILE             10041
#define IDS_ERR_SEEK_FILE               10042
#define IDS_ERR_WRITE_FILE              10043
#define IDS_ERR_HELP_NOT_FOUND          10044
#define IDS_ERR_FILE_OPEN_CODE          10045
#define IDS_ERR_WRITING_OPTIONS         10046
#define IDS_ERR_EMPTY_FILE              10047
#define IDS_ERR_EXT_EDITOR              10048
#define IDS_ERR_CANNOT_INSERT           10049
#define IDS_ERR_CHECK_FILESIZE          10050
#define IDS_ERR_NO_DATA                 10051
#define IDS_ERR_CANNOT_GET_TEXT         10052
#define IDS_ISO_KB                      10112
#define IDS_ISO_MB                      10113
#define IDS_ISO_GB                      10114
#define IDS_ISO_TB                      10115
#define IDS_ABOUT_BROWSER_ERR           10160
#define IDS_ABOUT_FILENOTFOUND          10161
#define IDS_BMK_INVALID_POSITION        10177
#define IDS_BMK_ALREADY_THERE           10178
#define IDS_BMK_EMPTY_FILE              10179
#define IDS_BMK_MAX_AMOUNT              10180
#define IDS_BMK_IS_INVALID              10181
#define IDS_BMK_NONE_TOREMOVE           10182
#define IDS_BMK_REMOVE_ALL              10183
#define IDS_APPEND_UNKNOWN_AMOUNT       10192
#define IDS_APPEND_NO_MEM               10193
#define IDS_BITMANIP_AT_OFFSET          10208
#define IDS_BITMANIP_VALUE              10209
#define IDS_DIFF_CHOOSEFILE             10224
#define IDS_DIFF_ERROPEN                10225
#define IDS_DIFF_AREAS_FOUND            10226
#define IDS_DIFF_REMAINING_BYTES        10227
#define IDS_DIFF_NO_DIFF                10228
#define IDS_CANNOT_ACCESS_CLIPBOARD     10240
#define IDS_CANNOT_LOCK_CLIPBOARD       10241
#define IDS_CLIPBOARD_NO_MEM            10242
#define IDS_CLIPBOARD_COPY_TO           10243
#define IDS_CLIPBOARD_SELECT_FORMAT     10244
#define IDS_CANNOT_GET_CB_TEXT          10245
#define IDS_IMPORT_FROM_CB              10246
#define IDS_COPY_TOO_MANY               10256
#define IDS_COPY_NO_MEM                 10257
#define IDS_CUT_TOO_MANY                10272
#define IDS_CUT_NO_MEM                  10273
#define IDS_CUT_FAILED                  10274
#define IDS_DELETE_TOO_MANY             10288
#define IDS_DELETE_FAILED               10289
#define IDS_DECI_UNKNOWN                10304
#define IDS_DECI_UNKNOWN_TIMES          10305
#define IDS_DECI_INVALID_START          10306
#define IDS_DECI_NO_SPACE               10307
#define IDS_PASTE_ATLEAST_ONCE          10320
#define IDS_PASTE_WAS_EMPTY             10321
#define IDS_PASTE_NO_MEM                10322
#define IDS_PASTE_NO_SPACE              10323
#define IDS_FILL_ZERO_SIZE_FILE         10336
#define IDS_FILL_ZERO_SIZE_STR          10337
#define IDS_FILL_TOO_MANY_BYTES         10338
#define IDS_CM_NEGATIVE_OFFSET          10352
#define IDS_CM_INVALID_TARGET           10353
#define IDS_CM_ZERO_LEN                 10354
#define IDS_CM_INVALID_BLOCK            10355
#define IDS_CM_NOT_MOVED                10356
#define IDS_CM_OUTSIDE_DATA             10357
#define IDS_PARTIAL_LOAD_BYTES          10368
#define IDS_PARTIAL_TOO_BIG             10387
#define IDS_PARTIAL_BIGGER              10388
#define IDS_PARTIAL_TOO_MANY_BYTES      10389
#define IDS_REVERSE_ONE_BYTE            10400
#define IDS_REVERSE_BLOCK_EXTEND        10401
#define IDS_SCUT_LINKNAMES              10416
#define IDS_SCUT_ALREADY_CONTAINS       10417
#define IDS_SCUT_CAN_ADD                10418
#define IDS_SCUT_CANNOT_ADD             10419
#define IDS_SCUT_CAN_SEARCH             10420
#define IDS_SCUT_CANNOT_SEARCH          10421
#define IDS_SCUT_CANNOT_SAVE            10422
#define IDS_SCUT_CANNOT_MOVE            10423
#define IDS_SCUT_NO_LINK_MOVE           10424
#define IDS_SCUT_CANNOT_FIND            10425
#define IDS_SCUT_PLACE_LINK             10426
#define IDS_SCUT_MOVE_LINK              10427
#define IDS_SCUT_ALREADY_LINK           10428
#define IDS_SCUT_UPDATE_LINKS           10429
#define IDS_SCUT_SEARCH_FOLDER          10430
#define IDS_SCUT_NO_SELECT_DEL          10431
#define IDS_FIND_SEL_TOO_LARGE          10448
#define IDS_FIND_CANNOT_FIND            10449
#define IDS_FIND_EMPTY_STRING           10450
#define IDS_FIND_NO_MORE                10451
#define IDS_FIND_NO_STRING              10452
#define IDS_DRIVES_NEED_ADMIN           10464
#define IDS_DRIVES_ERR_OPEN             10465
#define IDS_DRIVES_CYLINDERS            10466
#define IDS_DRIVES_SECTORS              10467
#define IDS_DRIVES_TRACSPERCYL          10468
#define IDS_DRIVES_SECTPERTRACK         10469
#define IDS_DRIVES_BYTESPERSECT         10470
#define IDS_DRIVES_TOTALBYTES           10471
#define IDS_DRIVES_SECTOR               10472
#define IDS_DRIVES_DRIVE_PART           10473
#define IDS_DRIVES_DRIVE_ONLY           10474
#define IDS_HEXF_NO_MEM                 10480
#define IDS_HEXF_ILLEGAL_CHAR           10481
#define IDS_HEXF_ILLEGAL_OFFS           10482
#define IDS_HEXF_NONZERO_START          10483
#define IDS_HEXF_INV_OFFSET             10484
#define IDS_HEXF_CHAR_HEX_NO_MATCH      10485
#define IDS_HEXF_ERR_INV_CHAR           10486
#define IDS_HEXF_ERR_EOF                10487
#define IDS_HEXF_OPEN_FORMAT1           10488
#define IDS_HEXF_OPEN_FORMAT2           10489
#define IDS_HEXF_OPEN_FORMAT3           10490
#define IDS_REPL_NO_DATA                10496
#define IDS_REPL_CANT_DELETE            10497
#define IDS_REPL_FAILED                 10498
#define IDS_REPL_CANNOT_CONVERT         10499
#define IDS_REPL_SAME_STRS              10500
#define IDS_REPL_COUNT                  10501
#define IDS_REPL_BAD_SELECT             10502
#define IDS_UPDLG_OPTION                10512
#define IDS_UPDLG_VALUE                 10513
#define IDS_UPDLG_LINKS                 10514
#define IDS_UPDLG_MRUFILES              10515
#define IDS_UPDLG_CANT_COPY_CURR        10516
#define IDS_CANT_OPEN_VER               10517
#define IDS_SBAR_SELECTED_OFFSET        11008
#define IDS_SBAR_NSEL_OFFSET            11009
#define IDS_SBAR_BITS                   11010
#define IDS_SBAR_UNSIGNED               11011
#define IDS_SBAR_BYTE_SHORT             11012
#define IDS_SBAR_END                    11013
#define IDS_SBAR_WORD_SHORT             11014
#define IDS_SBAR_LONG_SHORT             11015
#define IDS_SBAR_SIGNED                 11016
#define IDS_SBAR_SIZE                   11017
#define IDS_SBAR_NO_FILE                11018
#define IDS_TPL_FILENAME                12000
#define IDS_TPL_TEMPLATE_FILE           12001
#define IDS_TPL_APPLIED_AT              12002
#define IDS_TPL_FMT_BYTE_0              12003
#define IDS_TPL_FMT_BYTE                12004
#define IDS_TPL_ERR_NOSPC_BYTE          12005
#define IDS_TPL_ERR_NO_VAR              12006
#define IDS_TPL_FMT_WORD                12007
#define IDS_TPL_ERR_NOSPC_WORD          12008
#define IDS_TPL_FTM_DWORD               12009
#define IDS_TPL_ERR_NOSPC_DWORD         12010
#define IDS_TPL_FMT_FLOAT               12011
#define IDS_TPL_ERR_NOSPC_FLOAT         12012
#define IDS_TPL_FMT_DOUBLE              12013
#define IDS_TPL_ERR_NOSPC_DOUBLE        12014
#define IDS_TPL_ERR_UNK_TYPE            12015
#define IDS_TPL_LENGTH                  12016
#define IDS_TPL_FILE_PATTERN            12017
#define IDS_TPL_CHOOSE_FILE             12018
#define IDS_TPL_CANNOT_OPEN             12019
#define IDS_TPL_CANNOT_OPEN_FROM        12020
#define IDS_DD_SELECT_MOVE_ITEM         13008
#define IDS_DD_MENU_MOVE                13009
#define IDS_DD_MENU_COPY                13010
#define IDS_DD_MENU_CANCEL              13011
#define IDS_DD_NO_DATA                  13012
#define IDS_DD_TYMED_NOTSUP             13013
#define IDS_FLOAT_SIZE                  13024
#define IDS_FLOAT_NOSPACE               13025
#define IDS_DOUBLE_SIZE                 13026
#define IDS_DOUBLE_NOSPACE              13027
#define IDS_FPROP_NAME                  13028
#define IDS_FPROP_PARTIAL_OPEN          13029
#define IDS_FPROP_FSIZE                 13030
#define IDS_FPROP_HDUMP_LINES           13031
#define IDS_MRU_REMOVING                13032
#define IDS_RESET_COLORS                13033
#define IDS_ASK_DELETE_FILE             13034
#define IDS_ERR_CANNOT_DELETE           13035
#define IDS_ADOBT_OS_COLORS             13036
#define IDS_SAVE_MODIFIED               14000
#define IDS_HDUMP_SAVED                 15008
#define IDS_HDUMP_SAVE_FAIL             15009
#define IDS_HDUMP_NO_MEM_CL             15010
#define IDS_HDUMP_CL_FAIL               15011
#define IDS_HDUMP_FILE_PATTERN          15012
#define IDM_OLE_DRAG_DROP               40142
