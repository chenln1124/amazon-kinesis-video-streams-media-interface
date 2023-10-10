#ifndef GPIO_DES_HI3518EV200_H
#define GPIO_DES_HI3518EV200_H
#define HISI_GPIO_DECL(group, bit)	        (((group) << 16) | (bit))
#define HISI_MUXCTRL_CONFIG(offset, config)	(((offset) << 16) | (config))
#endif

