#ifndef __DIGITAL_TUBE_H
#define __DIGITAL_TUBE_H

void disp_one_num(u8 num, int pos, u8 showPoint);
void disp_number(int num);
void digital_tube_init(void);
void disp_all_same(unsigned char num);
void show_adc(float VAL);

#endif
