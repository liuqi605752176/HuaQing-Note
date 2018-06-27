
//cmd
#define FAIL '0'
#define OK '1'
#define LED_ON '2'
#define LED_OFF '3'
#define TEMP_HUMI '4'  //ÎÂÊª¶È
#define SMOKE '5' //ÑÌÎí
#define FIRE '6' //»ğÑæ
#define BODY '7' //ÈËÌå

struct shmbuf
{
	short int data[2];
};

struct msgbuf
{
	long mtype;
	char mtext[1];
};
