public class hello{

	static{
	
		System.loadLibrary("hello");//libhello.so
	
	
	}

	public   native int   print();//使用native修饰的函数，在java中声明，实现在动态库中实现。
	public  native  int  hello_open();
	public  native  int  hello_read();
	public  native  int  hello_write(int val);
	public  native  int  hello_ioctl(int which,int status);
	public static void main (String [] args)
	{
		hello  hello  = new hello();
		hello.print();
		hello.hello_open();
		hello.hello_read();
		System.out.print(hello.hello_write(1));
		System.out.print(hello.hello_ioctl(3,4));

	}

}
