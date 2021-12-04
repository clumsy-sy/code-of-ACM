//！！！！提交JAVA的时候一定要去掉package
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Scanner;
        Scanner cin=new Scanner(System.in);
        BigInteger num1=new BigInteger("12345");
        BigInteger num2=cin.nextBigInteger();
        BigDecimal num3=new BigDecimal("123.45");
        BigDecimal num4=cin.nextBigDecimal();
//整数
import java.math.BigInteger;
public class Main {
    public static void main(String[] args) {
        BigInteger num1=new BigInteger("12345");
        BigInteger num2=new BigInteger("45");    
        System.out.println(num1.add(num2));      //加法
        System.out.println(num1.subtract(num2)); //减法
        System.out.println(num1.multiply(num2)); //乘法
        System.out.println(num1.divide(num2));   //除法(相除取整)
        System.out.println(num1.mod(num2));      //取余
        System.out.println(num1.gcd(num2));      //最大公约数GCD
        System.out.println(num1.abs());          //取绝对值
        System.out.println(num1.negate());       //取反
        System.out.println(num1.max(num2));      //取最大值
        System.out.println(num1.min(num2));      //取最小值
        System.out.println(num1.equals(num2));   //是否相等
    }
}
//浮点数
import java.math.BigDecimal;
public class Main {
    public static void main(String[] args) {
        BigDecimal num1=new BigDecimal("123.45");
        BigDecimal num2=new BigDecimal("4.5");
        System.out.println(num1.add(num2));       //加法
        System.out.println(num1.subtract(num2));  //减法
        System.out.println(num1.multiply(num2));  //乘法
        //除法（在divide的时候就设置好要精确的小数位数和舍入模式）
        System.out.println(num1.divide(num2,10,BigDecimal.ROUND_HALF_DOWN);
        System.out.println(num1.abs());           //取绝对值
        System.out.println(num1.negate());        //取反
        System.out.println(num1.max(num2));       //取最大值
        System.out.println(num1.min(num2));       //取最小值
        System.out.println(num1.equals(num2));    //是否相等
        System.out.println(num2.compareTo(num1)); //判断大小( > 返回1, < 返回-1) 
    }
}