public class hello{

	static{
	
		System.loadLibrary("hello");//libhello.so
	
	
	}

	public   native int   print(int  [] a);//使用native修饰的函数，在java中声明，实现在动态库中实现。
	public static void main (String [] args)
	{
		int  [] a = {1,2,3};
		hello  hello  = new hello();
		System.out.print(hello.print(a));

	}

}
