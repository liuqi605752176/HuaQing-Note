#include <string.h>
#include "sqlite3.h"
#define N 20
int zhuce(char username[N],char userpasswd[N])
{
	
	sqlite3 *db;
	if(SQLITE_OK!=sqlite3_open("usr.db",&db))
	{
		return -1;
	}
	char sql[128] = {0};
	char **result;
	int row,column;
	sprintf(sql,"select * from user where name ='%s';",username);
	if(sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
	{
		sqlite3_close(db);
		return -2;
	}
	if(row!=0)
	{
		//用户名已存在
		sqlite3_close(db);
		return -3;
	}
	if(row==0)
	{
		char *errmsg;
		sprintf(sql,"insert into user values('%s','%s');",username,userpasswd);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
		{	
			//register fail
			sqlite3_free(errmsg);
			sqlite3_close(db);
			return -4;
		}
		//注册成功
		sqlite3_close(db);
		return 1;
	}

}
