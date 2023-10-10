#ifndef HAL_ALGORITHM_H
#define HAL_ALGORITHM_H

#define MAX_MD_GRID_AREA_NUM 256			//最大16*16个的正方形块
#define MAX_POINTS_EACH_MD_GRID_AREA 4

#define MAX_MD_AREA_NUM 8
#define MAX_POINTS_EACH_MD_AREA 8

#define MAX_HD_AREA_NUM 8
#define MAX_POINTS_EACH_HD_AREA 8

#define MAX_OD_AREA_NUM 8
#define MAX_POINTS_EACH_OD_AREA 8

#define MAX_VG_AREA_NUM 8
#define MAX_LINES_EACH_VG_AREA 4

#define MAX_PET_AREA_NUM 8
#define MAX_POINTS_EACH_PET_AREA 8

#define MAX_VEH_AREA_NUM 8
#define MAX_POINTS_EACH_VEH_AREA 8

#define MAX_PVD_AREA_NUM 8
#define MAX_POINTS_EACH_PVD_AREA 8

#define MAX_FACE_AREA_NUM 8
#define MAX_POINTS_EACH_FACE_AREA 8

#define MAX_PERVEHPET_AREA_NUM 8
#define MAX_POINTS_EACH_PERVEHPET_AREA 8


typedef struct AlarmAreaPoint_s
{
    int x;
    int y;
} AlarmAreaPoint_t;

typedef struct MdArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_MD_AREA];	//里面的点按照顺时针方向设置，左上，右上，右下，左下
	int AlarmAreaMaskEnabled;				//0: 区域内侦测到报警；1:区域内侦测到不报警
} MdArea_t;

typedef struct MdGridArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_MD_GRID_AREA];
	int AlarmAreaMaskEnabled;				//0: 区域内侦测到报警；1:区域内侦测到不报警
} MdGridArea_t;

typedef struct HdArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_HD_AREA];
} HdArea_t;

typedef struct PetArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_PET_AREA];
} PetArea_t;

typedef struct VehArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_VEH_AREA];
} VehArea_t;

typedef struct PvdArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_PVD_AREA];
} PvdArea_t;

typedef struct FaceArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_FACE_AREA];
} FaceArea_t;

typedef struct PersonVehiclePetArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_PERVEHPET_AREA];
} PersonVehiclePetArea_t;




typedef struct ODArea_s
{
    int AlarmAreaPointNum;
    AlarmAreaPoint_t AlarmAreaPoint[MAX_POINTS_EACH_OD_AREA];
} OdArea_t;

typedef struct VG_Point_s
{
    int x;
    int y;
} VG_Point_t;

typedef struct VGLine_s
{
    VG_Point_t px;   //point x
    VG_Point_t py;   //point y
    VG_Point_t pdx;  //point direction x
    VG_Point_t pdy;  //point direction y
} VGLine_t;

typedef struct VgArea_s
{
    int AlarmLineNum;
    VGLine_t AlarmLine[MAX_LINES_EACH_VG_AREA];
} VgArea_t;


typedef struct ipc_motion_detect_config_s
{
	int enable;
	int motion_track_enable;		//for PTZ tracking
	int sensitivity;
	int motion_pixels_threshold;
	
	int MDAreaNum;					//设定多个矩形框/规则框，区域侦测模式，框个数
	MdArea_t MDArea[MAX_MD_AREA_NUM];	//现仅支持四点矩形区域侦测，并且是矩形区域。

	int ODAreaNum;
	OdArea_t ODArea[MAX_OD_AREA_NUM];

	int VGAreaNum;
	VgArea_t VGArea[MAX_VG_AREA_NUM];

	int GridAreaDivRowNum;		//分成多少行
	int GridAreaDivColNum;		//分成多少列	
	int MDGridAreaNum;			//设定网格区域侦测模式，网格个数，数值为 GridAreaDivRowNum * GridAreaDivColNum
	MdGridArea_t MDGridArea[MAX_MD_GRID_AREA_NUM];
}ipc_motion_detect_config;

