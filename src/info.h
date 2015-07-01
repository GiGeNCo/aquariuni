/*
 * src/info.c
 *
 *  Copyleft (C) 2015  IliaUni Robotics TeaM  
 * 
 * Get additional information about program
 */


#define VERSION_MAX     1
#define VERSION_MID     0
#define VERSION_MIN     2
#define BUILD_NUMBER    24


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/* 
 * get_version - Get program version. Function returns 
 * version, build number and build date of application. 
 * Return value is char pointer.
 */
const char* get_version();


/* 
 * get_version_short - Get program version. Function returns only
 * version, build number of application without additional strings. 
 * Return value is char pointer. For example: 1.0.32
 */
const char* get_version_short();


/* 
 * greet - Print greeting message. Function returns program 
 * name, version, build number and build date. Argument 
 * p_name is program name from which we want to greet users. 
 */
void greet(char *p_name);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif
