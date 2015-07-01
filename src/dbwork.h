/*
 * src/dbwork.h
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Simple source fot parsing data from config file.
 */


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/* User input configuration data */
typedef struct {
    int light_hour;
    int celsius_min;
    int celsius_max;
    int humidity_min;
} UserInputConfig;


/* 
 * ini_uic - This function initializes default 
 * config values for user inpute data. Argument
 * uic is pointer of UserInputConfig structure.
 */
void ini_uic(UserInputConfig *uic);


/* 
 * parse_user_config - This function parses values from config 
 * file. Argument uic is pointer of UserInputConfig structure.
 */
int parse_user_config(static char *fname, UserInputConfig *uic);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif
