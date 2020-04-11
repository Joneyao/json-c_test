
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"


//json data
char text[] = "{\"timestamp\":\"%s\",\"value\":%d}";

void parse_json(char *pData)
{
    cJSON *pJson, *pJsonVal, *pJsonTS;
    char inS[128];
    int inValue = 0;
    char inString[128];

    scanf("%s %d",inString,&inValue);

    snprintf(inS,sizeof(inS),text,inString,inValue);
    
    pJson = cJSON_Parse(inS);
    if(!pJson){
        printf("Parse json error!\n");
    }
    else{
        pJsonVal = cJSON_GetObjectItem(pJson,"value");
        if(pJsonVal->type == cJSON_Number){
            printf("value:%d \n",pJsonVal->valueint);
        }

        pJsonTS = cJSON_GetObjectItem(pJson,"timestamp");
        if(pJsonTS->type == cJSON_String){
            printf("timestamp:%s \n",pJsonTS->valuestring);
        }

        //release json
        cJSON_Delete(pJson);        
    }
}

void make_json(void)
{
    char name[] = "yaojingwei";
    int list[4] = {1,2,3,4};
    char *nameList[3] = {"yao","jing","wei"};
    // create json object 
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root,"value",123.4);
    // 此种方式添加字符串时，不能进行对齐
    cJSON_AddStringToObject(root,"name",name);
    // 此种方式添加字符串时，输出能对齐
    cJSON_AddItemToObject(root,"name1",cJSON_CreateString(name));

    // 添加bool型
    cJSON_AddItemToObject(root,"success",cJSON_CreateTrue());
    cJSON_AddItemToObject(root,"fail",cJSON_CreateTrue());

    cJSON *pBool = cJSON_GetObjectItem(root,"success");
    if(pBool){
        printf("valueint:%d \n",pBool->valueint);
    }

    // add array
    cJSON_AddItemToObject(root,"lists",cJSON_CreateIntArray(list,4));
    
    cJSON *pRows, *pRow;
    cJSON_AddItemToObject(root,"rows", pRows = cJSON_CreateArray());
    int i = 0;
    for(i = 0; i < 3; i++){
        cJSON_AddItemToArray(pRows, pRow = cJSON_CreateObject());
        cJSON_AddItemToObject(pRow,"name",cJSON_CreateString(nameList[i]));
    }


    char *pOut = cJSON_Print(root);

    printf("json:%s \n",pOut);

    cJSON_Delete(root);
    free(pOut);
}

int main(int argc, char **argv)
{

    parse_json(NULL);

    return 0;
}
