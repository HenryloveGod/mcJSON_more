

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


#include "mcJSON.h"

int  main(void )
{
    char *filestr;
    cJSON * all_tt;

    if ((filestr =read_json_file_delete_comment("test.json")) == NULL){
        printf("ERROR read file ! \n" );
        exit(EXIT_FAILURE);
    }

    if ((all_tt = cJSON_Parse(filestr)) == NULL){
        printf("ERROR file string to JSON !\n" );
        exit(EXIT_FAILURE);
    }

	printf("test data is :%s\n",cJSON_Print(all_tt));
	printf("child data list :%s\n",cJSON_Print(mcJSON_getJSON(all_tt,"data_list",NULL)));
	printf("test\\test1:%s\n",cJSON_Print(mcJSON_getJSON(all_tt,"test","test1",NULL)));
	printf("test\\test1\\test2\\name value :%s\n",mcJSON_getSTRING(all_tt,NULL,"test","test1","test2","name",NULL));
	printf("test\\test1\\test2\\id value :%d\n",mcJSON_getINT(all_tt,-1,"test","test1","test2","id",NULL));

	mcjson_setstring(all_tt,"text1_value","test","test1","test2" ,NULL);
	mcjson_setint(all_tt, 122,"status",NULL);
    mcjson_setstring(all_tt, "new msg value","msg",NULL);

    printf("test data change now :%s\n",cJSON_Print(all_tt));

	/*数据格式中，没有严格限定TYPE，所以test/test1下的test2 对象, 包含 字符串text1_value 和 test2对象 */
	printf("print text1_value position :%s\n",cJSON_Print(mcJSON_getJSON(all_tt,"test",NULL)));
	printf("get name value :%s\n",mcJSON_getSTRING(all_tt,NULL,"test","test1","test2","name",NULL));


	return 0;
}