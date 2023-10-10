#include <stdint.h>
#include <stdbool.h>

/*
 * 输入帧的信息
 */
typedef struct {
    unsigned char *data; /**< 帧的起始地址 */
    int width;		 /**< 帧分辨率的宽 */
    int height;		 /**< 帧分辨率的高 */
    int pixfmt;		 /**< 帧的图像格式 */
	int64_t timeStamp; /**< 帧的时间戳 */
}t31_IVSFrame;

typedef t31_IVSFrame t31_IVSFrameInfo;

/*
 * 点的定义
 */
typedef struct{
    int x;    /**< 横向的坐标值 */
    int y;    /**< 纵向的坐标值 */
}t31_IVSPoint;

/*
 * 矩形框的定义
 */
typedef struct{
  t31_IVSPoint ul;    /**< 左上角点坐标 */
  t31_IVSPoint br;    /**< 右下角点坐标 */
}t31_IVSRect;
/*
 * 移动侦测输入结构体
 */
typedef struct {
  int sense; /**< 高级移动侦测的灵敏度，范围为0-4 */

  int min_h; /**< 高级移动侦测物体的最小高度 */
  int min_w; /**< 高级移动侦测物体的最小宽度 */

  t31_IVSRect* rois; /**< 高级移动侦测待检测的区域信息 */
  int cntRoi; /**< 高级移动侦测待检测区域的数量 */

  int isSkipFrame; /**< 高级移动侦测跳帧处理开关 */

  int det_w; /**<宫格最小单元宽度*/
  int det_h; /**<宫格最小单元高度 */

  bool light; /**< 高级移动侦测光照处理开关 */
  float level;/**0-1,屏幕检测程度  */
  int timeon;/**开灯用时  */
  int timeoff;/**开灯间隔  */

  t31_IVSFrameInfo frameInfo; /**< 帧信息 */
}t31_move_param_input_t;

/*
 * 
 */
typedef struct {
    //mod = 0: Configure convex polygons
  t31_IVSPoint *p;    /**< 周界各个顶点信息,不能有线交叉 */
  int pcnt;      /**<  周界顶点数量,最多8个点,*/
    //mod = 1:Configure Rect 
  t31_IVSRect r;
    
  int detdist; /**< 检测距离 0~4  0:6米 max(img_w, img_h) >= 320 ;  1:8米  max(img_w, img_h) >= 416 \
                    2:10米 max(img_w, img_h) >= 512   3:11米 max(img_w, img_h) >= 640 \
                    4:13米  max(img_w, img_h) >= 800 default:2 */

  uint64_t alarm_last_time;	/**<  reserved*/
}t31_persondet_perm_t;

/*
 * 人形检测输入结构体
 */
typedef struct {
    bool ptime; /**< 是否打印检测时间 */
    int skip_num; /**< 跳帧数目 */
    t31_IVSFrameInfo frameInfo; /**< 帧信息 */
    int sense; /**< 检测灵敏度 0~5 0:最不灵敏 5:最灵敏 default:4 */
    int detdist; /**< 检测距离 0~4  0:6米 max(img_w, img_h) >= 320 ;  1:8米  max(img_w, img_h) >= 416 \
                    2:10米 max(img_w, img_h) >= 512   3:11米 max(img_w, img_h) >= 640 \
                    4:13米  max(img_w, img_h) >= 800 default:2 */
    bool enable_move; /**<true: 开启移动侦测 false:关闭移动侦测 default: false>*/
    bool open_move_filter; /**<true: 只检测移动人形目标,需enable_move=ture; false:检测全部人形目标 default: false>*/
    int move_sense;   /**< 移动侦测的灵敏度，范围为0-4, default 2 */
    int move_min_h;   /**< 移动侦测物体的最小高度 , default 20*/
    int move_min_w;   /**< 移动侦测物体的最小宽度 , default 20*/
    bool enable_perm; /**<true: 开启周界功能 false: 关闭周界功能 default: false>*/
    t31_persondet_perm_t perms[IVS_PERSONDET_PERM_MAX_ROI];  /**< 周界信息 */
    int permcnt;      /**<  周界数量,最多4个*/
    int mod;          /**<  mod = 0: 检测多边形模式 mod = 1:检测矩形框模式 */
    bool update_perm;  /** 快速动态设制周界信息开关 ,true:快速更新功能开起,false:默认更新*/ 
    float pred_factor;  /**控制 pred_box 超前量系数 0.0 ~ 3.0 default 1.5, track_mode 生效*/
    bool track_mode;  /** 跟踪模式, true: 打开 ,false: 关闭, default false*/

}t31_persondet_param_input_t;