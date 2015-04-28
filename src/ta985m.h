#ifndef TA985M_H
#define TA985M_H


#define APP_NAME        "ta985m"
#define APP_Version     "0.0"
#define ORG_NAME        "OAO RCS"
#define ORG_DOMAIN      "http://www.rniikp.ru"


#define PVD_ADDR                24

#define ADDR_REGIM_LKG_1            2
#define ADDR_REGIM_LKG_2            3
#define ADDR_REGIM_LKG_3            4
#define ADDR_REGIM_LKG_4            5

#define ADDR_REGIM_LKD_1            6
#define ADDR_REGIM_LKD_2            7
#define ADDR_REGIM_LKD_3            8
#define ADDR_REGIM_LKD_4            9

#define MSS_BUFF_SIZE           256
#define MSS_BUFF_SIZE_WORD      (MSS_BUFF_SIZE / 2)
#define MSS_READ_BUFF_SIZE      64


#define MSS_ONOFF_ADDR          0

#define PVD_ONOFF_ADDR          0
#define PVD_REGIME_ADDR         5
#define PVD_TEST_RESULT_ADDR_ALL 0


#define MAG_TEST_RESULT_ADDR_ALL 0
#define MAG_REGIME_ADDR          0
#define MAG_SYNC_SOURCE_ADDR     2
#define MAG_CHANNEL_ADDR         4
#define MAG_SYNC_TACKT_ADDR      5
#define MAG_ADDRESS_ADDR         0


#define MSS_CHANAL1_ADDR        0
#define MSS_CHANAL2_ADDR        0
#define MSS_CHANAL3_ADDR        0
#define MSS_CHANAL4_ADDR        0
#define MSS_CHANAL_ADDR         4

#define MSS_SALFTEST_ADDR       6
#define MSS_TEST_RESULT_ADDR    4

#define MSS_BLOCK_WRITE         128

#define KOM_MSS_CHA_ADDR        0
#define KOM_MSS_CHB_ADDR        1
#define KOM_MSS_CHV_ADDR        2
#define KOM_MSS_CHG_ADDR        3
#define KOM_MSS_CHD_ADDR        4

#define KOM_MSS_OSN             0
#define KOM_MSS_RES             1








#endif // TA985M_H