typedef struct ipc_human_detect_config_s
{
	int enable;
	int human_track_enable;		//for PTZ tracking
	int width;
	int height;
	int framerate;
	int sensitivity;	// Sigmastar:[0,10]; Realtek:[0,7]; T31:[0,5]

	int HDAreaNum;
	HdArea_t HDArea[MAX_HD_AREA_NUM];
}ipc_human_detect_config;

typedef struct t31_vg_detect_config_s
{
	int enable;
	int vg_track_enable;		//for PTZ tracking
	int ul_x;//左上角x
	int ul_y;//左上角y
	int br_x;//右下角x
	int br_y;//右下角y
	int framerate;
	int sensitivity; 
}t31_vg_detect_config;

typedef struct t31_pet_detect_config_s
{
	int enable;
	int pet_track_enable;		//for PTZ tracking
	int ul_x;//左上角x
	int ul_y;//左上角y
	int br_x;//右下角x
	int br_y;//右下角y
	int framerate;
	int sensitivity; 
	int PETAreaNum;
	PetArea_t PETArea[MAX_PET_AREA_NUM];
}t31_pet_detect_config;

typedef struct t31_veh_detect_config_s
{
	int enable;
	int veh_track_enable;		//for PTZ tracking
	int framerate;
	int sensitivity; 
	int VEHAreaNum;
	VehArea_t VEHArea[MAX_VEH_AREA_NUM];
}t31_veh_detect_config;

typedef struct t31_pvd_detect_config_s
{
	int enable;
	int veh_track_enable;		//for PTZ tracking
	int framerate;
	int sensitivity; 
	int PVDAreaNum;
	PvdArea_t PVDArea[MAX_PVD_AREA_NUM];
}t31_pvd_detect_config;

typedef struct t31_face_detect_config_s
{
	int enable;
	int face_track_enable;		//for PTZ tracking
	int framerate;
	int sensitivity; 
	int FACEAreaNum;
	FaceArea_t FACEArea[MAX_PVD_AREA_NUM];
}t31_face_detect_config;

typedef struct t31_personvehiclepet_detect_config_s
{
	int enable;
	int PersonVehiclePet_track_enable;		//for PTZ tracking
	int framerate;
	int sensitivity; 
	int PersonVehiclePetAreaNum;
	PersonVehiclePetArea_t PersonVehiclePetArea[MAX_PERVEHPET_AREA_NUM];
}t31_personvehiclepet_detect_config;





typedef struct ipc_mt_config_s
{
	int enable;
	int detect_every_frames;
	int fov_hori_degree;
	int fov_vert_degree;
	int sensitivity;
}ipc_mt_config;

/* Only for rts3903n/rts3906 new rtsxmd library */
typedef struct ipc_rtsxmd_config_s
{
	int width;
	int height;
	int framerate;	
	int md_sensitivity;
	int pd_sensitivity;
	int mt_sensitivity;
	int ioc_sensitivity;
}ipc_rtsxmd_config;

typedef enum
{
	E_HAL_VIDEO_ALGORITHM_MOTION_DETECTION = 0,
	E_HAL_VIDEO_ALGORITHM_HUMAN_DETECTION,
	E_HAL_VIDEO_ALGORITHM_MOTION_TRACKING,	//Only for Realtek rtsxmd library
	E_HAL_VIDEO_ALGORITHM_INOUT_COUNT,		//Only for Realtek rtsxmd library
	E_HAL_VIDEO_ALGORITHM_PERM_DETECTION,
	E_HAL_VIDEO_ALGORITHM_PETBODY_DETECTION,
	E_HAL_VIDEO_ALGORITHM_VEHICLE_DETECTION,
	E_HAL_VIDEO_ALGORITHM_HUMAN_VEHICLE_DETECTION,
	E_HAL_VIDEO_ALGORITHM_FACECAP_DETECTION,
	E_HAL_VIDEO_ALGORITHM_PERSON_VEHICLE_PET_DETECTION,
	E_HAL_VIDEO_ALGORITHM_MAX,
}E_HAL_VIDEO_ALGORITHM_TYPE;

