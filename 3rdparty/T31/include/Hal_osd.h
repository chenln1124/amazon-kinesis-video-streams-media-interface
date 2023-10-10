#ifndef HAL_OSD_H
#define HAL_OSD_H

typedef enum
{
	E_HAL_OSD_POS_LEFT_TOP = 0,
	E_HAL_OSD_POS_RIGHT_TOP,
	E_HAL_OSD_POS_LEFT_BOTTOM,
	E_HAL_OSD_POS_RIGHT_BOTTOM,
	E_HAL_OSD_POS_RIGHT_BOTTOM1,
	E_HAL_OSD_POS_RIGHT_BOTTOM2,
	E_HAL_OSD_POS_RIGHT_BOTTOM3,
	E_HAL_OSD_POS_RIGHT_BOTTOM4,
	E_HAL_OSD_POS_RIGHT_BOTTOM5,
	E_HAL_OSD_POS_RIGHT_BOTTOM6,
	E_HAL_OSD_POS_TOP_CENTER,
	E_HAL_OSD_POS_BOTTOM_CENTER,
}E_HAL_OSD_POS_TYPE;

typedef enum
{
	E_HAL_OSD_TIME_YYMMDD = 0,
	E_HAL_OSD_TIME_MMDDYY = 1,
	E_HAL_OSD_TIME_DDMMYY = 2,
}E_HAL_OSD_TIME_TYPE;

/* OSD TIME */
typedef struct
{
	unsigned char bShowDate;
	unsigned char bShowTime;
	unsigned char bShowWeek;
	unsigned char bShowTemperature;
	unsigned char bShowHumidity;
	unsigned char u8DateSeparatorFormat;	//日期分割符格式 0:/		 1:-
	unsigned char u32OsdTimeFormat;			//0:YYYY-MM-DD 1:MM-DD-YYYY 2:DD-MM-YYYY
	E_HAL_OSD_POS_TYPE posTime;

	int timezone;							//unit: seconds
	int timezone_offset_seconds;			//非标准时区，偏移秒数
	int dst_opened;							//夏令时开始了
	int dst_offset_seconds;					//夏令时偏移秒数
	int hour_format;						//0: 24小时制 1: 12小时制
}Hal_osd_time_config_s;

/* OSD Chn Name */
typedef struct
{
	unsigned char bShowChnName;
	unsigned char strChnName[64];
	E_HAL_OSD_POS_TYPE posChnName;
}Hal_osd_chn_name_config_s;

/* OSD logo */
typedef struct
{
	unsigned char bShowLogo;
	unsigned int  logoWidth[4];
	unsigned int  logoHeight[4];
	E_HAL_OSD_POS_TYPE posLogo;
	char filename[4][128];
}Hal_osd_logo_config_s;

/* OSD Index */
typedef struct
{
	unsigned char bShowIndex;
	unsigned char strIndex[80];
	unsigned int strIndexLen;
	E_HAL_OSD_POS_TYPE posIndex;
}Hal_osd_index_config_s;

/* OSD Ivs */
typedef struct
{
	unsigned short bIvsRgnSupport; // RGN support ivs frame use with Hal_algorithm_chn_config bRGNSupport
}Hal_osd_ivs_cofig_s;

typedef enum
{
	E_HAL_OSD_INDEX_TIME = 0,
	E_HAL_OSD_INDEX_CHN_NAME,
	E_HAL_OSD_INDEX_LOGO,
	E_HAL_OSD_INDEX_COVER1,
	E_HAL_OSD_INDEX_COVER2,
	E_HAL_OSD_INDEX_COVER3,
	E_HAL_OSD_INDEX_COVER4,
	E_HAL_OSD_INDEX_COVER5,
	E_HAL_OSD_INDEX_COVER6,
	E_HAL_OSD_INDEX_MD,
	E_HAL_OSD_INDEX_HD,
	E_HAL_OSD_INDEX_VG,
	E_HAL_OSD_INDEX_TRACK,
	E_HAL_OSD_INDEX_PET,
	E_HAL_OSD_INDEX_VEH,
	E_HAL_OSD_INDEX_MAX,
}E_HAL_OSD_INDEX;

typedef struct Hal_osd_config_s
{
	int bSupport;
	union
	{
		Hal_osd_time_config_s osd_time_cfg;
		Hal_osd_chn_name_config_s osd_chn_name_cfg;
		Hal_osd_logo_config_s osd_logo_cfg;
		Hal_osd_index_config_s osd_index_cfg;
		Hal_osd_ivs_cofig_s osd_ivs_cfg;
	};
}__attribute__((packed))Hal_osd_config_t;

/*****************************************************************************
 Prototype    : Hal_osd_get_gb2312_font_config
 Description  : 库内部使用，获取gb2312字体库支持情况
 Input        : int *bSupportChinese         
                int *bUseSmallGB2312FontLib  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/12
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern void Hal_osd_get_gb2312_font_config(int *bSupportChinese, int *bUseSmallGB2312FontLib);

/*****************************************************************************
 Prototype    : Hal_osd_get_is_support
 Description  : 库内部使用，获取OSD是否支持
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/12
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_osd_get_is_support();

/*****************************************************************************
 Prototype    : Hal_osd_get_params
 Description  : 获取OSD类型参数配置
 Input        : E_HAL_OSD_INDEX index       
                Hal_osd_config_t **pOsdCfg  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/12
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_osd_get_params(E_HAL_OSD_INDEX index, Hal_osd_config_t **pOsdCfg);

/*****************************************************************************
 Prototype    : Hal_osd_set_params
 Description  : 设置OSD显示参数
 Input        : E_HAL_OSD_INDEX index     
                Hal_osd_config_t osd_cfg  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_osd_set_params(E_HAL_OSD_INDEX index, Hal_osd_config_t osd_cfg);

/*****************************************************************************
 Prototype    : Hal_osd_get_chn_params
 Description  : 分别获取主子码流OSD类型参数配置
 Input        : E_HAL_OSD_INDEX index       
                Hal_osd_config_t **pOsdCfg  
               int chn//0:主码流 1:子码流
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/10/20
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_osd_get_chn_params(E_HAL_OSD_INDEX index, Hal_osd_config_t **pOsdCfg,int chn);


/*****************************************************************************
 Prototype    : Hal_osd_set_chn_params
 Description  : 主子码流设置OSD显示参数
 Input        : E_HAL_OSD_INDEX index     
                Hal_osd_config_t osd_cfg  
				int chn//0:主码流 1:子码流
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/10/19
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_osd_set_chn_params(E_HAL_OSD_INDEX index, Hal_osd_config_t osd_cfg,int chn);

/*****************************************************************************
 Prototype    : Hal_osd_uninit
 Description  :  
 Input        : None
 Output       : None
 Return Value : 0:success; others:failed
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_osd_uninit();

/*****************************************************************************
 Prototype    : Hal_osd_init
 Description  :  
 Input        : int bSupport                                   
                int bSupportChinese                            
                int bUseSmallGB2312FontLib    
                unsigned char resRootPath[64]		//字体资源存放路径，暂时只支持配置字体路劲配置，如/mnt/mtd/font/
                Hal_osd_config_t osd_cfg[E_HAL_OSD_INDEX_MAX]  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_osd_init(int bSupport, int bSupportChinese, int bUseSmallGB2312FontLib, unsigned char resRootPath[64], Hal_osd_config_t osd_cfg[E_HAL_OSD_INDEX_MAX]);


#endif
