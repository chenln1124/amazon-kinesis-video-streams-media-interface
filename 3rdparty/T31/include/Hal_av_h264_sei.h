#ifndef AV_H264_SEI_H
#define AV_H264_SEI_H
extern int Hal_h264_avc_set_sei_packet(unsigned char *packet, const char *content, unsigned int size);
extern int Hal_h264_avc_get_sei_content(unsigned char * packet, unsigned int size, char * buffer,int *count);
#endif /* AV_H264_SEI_H */