/* All based on Motion Detection Algorithm */
typedef enum
{
	E_HAL_VIDEO_ALGO_MD_AREA = 0,
	E_HAL_VIDEO_ALGO_OD_AREA,	
	E_HAL_VIDEO_ALGO_VG_AREA,
	E_HAL_VIDEO_ALGO_HD_AREA,
	E_HAL_VIDEO_ALGO_PBD_AREA,
	E_HAL_VIDEO_ALGO_VEH_AREA,
	E_HAL_VIDEO_ALGO_PVD_AREA,
	E_HAL_VIDEO_ALGO_PVPETD_AREA,
	E_HAL_VIDEO_ALGO_AREA_MAX_TYPE,
}E_HAL_VIDEO_ALGO_AREA_TYPE;

typedef enum
{
	E_HAL_ALARM_MSG_MOTION_DETECTION = 0,
	E_HAL_ALARM_MSG_NO_MOTION_DETECTION,
	E_HAL_ALARM_MSG_HUMAN_DETECTION,
	E_HAL_ALARM_MSG_NO_HUMAN_DETECTION,
	E_HAL_ALARM_MSG_PERM_DETECTION,
	E_HAL_ALARM_MSG_NO_PERM_DETECTION,
	E_HAL_ALARM_MSG_PETBODY_DETECTION,
	E_HAL_ALARM_MSG_VEHICLE_DETECTION,
	E_HAL_ALARM_MSG_PERSONVEHICLE_DETECTION,
	E_HAL_ALARM_MSG_FACECAP_DETECTION,
	E_HAL_ALARM_MSG_SOUND_DETECTION,
}E_HAL_ALARM_MSG_TYPE;

