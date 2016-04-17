import java.util.Scanner;
public class fibonacci{
  
  
    public static int fibonacci(int n)
    { 
	System.out.println(n);
	System.out.println("fibonacci(" + n +")");
	if (n==0){
	    System.out.println("fibonacci=0");
	    return 0;
	} 
	else{
	    int x= fibonacci_helper ( n, 1, 0, 1 );
	    System.out.println("fibonacci="+ x);
	    return x;
	}
    
    }
  
    private static int fibonacci_helper (int n, int m, int fib_m_minus_1,int fib_m ){
	System.out.println("fibonacci_helper(" + n + "," + m + ","+ fib_m_minus_1+ "," + fib_m + ")");
	if (m==n){   
	    System.out.println("fibonacci_helper=" + fib_m);
	    return fib_m;
	}
	else {
	    int x= fibonacci_helper ( n, m + 1, fib_m, fib_m_minus_1 + fib_m);
	    System.out.println("fibonacci_helper=" + x);
	    return x;
      
	}
    
    }
    public static void main ( String [] args ){
	Scanner scanner = new Scanner( System.in );
	fibonacci fib= new fibonacci();
    
	while (scanner.hasNextLine()) {
	    int number = Integer.parseInt(scanner.nextLine()); 
	    fib.fibonacci(number);
	}
    }
}
