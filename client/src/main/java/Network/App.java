package Network;
import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

/**
 * Hello world!
 *
 */
public class App
{
    public static void main( String[] args ) throws UnknownHostException, IOException
    {
        System.out.println( "Hello World!" );
		int number;
		Scanner sc = new Scanner(System.in);
		Socket s = new Socket("127.0.0.1", 1342);
		Scanner sc1 = new Scanner(s.getInputStream());
		System.out.println("enter number");
		number = sc.nextInt();
		PrintStream p = new PrintStream(s.getOutputStream());
		p.println(number);

		int temp = sc1.nextInt();
		System.out.println(temp);
    }
}
