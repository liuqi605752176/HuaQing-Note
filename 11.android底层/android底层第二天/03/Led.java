public class Led{

	static{
	
		System.loadLibrary("fspad733_led");//libhello.so
	
	
	}

	public   native int   led_open();//使用native修饰的函数，在java中声明，实现在动态库中实现。
	public  native  int  led_ioctl(int which,int status);
	public static void main (String [] args)
	{
		Led  d = new Led();
		System.out.print(d.led_open());
		d.led_ioctl(1,1);

	}

}