typedef struct Hal_algorithm_chn_config
{
	int bSupport;
	int bRGNSupport; // Frame switch available use with Hal_osd_ivs_cofig_s bIvsRgnSupport 
	union
	{
		ipc_motion_detect_config md_config;
		ipc_human_detect_config hd_config;
		ipc_mt_config mt_config;
		ipc_rtsxmd_config rtsxmd_config;
		t31_vg_detect_config vg_config;
		t31_pet_detect_config pet_config;
		t31_veh_detect_config veh_config;
		t31_pvd_detect_config pvd_config;
		t31_face_detect_config face_config;
		t31_personvehiclepet_detect_config personvehiclepet_config;
	};
	/* 报警侦测触发，回调处理联动事件 */
	int (*Hal_alarm_triggered)(E_HAL_ALARM_MSG_TYPE msg_type, int lParam);

	/* 部分光线变化时，应当忽略部分移动侦测误报 */
	int (*Hal_alarm_ignore_event)(E_HAL_VIDEO_ALGORITHM_TYPE alarm_type);
	
	/* 移动追踪算法有结果，电机开始转动至对应位置 */
	/* 追踪接口，x/y是图像中心点为坐标轴原点的坐标信息，    res_width/res_height指定坐标以此分辨率基准的结果 */
	int (*Hal_ptz_track_motor_start)(signed int pos_x, signed int pos_y, int res_width, int res_height);
}Hal_algorithm_chn_config;
/*****************************************************************************
 Prototype    : Hal_perm_detection_set_enable
 Description  : 设置区域侦测算法开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/7/11
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_perm_detection_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_perm_detection_set_sensitivity
 Description  : 设置区域侦测算法灵敏度
 Input        : int sensitivity  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/7/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_perm_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_perm_detection_set_line
 Description  : 设置区域侦测算法线框开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/7/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_perm_detection_set_line(int enable);

/*****************************************************************************
 Prototype    : Hal_petbody_detection_set_sensitivity
 Description  : 设置宠物侦测算法灵敏度
 Input        : int sensitivity  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/10/25
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_petbody_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_petbody_detection_set_enable
 Description  : 设置宠物侦测算法开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/10/25
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_petbody_detection_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_vehicle_detection_set_sensitivity
 Description  : 设置车辆侦测算法灵敏度
 Input        : int sensitivity  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/10/25
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_vehicle_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_vehicle_detection_set_enable
 Description  : 设置车辆侦测算法开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/10/25
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_vehicle_detection_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_person_vehicle_detection_set_sensitivity
 Description  : 设置人车侦测算法灵敏度
 Input        : int sensitivity  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2023/1/5
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_human_vehicle_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_human_vehicle_detection_set_enable
 Description  : 设置人车侦测算法开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2023/1/5
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_human_vehicle_detection_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_person_vehicle_pet_detection_set_sensitivity
 Description  : 设置人车宠物三合一侦测算法灵敏度
 Input        : int sensitivity  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2023/3/4
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_person_vehicle_pet_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_human_vehicle_detection_set_enable
 Description  : 设置人车宠物三合一侦测算法开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2023/3/4
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_person_vehicle_pet_detection_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_facecap_detection_set_sensitivity
 Description  : 设置人脸侦测算法灵敏度,只支持1~4灵敏度
 Input        : int sensitivity  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2023/1/5
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_facecap_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_facecap_detection_set_enable
 Description  : 设置人脸侦测算法开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2023/1/5
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/
extern int Hal_facecap_detection_set_enable(int enable);

extern int Hal_motion_detection_set_stop_track_flag(int stopFlag);

/*****************************************************************************
 Prototype    : Hal_motion_detection_set_mdodvg_grid_area
 Description  : 设置移动侦测MD/HD/OD/VG网格区域侦测参数，
                暂时  只支持移动侦测的网格侦测
 Input        : E_HAL_VIDEO_ALGO_AREA_TYPE area_type             
                unsigned int GridAreaDivRowMode  					分成多少行               
                unsigned int GridAreaDivColMode                  	分成多少列 
                unsigned int pMaskEnabled[MAX_MD_GRID_AREA_NUM]  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_motion_detection_set_mdodvg_grid_area(E_HAL_VIDEO_ALGO_AREA_TYPE area_type, unsigned int GridAreaDivRowNum, unsigned int GridAreaDivColNum, unsigned int pMaskEnabled[MAX_MD_GRID_AREA_NUM]);

/*****************************************************************************
 Prototype    : Hal_motion_detection_set_mdodvg_area
 Description  : 设置移动侦测MD/HD/OD/VG区域侦测参数
 Input        : E_HAL_VIDEO_ALGO_AREA_TYPE area_type  
                unsigned int MDAreaNum                
                MdArea_t pMdArea[MAX_MD_AREA_NUM]     
                unsigned int HDAreaNum                
                HdArea_t pHdArea[MAX_HD_AREA_NUM]     
                unsigned int ODAreaNum                
                OdArea_t pOdArea[MAX_OD_AREA_NUM]     
                unsigned int VGAreaNum                
                VgArea_t pVgArea[MAX_VG_AREA_NUM]
           		unsigned int PVPETAreaNum//支持2个周界
           		PersonVehiclePetArea_t pPvpetArea[MAX_PERVEHPET_AREA_NUM]//第一个周界最多支持6个顶点，第二个周界最多支持5个顶点
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/3/8
    Author       : Owen
    Modification : Created function

*****************************************************************************/

