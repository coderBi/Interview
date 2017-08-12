package change.inner.array;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;

public class Main
{
	public static void main(String[] args) throws Exception{
		int a = 10;
		//获取Integer内部类IntegerCache
		Class<?>[] classes = Integer.class.getDeclaredClasses();
		Class<?> integerCache = null;
		for(Class<?> item : classes){
			if("IntegerCache".equals(item.getSimpleName())){
				integerCache = item;
				break;
			}
		}
		//获取integerCache里面的public final static Integer[] cache
		Field field = integerCache.getDeclaredField("cache");
		//设置可见性
		field.setAccessible(true);
		//获取field里面的内容 这里由于cache是static的，所以get传递一个null
		Integer[] cache = (Integer[])field.get(null);
		//修改cache数组
		cache[10 + 128] =  100;

		//测试结果
		System.out.printf("%d\n",a); //100 有装箱
		System.out.println(""+a); //10 由于函数实现是java1.5之前的 所以没有装箱
		System.out.println("" + Integer.valueOf(a)); //100 手动使用valueOf()方法返回相应的Integer对象
	}
}
