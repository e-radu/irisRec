// irisRec.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "utils.h"
void get_arguments(int argc, char* argv[], ARGS* argst)
{
    //set default values for arguments
    argst->dev_name = "/dev/video0";
    argst->usr_name = "unknown";
    argst->mode     = IRIS_CHK;
    int opt;
    while((opt = getopt(argc, argv, "d:a:")) != -1)
    {
        switch(opt)
        {
        case 'd' :
            argst->dev_name = optarg;
            break;
        case 'a' :
            argst->usr_name = optarg;
            argst->mode  = IRIS_ADD;
            break;
        case ':' :
            printf("Option -%c requires an operand\n", optopt);
            break;
        case '?' :
            printf("Unrecognized option: -%c\n", optopt);
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    //FILE* fn;
    IRISCONFIG config;
    ARGS argst;
    get_arguments(argc, argv, &argst);

    config.dev_name  = argst.dev_name;
    config.mode      = argst.mode;
    config.user_name = argst.usr_name;

    printf("Opening device %s\n", config.dev_name);
    config.width  = WIDTH;
    config.height = HEIGHT;
    //allocate memory for the input frame
    config.frame = (u8_int*)malloc(config.width * config.height);
    if(initIris(&config) != 1)
        return -1;
    if(runIris(&config) != 1)
        return -1;
    if(freeIris(&config) != 1)
        return -1;
    free(config.frame);
	return 0;
}

