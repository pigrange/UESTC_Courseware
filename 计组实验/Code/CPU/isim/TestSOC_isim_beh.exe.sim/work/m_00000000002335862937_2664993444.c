/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "D:/Codes/Verilog/CPU/Extender.v";
static unsigned int ng1[] = {65535U, 0U};
static unsigned int ng2[] = {0U, 0U};



static void Cont_26_0(char *t0)
{
    char t3[8];
    char t4[8];
    char t16[8];
    char t19[8];
    char t20[8];
    char t22[8];
    char t51[8];
    char t54[8];
    char t55[8];
    char t57[8];
    char *t1;
    char *t2;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    char *t17;
    char *t18;
    char *t21;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    char *t36;
    char *t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    char *t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    char *t52;
    char *t53;
    char *t56;
    char *t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    char *t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    char *t71;
    char *t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    char *t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    char *t81;
    char *t82;
    char *t83;
    char *t84;
    char *t85;
    char *t86;
    char *t87;

LAB0:    t1 = (t0 + 2528U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(26, ng0);
    t2 = (t0 + 1208U);
    t5 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t5 + 4);
    t6 = *((unsigned int *)t2);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 & 1U);
    if (t10 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t2) != 0)
        goto LAB6;

LAB7:    t12 = (t4 + 4);
    t13 = *((unsigned int *)t4);
    t14 = *((unsigned int *)t12);
    t15 = (t13 || t14);
    if (t15 > 0)
        goto LAB8;

LAB9:    t47 = *((unsigned int *)t4);
    t48 = (~(t47));
    t49 = *((unsigned int *)t12);
    t50 = (t48 || t49);
    if (t50 > 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t12) > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) > 0)
        goto LAB14;

LAB15:    memcpy(t3, t51, 8);

LAB16:    t82 = (t0 + 2928);
    t83 = (t82 + 56U);
    t84 = *((char **)t83);
    t85 = (t84 + 56U);
    t86 = *((char **)t85);
    memcpy(t86, t3, 8);
    xsi_driver_vfirst_trans(t82, 0, 31);
    t87 = (t0 + 2848);
    *((int *)t87) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t4) = 1;
    goto LAB7;

LAB6:    t11 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB7;

LAB8:    t17 = (t0 + 1048U);
    t18 = *((char **)t17);
    t17 = (t0 + 1048U);
    t21 = *((char **)t17);
    memset(t22, 0, 8);
    t17 = (t22 + 4);
    t23 = (t21 + 4);
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 15);
    t26 = (t25 & 1);
    *((unsigned int *)t22) = t26;
    t27 = *((unsigned int *)t23);
    t28 = (t27 >> 15);
    t29 = (t28 & 1);
    *((unsigned int *)t17) = t29;
    memset(t20, 0, 8);
    t30 = (t22 + 4);
    t31 = *((unsigned int *)t30);
    t32 = (~(t31));
    t33 = *((unsigned int *)t22);
    t34 = (t33 & t32);
    t35 = (t34 & 1U);
    if (t35 != 0)
        goto LAB17;

LAB18:    if (*((unsigned int *)t30) != 0)
        goto LAB19;

LAB20:    t37 = (t20 + 4);
    t38 = *((unsigned int *)t20);
    t39 = *((unsigned int *)t37);
    t40 = (t38 || t39);
    if (t40 > 0)
        goto LAB21;

LAB22:    t42 = *((unsigned int *)t20);
    t43 = (~(t42));
    t44 = *((unsigned int *)t37);
    t45 = (t43 || t44);
    if (t45 > 0)
        goto LAB23;

LAB24:    if (*((unsigned int *)t37) > 0)
        goto LAB25;

LAB26:    if (*((unsigned int *)t20) > 0)
        goto LAB27;

LAB28:    memcpy(t19, t46, 8);

LAB29:    xsi_vlogtype_concat(t16, 32, 32, 2U, t19, 16, t18, 16);
    goto LAB9;

LAB10:    t52 = (t0 + 1048U);
    t53 = *((char **)t52);
    t52 = (t0 + 1048U);
    t56 = *((char **)t52);
    memset(t57, 0, 8);
    t52 = (t57 + 4);
    t58 = (t56 + 4);
    t59 = *((unsigned int *)t56);
    t60 = (t59 >> 15);
    t61 = (t60 & 1);
    *((unsigned int *)t57) = t61;
    t62 = *((unsigned int *)t58);
    t63 = (t62 >> 15);
    t64 = (t63 & 1);
    *((unsigned int *)t52) = t64;
    memset(t55, 0, 8);
    t65 = (t57 + 4);
    t66 = *((unsigned int *)t65);
    t67 = (~(t66));
    t68 = *((unsigned int *)t57);
    t69 = (t68 & t67);
    t70 = (t69 & 1U);
    if (t70 != 0)
        goto LAB30;

LAB31:    if (*((unsigned int *)t65) != 0)
        goto LAB32;

LAB33:    t72 = (t55 + 4);
    t73 = *((unsigned int *)t55);
    t74 = *((unsigned int *)t72);
    t75 = (t73 || t74);
    if (t75 > 0)
        goto LAB34;

LAB35:    t77 = *((unsigned int *)t55);
    t78 = (~(t77));
    t79 = *((unsigned int *)t72);
    t80 = (t78 || t79);
    if (t80 > 0)
        goto LAB36;

LAB37:    if (*((unsigned int *)t72) > 0)
        goto LAB38;

LAB39:    if (*((unsigned int *)t55) > 0)
        goto LAB40;

LAB41:    memcpy(t54, t81, 8);

LAB42:    xsi_vlogtype_concat(t51, 32, 32, 2U, t54, 16, t53, 16);
    goto LAB11;

LAB12:    xsi_vlog_unsigned_bit_combine(t3, 32, t16, 32, t51, 32);
    goto LAB16;

LAB14:    memcpy(t3, t16, 8);
    goto LAB16;

LAB17:    *((unsigned int *)t20) = 1;
    goto LAB20;

LAB19:    t36 = (t20 + 4);
    *((unsigned int *)t20) = 1;
    *((unsigned int *)t36) = 1;
    goto LAB20;

LAB21:    t41 = ((char*)((ng1)));
    goto LAB22;

LAB23:    t46 = ((char*)((ng2)));
    goto LAB24;

LAB25:    xsi_vlog_unsigned_bit_combine(t19, 16, t41, 16, t46, 16);
    goto LAB29;

LAB27:    memcpy(t19, t41, 8);
    goto LAB29;

LAB30:    *((unsigned int *)t55) = 1;
    goto LAB33;

LAB32:    t71 = (t55 + 4);
    *((unsigned int *)t55) = 1;
    *((unsigned int *)t71) = 1;
    goto LAB33;

LAB34:    t76 = ((char*)((ng2)));
    goto LAB35;

LAB36:    t81 = ((char*)((ng2)));
    goto LAB37;

LAB38:    xsi_vlog_unsigned_bit_combine(t54, 16, t76, 16, t81, 16);
    goto LAB42;

LAB40:    memcpy(t54, t76, 8);
    goto LAB42;

}


extern void work_m_00000000002335862937_2664993444_init()
{
	static char *pe[] = {(void *)Cont_26_0};
	xsi_register_didat("work_m_00000000002335862937_2664993444", "isim/TestSOC_isim_beh.exe.sim/work/m_00000000002335862937_2664993444.didat");
	xsi_register_executes(pe);
}
