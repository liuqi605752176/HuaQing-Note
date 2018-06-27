public class hello{

	static{
	
		System.loadLibrary("hello");//libhello.so
	
	
	}

	public   native int   print();//使用native修饰的函数，在java中声明，实现在动态库中实现。
	public static void main (String [] args)
	{
		hello  hello  = new hello();
		hello.print();

	}

}