extern int Hal_motion_detection_set_mdodvg_area(E_HAL_VIDEO_ALGO_AREA_TYPE area_type, unsigned int MDAreaNum, MdArea_t pMdArea[MAX_MD_AREA_NUM], unsigned int HDAreaNum, HdArea_t pHdArea[MAX_HD_AREA_NUM], unsigned int ODAreaNum, OdArea_t pOdArea[MAX_OD_AREA_NUM], unsigned int VGAreaNum, VgArea_t pVgArea[MAX_VG_AREA_NUM],unsigned int PVPETAreaNum, PersonVehiclePetArea_t pPvpetArea[MAX_PERVEHPET_AREA_NUM]);

/*****************************************************************************
 Prototype    : Hal_motion_detection_set_sensitivity
 Description  : 设置移动侦测算法灵敏度
 Input        : int sensitivity  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_motion_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_motion_detection_set_enable
 Description  : 设置移动侦测算法开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_motion_detection_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_motion_detection_set_chipset_sdk_params
 Description  : 设置移动/人形侦测算法参数
 Input        : void *args 
 				移动侦测时, args填入t31_move_param_input_t结构体
				人形侦测时，args填入t31_persondet_param_input_t结构体
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/8/3
    Author       : liujinfeng
    Modification : Created function

*****************************************************************************/

extern int Hal_set_chipset_sdk_params(E_HAL_VIDEO_ALGORITHM_TYPE enWorkMode, void *args);


/*****************************************************************************
 Prototype    : Hal_motion_tracking_set_enable
 Description  : 开始电机追踪移动物体
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/11/18
    Author       : Owen
    Modification : Created function

*****************************************************************************/
int Hal_motion_tracking_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_human_detection_set_sensitivity
 Description  : 设置人形侦测灵敏度
 Input        : int sensitivity  [0,10]
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_human_detection_set_sensitivity(int sensitivity);

/*****************************************************************************
 Prototype    : Hal_human_detection_set_enable
 Description  : 设置人形侦测开关
 Input        : int enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_human_detection_set_enable(int enable);

/*****************************************************************************
 Prototype    : Hal_get_video_algo_channel_width
 Description  : 内部库使用，获取算法视频通道的视频宽
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_video_algo_channel_width();

/*****************************************************************************
 Prototype    : Hal_get_video_algo_channel_height
 Description  : 内部库使用，获取算法视频通道的高
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_video_algo_channel_height();

/*****************************************************************************
 Prototype    : Hal_get_video_algo_is_support
 Description  : 内部库使用，获取当前算法是否配置支持
 Input        : E_HAL_VIDEO_ALGORITHM_TYPE algo_type  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_video_algo_is_support(E_HAL_VIDEO_ALGORITHM_TYPE algo_type);

/*****************************************************************************
 Prototype    : Hal_get_video_algo_channel_config
 Description  : 内部库使用，获取算法通道全局变量参数
 Input        : E_HAL_VIDEO_ALGORITHM_TYPE algo_type       
                Hal_algorithm_chn_config **pAlgoChnconfig  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_get_video_algo_channel_config(E_HAL_VIDEO_ALGORITHM_TYPE algo_type, Hal_algorithm_chn_config **pAlgoChnconfig);

/*****************************************************************************
 Prototype    : Hal_set_video_algo_channel_config
 Description  : 内部库使用，同步算法通道全局变量参数
 Input        : E_HAL_VIDEO_ALGORITHM_TYPE algo_type      
                Hal_algorithm_chn_config *pAlgoChnconfig  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_set_video_algo_channel_config(E_HAL_VIDEO_ALGORITHM_TYPE algo_type, Hal_algorithm_chn_config *pAlgoChnconfig);

/*****************************************************************************
 Prototype    : Hal_video_algorithm_uninit
 Description  :  
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/2/23
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_video_algorithm_uninit();

/*****************************************************************************
 Prototype    : Hal_video_algorithm_init
 Description  :  
 Input        : Hal_algorithm_chn_config algo_chn_cfg[E_HAL_VIDEO_ALGORITHM_MAX]  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/11
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_video_algorithm_init(Hal_algorithm_chn_config algo_chn_cfg[E_HAL_VIDEO_ALGORITHM_MAX]);

#endif
