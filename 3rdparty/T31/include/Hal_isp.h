#ifndef HAL_ISP_H
#define HAL_ISP_H

typedef enum
{
	E_ISP_HLDC_DISABLE = 0,
	E_ISP_HLDC_ENABLE,
}E_ISP_HLDC_MODE;


typedef enum
{
	E_ISP_WDR_DISABLE = 0,
	E_ISP_WDR_ENABLE,
}E_ISP_WDR_MODE;

typedef enum
{
	E_ISP_FLIP_DISABLE = 0,
	E_ISP_FLIP_ENABLE,
}E_ISP_FLIP_MODE;

typedef enum
{
	E_ISP_MIRROR_DISABLE = 0,
	E_ISP_MIRROR_ENABLE,
}E_ISP_MIRROR_MODE;

typedef enum
{
	E_ISP_3DNR_OFF = 0,
	E_ISP_3DNR_LEVEL0,
	E_ISP_3DNR_LEVEL1,
	E_ISP_3DNR_LEVEL2,
	E_ISP_3DNR_LEVEL3,
}E_ISP_3DNR_MODE;

typedef enum
{
	E_ISP_AE_FLICKER_DISABLE = 0,
	E_ISP_AE_FLICKER_50HZ = 50,	
	E_ISP_AE_FLICKER_60HZ = 60,	
	E_ISP_AE_FLICKER_AUTO = 100,	
}E_ISP_AE_FLICKER_MODE;

typedef enum
{
	E_ISP_IR_GRAY_DISABLE = 0,
	E_ISP_IR_GRAY_ENABLE = 1,
}E_ISP_IR_GRAY_MODE;

/*****************************************************************************
 Prototype    : t31_isp_set_tunning_HiLightDepress
 Description  : 设置T31 isp强光抑制强度
 Input        : int strength  强光抑制强度参数. 君正T31 取值范围为［0-10], 0表示关闭功能。
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/4/22
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_set_tunning_HiLightDepress(int strength);

/*****************************************************************************
 Prototype    : t31_isp_get_tunning_HiLightDepress
 Description  : 获取当前t31 isp强光抑制强度
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/4/22
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_get_tunning_HiLightDepress();

/*****************************************************************************
 Prototype    : Hal_isp_set_tunning_hldc
 Description  : 动态设定畸变校正开关
 Input        : E_ISP_HLDC_MODE enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2022/4/22
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_set_tunning_hldc(E_ISP_HLDC_MODE enable);

/*****************************************************************************
 Prototype    : Hal_isp_set_wdr_enable
 Description  : 设置WDR开关
 Input        : E_ISP_WDR_MODE enable  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_set_wdr_enable(E_ISP_WDR_MODE enable);

/*****************************************************************************
 Prototype    : Hal_isp_get_flip_mirror
 Description  : 获取flip/mirror开关变量值
 Input        : int *bFlip    
                int *bMirror  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/4/19
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_get_flip_mirror(int *bFlip, int *bMirror);

/*****************************************************************************
 Prototype    : Hal_isp_set_flip_mirror
 Description  : 设置视频翻转镜像
 Input        : E_ISP_FLIP_MODE bFlip      
                E_ISP_MIRROR_MODE bMirror  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_set_flip_mirror(E_ISP_FLIP_MODE bFlip, E_ISP_MIRROR_MODE bMirror);

/*****************************************************************************
 Prototype    : Hal_isp_set_3DNR_level
 Description  : 设置3DNR 3D降噪等级，level 0为关闭
 Input        : E_ISP_3DNR_MODE level  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_set_3DNR_level(E_ISP_3DNR_MODE level);

/*****************************************************************************
 Prototype    : Hal_isp_set_Aeflicker_frequency
 Description  : 设置刷新频率
 Input        : E_ISP_AE_FLICKER_MODE frequency  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_set_Aeflicker_frequency(E_ISP_AE_FLICKER_MODE frequency);

/*****************************************************************************
 Prototype    : Hal_isp_set_color2gray
 Description  : 白天夜视切换时，图像灰阶模式开关控制
 Input        : E_ISP_IR_GRAY_MODE mode  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2021/3/15
    Author       : Owen
    Modification : Created function

*****************************************************************************/
extern int Hal_isp_set_color2gray(E_ISP_IR_GRAY_MODE mode);

#endif
