#include<string.h>
#include "sqlite3.h"

#define N 20

int denglu(char username[N],char userpasswd[N])
{
	

		sqlite3 *db;
		if(SQLITE_OK!=sqlite3_open("usr.db",&db))
		{
			return -1;
		}
		char sql[128];
		char **result;
		int row,column;
		sprintf(sql,"select * from xin where name ='%s' and password='%s';",username,userpasswd);
		if(sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
		{
			sqlite3_close(db);
			return -2;
		}

		if(row == 0)
		{
			sqlite3_close(db);
			return -3;
		}
		if(row != 0)
        {
            return 1;
        }


}
