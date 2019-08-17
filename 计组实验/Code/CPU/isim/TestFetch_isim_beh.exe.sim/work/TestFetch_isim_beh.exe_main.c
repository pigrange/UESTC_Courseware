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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000000084592999_2009983731_init();
    work_m_00000000001650841550_4062847055_init();
    work_m_00000000003026779820_4031852583_init();
    work_m_00000000001197957474_0192710021_init();
    work_m_00000000003195823987_1733832700_init();
    work_m_00000000003434545822_1307194410_init();
    work_m_00000000003397153614_0894457032_init();
    work_m_00000000004047273037_3543086789_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000004047273037_3543086789");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
