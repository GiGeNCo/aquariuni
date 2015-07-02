/*
 * src/dbwork.c
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Simple source fot parsing data from config file.
 */


#include "stdinc.h"
#include "dbwork.h"


/* 
 * init_uic - This function initializes default 
 * config values for user inpute data. Argument
 * uic is pointer of UserInputConfig structure.
 */
void init_uic(UserInputConfig *uic) 
{
    uic->light_hour = 20;
    uic->celsius_min = 15;
    uic->celsius_max = 25;
    uic->humidity_min = 40;
}


/* 
 * parse_user_config - This function parses values from config 
 * file. Argument uic is pointer of UserInputConfig structure.
 */
int parse_user_config(const char *fname, UserInputConfig *uic) 
{
    /* Used variables */
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int ret = 0;

    /* Open file pointer */
    file = fopen(fname, "r");
    if(file == NULL) return ret;

    /* Line-by-line read cfg file */
    while ((read = getline(&line, &len, file)) != -1)
    {
        /* Find level in file */
        if(strstr(line, "LIGHT_HOUR") != NULL)
        {
            /* Get log level */
            uic->light_hour = atoi(line+10);
            ret = 1;
        }
        else if(strstr(line, "CELSIUS_MIN") != NULL)
        {
            /* Get log level */
            uic->celsius_min = atoi(line+11);
            ret = 1;
        }
        else if(strstr(line, "CELSIUS_MAX") != NULL)
        {
            /* Get log type */
            uic->celsius_max = atoi(line+11);
            ret = 1;
        }
        else if(strstr(line, "HUMIDITY_MIN") != NULL)
        {
            /* Get log type */
            uic->humidity_min = atoi(line+12);
            ret = 1;
        }
    }

    /* Cleanup */
    if (line) free(line);
    fclose(file);

    return ret;
}